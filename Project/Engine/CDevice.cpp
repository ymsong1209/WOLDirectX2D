#include "pch.h"
#include "CDevice.h"
#include "CEngine.h"
#include "CConstBuffer.h"

#include "CResMgr.h"

CDevice::CDevice()
	: m_hWnd(nullptr)
	, m_ViewPort{}
	, m_arrConstBuffer{}
{
}

CDevice::~CDevice()
{
	Safe_Del_Array(m_arrConstBuffer);
}


int CDevice::init(HWND _hWnd, UINT _iWidth, UINT _iHeight)
{
	m_hWnd = _hWnd;
	m_vRenderResolution = Vec2((float)_iWidth, (float)_iHeight);

	GlobalData.Resolution = m_vRenderResolution;

	int iFlag = 0;
#ifdef _DEBUG
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL eLevel = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;


	if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE
		, nullptr, iFlag
		, nullptr, 0
		, D3D11_SDK_VERSION
		, m_Device.GetAddressOf(), &eLevel
		, m_Context.GetAddressOf()))) {
		MessageBox(nullptr, L"Device, Context ���� ����", L"Device �ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}

	if (FAILED(CreateSwapChain())) {
		MessageBox(nullptr, L"����ü�� ���� ����", L"Device �ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}

	if (FAILED(CreateView())) {
		MessageBox(nullptr, L"View ���� ����", L"Device �ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}

	// ��� Ÿ�� ����. �������� ����?
	// ���� �ؽ��Ĵ� �������ϼ� ������ ���� �ؽ��Ĵ� ������ �Ѱ�������
	// �׷��� ���ڸ� ����Ÿ�ٹ迭�� �ּ�(����������)�� �����
	//IMGUI�� Windows�� �ϳ� �� ������Ű�� RenderTarget�� ���ο� Window�� ���������.
	//�츮�� Engine���� ���� �͵��� MainWindow�� ��µǾ���ϴϱ�,
	//m_Context->OMSetRenderTargets(1, m_RTV.GetAddressOf(), m_DSV.Get());

	//ViewPort����
	m_ViewPort.TopLeftX = 0.f;
	m_ViewPort.TopLeftY = 0.f;

	Vec2 vWindowResol = CEngine::GetInst()->GetWindowResolution();
	m_ViewPort.Width = vWindowResol.x;
	m_ViewPort.Height = vWindowResol.y;

	m_ViewPort.MinDepth = 0.f;
	m_ViewPort.MaxDepth = 1.f;

	m_Context->RSSetViewports(1, &m_ViewPort);

	// RasterizerState ����
	if (FAILED(CreateRasterizerState()))
	{
		MessageBox(nullptr, L"�����Ͷ����� ������Ʈ ���� ����", L"Device �ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}

	// DepthStencilState ����
	if (FAILED(CreateDepthStencilState()))
	{
		MessageBox(nullptr, L"DepthStencilState ���� ����", L"Device �ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}

	// BlendState ����
	if (FAILED(CreateBlendState()))
	{
		MessageBox(nullptr, L"BlendState ���� ����", L"Device �ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}


	// ���÷� ����
	if (FAILED(CreateSampler()))
	{
		MessageBox(nullptr, L"���÷� ���� ����", L"Device �ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}

	// ������� ����
	CreateConstBuffer();

	return S_OK;//��ȯ �����ϸ� E_FAIL��ũ�ΰ� ��
}


int CDevice::CreateSwapChain()
{
	//swapchange�� dx������ �ٲ� �Ȱ���.

	//����ü�� ����
	DXGI_SWAP_CHAIN_DESC tDesc = {};

	tDesc.OutputWindow = m_hWnd; //��� ����Ұ��� �˾ƾ���
	tDesc.Windowed = true; //â��� , ��üȭ�� ���


	tDesc.BufferCount = 1; //���۰� front, back �ΰ������ϴµ� buffercount 1�� �����޶��ϸ� �˾Ƽ� 2�� �������. DX11������ 1
	tDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;//rendertarget�뵵�� �����������. swapchain���鶧 �ٵ� �ڵ������� buffer�� �����! ������ �뵵�� ����Ÿ���̴�.
	tDesc.BufferDesc.Width = (UINT)m_vRenderResolution.x;
	tDesc.BufferDesc.Height = (UINT)m_vRenderResolution.y;
	tDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//�ȼ� ���� red 8bit blue 8bit green 8bit alpha 8bit = 32bit
	tDesc.BufferDesc.RefreshRate.Denominator = 1; //�и�, ȭ�� ���� ����.����ӵ�.60hz
	tDesc.BufferDesc.RefreshRate.Numerator = 60; //����, swapchain�� 1/60�ʰ� �Ǹ� �׶� ������. ������� �Ѱ谡 �׸�ŭ�̱� ����
	tDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;//������
	tDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;//������


	tDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD; //dxgi swapeffect, ���۰� change�ɶ����� ���� �׸� ���� �����ٴ¶�
	tDesc.SampleDesc.Count = 1;
	tDesc.SampleDesc.Quality = 0;

	tDesc.Flags = 0;

	
	// ����ü�� ����
	ComPtr<IDXGIDevice>  pDXGIDevice;
	ComPtr<IDXGIAdapter> pAdapter;
	ComPtr<IDXGIFactory> pFactory;

	HRESULT hr = S_OK;

	hr = m_Device->QueryInterface(__uuidof(IDXGIDevice), (void**)pDXGIDevice.GetAddressOf());
	hr = pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)pAdapter.GetAddressOf());
	hr = pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)pFactory.GetAddressOf());

	hr = pFactory->CreateSwapChain(m_Device.Get(), &tDesc, m_SwapChain.GetAddressOf());

	return hr;
}

int CDevice::CreateView()
{
	//CreateView���� ���� �̹� RenderTexture�� Backbuffer�� ���������.
	ComPtr<ID3D11Texture2D> tex2D;
	m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)tex2D.GetAddressOf());
	

	// RenderTarget �� �ؽ��� ���
	m_RTTex = CResMgr::GetInst()->CreateTexture(L"RenderTargetTex", tex2D);

	// DepthStencil �뵵 �ؽ��� ����
	// Format : DXGI_FORMAT_D24_UNORM_S8_UINT �ȼ� �ϳ��� 4����Ʈ float, ���̸� �����Ұű� ����
	m_DSTex = CResMgr::GetInst()->CreateTexture(L"DepthStencilTex"
		, (UINT)m_vRenderResolution.x, (UINT)m_vRenderResolution.y
		, DXGI_FORMAT_D24_UNORM_S8_UINT, D3D11_BIND_DEPTH_STENCIL, D3D11_USAGE_DEFAULT);



	return S_OK;
}

int CDevice::CreateRasterizerState()
{
	m_RSState[(UINT)RS_TYPE::CULL_BACK] = nullptr;

	D3D11_RASTERIZER_DESC Desc = {};
	Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;
	Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;//Solid : ���θ� ä���.
	DEVICE->CreateRasterizerState(&Desc, m_RSState[(UINT)RS_TYPE::CULL_FRONT].GetAddressOf());

	Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
	Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	DEVICE->CreateRasterizerState(&Desc, m_RSState[(UINT)RS_TYPE::CULL_NONE].GetAddressOf());

	Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
	Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
	DEVICE->CreateRasterizerState(&Desc, m_RSState[(UINT)RS_TYPE::WIRE_FRAME].GetAddressOf());

	return S_OK;
}

int CDevice::CreateDepthStencilState()
{
	// Less
	m_DSState[(UINT)DS_TYPE::LESS] = nullptr;

	// Less Equal
	D3D11_DEPTH_STENCIL_DESC Desc = {};
	Desc.DepthEnable = true;
	Desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	Desc.StencilEnable = false;
	Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	DEVICE->CreateDepthStencilState(&Desc, m_DSState[(UINT)DS_TYPE::LESS_EQUAL].GetAddressOf());

	// Greater
	Desc.DepthEnable = true;
	Desc.DepthFunc = D3D11_COMPARISON_GREATER;
	Desc.StencilEnable = false;
	Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	DEVICE->CreateDepthStencilState(&Desc, m_DSState[(UINT)DS_TYPE::GREATER].GetAddressOf());

	// Greater Equal
	Desc.DepthEnable = true;
	Desc.DepthFunc = D3D11_COMPARISON_GREATER_EQUAL;
	Desc.StencilEnable = false;
	Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	DEVICE->CreateDepthStencilState(&Desc, m_DSState[(UINT)DS_TYPE::GREATER_EQUAL].GetAddressOf());

	// No Write
	// ���� ������ less�� ������, ���̰��� ������Ѵ�. ���� �׷��� �ְ� �־ ���������� ������ ���� �ִ�.
	Desc.DepthEnable = true;
	Desc.DepthFunc = D3D11_COMPARISON_LESS;
	Desc.StencilEnable = false;
	Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	DEVICE->CreateDepthStencilState(&Desc, m_DSState[(UINT)DS_TYPE::NO_WRITE].GetAddressOf());

	// NoTest NoWrite
	// ���� ������ ���ϰ�, ������ ���̸� ������ �ʴ´�.
	Desc.DepthEnable = false;
	Desc.StencilEnable = false;
	Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	DEVICE->CreateDepthStencilState(&Desc, m_DSState[(UINT)DS_TYPE::NO_TEST_NO_WRITE].GetAddressOf());


	return S_OK;
}

int CDevice::CreateBlendState()
{
	// No Blend
	m_BSState[(UINT)BS_TYPE::DEFAULT] = nullptr;

	// Mask
	D3D11_BLEND_DESC Desc = {};
	Desc.AlphaToCoverageEnable = true; //coverage�ɼ��� 0.5���̸� �׳� ������ �׷��� �������� transparent�� ������ ���Ѵ�.
	Desc.IndependentBlendEnable = false;

	Desc.RenderTarget[0].BlendEnable = true;
	Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	Desc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;

	Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

	Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	DEVICE->CreateBlendState(&Desc, m_BSState[(UINT)BS_TYPE::MASK].GetAddressOf());


	// Alpha Blend
	Desc.AlphaToCoverageEnable = false;
	Desc.IndependentBlendEnable = false;

	Desc.RenderTarget[0].BlendEnable = true;
	Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	Desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

	Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

	Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	DEVICE->CreateBlendState(&Desc, m_BSState[(UINT)BS_TYPE::ALPHA_BLEND].GetAddressOf());




	// One One
	Desc.AlphaToCoverageEnable = false;
	Desc.IndependentBlendEnable = false;

	Desc.RenderTarget[0].BlendEnable = true;
	Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	Desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;

	Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

	Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	DEVICE->CreateBlendState(&Desc, m_BSState[(UINT)BS_TYPE::ONE_ONE].GetAddressOf());

	return S_OK;
}


int CDevice::CreateSampler()
{
	D3D11_SAMPLER_DESC tSamDesc = {};
	
	//WrapMode : �ؽ��İ� �������� �þ
	tSamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	tSamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	tSamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	tSamDesc.Filter = D3D11_FILTER_ANISOTROPIC; //�̹漺 ���͸�, �ֺ� ������ �����ͼ� ����
	DEVICE->CreateSamplerState(&tSamDesc, m_Sampler[0].GetAddressOf());

	tSamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	tSamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	tSamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	tSamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;//������ ������ �״�� ������, �ȼ� ���ӿ� ������
	DEVICE->CreateSamplerState(&tSamDesc, m_Sampler[1].GetAddressOf());

	CONTEXT->VSSetSamplers(0, 1, m_Sampler[0].GetAddressOf());
	CONTEXT->HSSetSamplers(0, 1, m_Sampler[0].GetAddressOf());
	CONTEXT->DSSetSamplers(0, 1, m_Sampler[0].GetAddressOf());
	CONTEXT->GSSetSamplers(0, 1, m_Sampler[0].GetAddressOf());
	CONTEXT->PSSetSamplers(0, 1, m_Sampler[0].GetAddressOf());
	

	CONTEXT->VSSetSamplers(1, 1, m_Sampler[1].GetAddressOf());
	CONTEXT->HSSetSamplers(1, 1, m_Sampler[1].GetAddressOf());
	CONTEXT->DSSetSamplers(1, 1, m_Sampler[1].GetAddressOf());
	CONTEXT->GSSetSamplers(1, 1, m_Sampler[1].GetAddressOf());
	CONTEXT->PSSetSamplers(1, 1, m_Sampler[1].GetAddressOf());
	

	return S_OK;
}

void CDevice::ClearTarget(float(&_color)[4])
{
	m_Context->ClearRenderTargetView(m_RTTex->GetRTV().Get(), _color);
	m_Context->ClearDepthStencilView(m_DSTex->GetDSV().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0); //���̰��� 1�� �����ؾ��� �ٸ� object���� �ִ��� 1���� ���� ��ġ�� ��ϵ�
}

void CDevice::CreateConstBuffer()
{
	m_arrConstBuffer[(UINT)CB_TYPE::TRANSFORM] = new CConstBuffer((UINT)CB_TYPE::TRANSFORM);
	m_arrConstBuffer[(UINT)CB_TYPE::TRANSFORM]->Create(sizeof(tTransform), 1);

	m_arrConstBuffer[(UINT)CB_TYPE::MATERIAL] = new CConstBuffer((UINT)CB_TYPE::MATERIAL);
	m_arrConstBuffer[(UINT)CB_TYPE::MATERIAL]->Create(sizeof(tMtrlConst), 1);

	m_arrConstBuffer[(UINT)CB_TYPE::GLOBAL] = new CConstBuffer((UINT)CB_TYPE::GLOBAL);
	m_arrConstBuffer[(UINT)CB_TYPE::GLOBAL]->Create(sizeof(tGlobal), 1);
}

