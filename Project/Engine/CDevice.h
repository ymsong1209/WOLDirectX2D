#pragma once

#include "ptr.h"
#include "CTexture.h"
class CConstBuffer;


class CDevice
	: public CSingleton<CDevice>
{
private:
	HWND							m_hWnd;
	
	
	ComPtr<ID3D11Device>			m_Device; //GPU �޸� �Ҵ�
	ComPtr<ID3D11DeviceContext>		m_Context; //GPU ����, ������, ���� ����

	ComPtr<IDXGISwapChain>			m_SwapChain;


	Ptr<CTexture>					m_RTTex;
	Ptr<CTexture>					m_DSTex;


		
	ComPtr<ID3D11SamplerState>		m_Sampler[2];// Sampler

	// RasterizerState
	ComPtr<ID3D11RasterizerState>	m_RSState[(UINT)RS_TYPE::END];

	// DepthStencilState
	ComPtr<ID3D11DepthStencilState>	m_DSState[(UINT)DS_TYPE::END];

	// BlendState
	ComPtr<ID3D11BlendState>		m_BSState[(UINT)BS_TYPE::END];


	D3D11_VIEWPORT					m_ViewPort;

	//����Ÿ�� �ػ�
	Vec2							m_vRenderResolution;

	CConstBuffer* m_arrConstBuffer[(UINT)CB_TYPE::END];

	// ID3D11RenderTargetView
	// ID3D11DepthStencilView
	// ID3D11ShaderResourceView
	// ID3D11UnorderedAccessView

public:
	int init(HWND _hWnd, UINT _iWidth, UINT _iHeight);
	void ClearTarget(float(&_color)[4]);
	void OMSet() { m_Context->OMSetRenderTargets(1, m_RTTex->GetRTV().GetAddressOf(), m_DSTex->GetDSV().Get()); }
	void Present(){	m_SwapChain->Present(0, 0);	}
	Vec2 GetRenderResolution() { return m_vRenderResolution; }

private:
	int CreateSwapChain();
	int CreateView();
	int CreateRasterizerState();
	int CreateBlendState();
	int CreateDepthStencilState();
	int CreateSampler();
	void CreateConstBuffer();
public:
	ID3D11Device* GetDevice() {	return m_Device.Get();}
	ID3D11DeviceContext* GetDeviceContext() { return m_Context.Get(); }
	CConstBuffer* GetConstBuffer(CB_TYPE _Type) { return m_arrConstBuffer[(UINT)_Type]; }

	ComPtr<ID3D11RasterizerState> GetRSState(RS_TYPE _Type) { return m_RSState[(UINT)_Type]; }
	ComPtr<ID3D11DepthStencilState> GetDSState(DS_TYPE _Type) { return m_DSState[(UINT)_Type]; }
	ComPtr<ID3D11BlendState> GetBSState(BS_TYPE _Type) { return m_BSState[(UINT)_Type]; }


	const D3D11_VIEWPORT& GetViewport() { return m_ViewPort; }
public:
	CDevice();
	~CDevice();
};

