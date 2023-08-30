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
		MessageBox(nullptr, L"Device, Context 생성 실패", L"Device 초기화 에러", MB_OK);
		return E_FAIL;
	}

	if (FAILED(CreateSwapChain())) {
		MessageBox(nullptr, L"스왑체인 생성 실패", L"Device 초기화 에러", MB_OK);
		return E_FAIL;
	}

	if (FAILED(CreateView())) {
		MessageBox(nullptr, L"View 생성 실패", L"Device 초기화 에러", MB_OK);
		return E_FAIL;
	}

	// 출력 타겟 설정. 목적지가 어디냐?
	// 렌더 텍스쳐는 여러개일수 있지만 깊이 텍스쳐는 무조건 한개여야함
	// 그래서 인자를 렌터타겟배열의 주소(이중포인터)로 줘야함
	//IMGUI가 Windows를 하나 더 생성시키면 RenderTarget이 새로운 Window로 덮어씌워진다.
	//우리의 Engine에서 만든 것들은 MainWindow에 출력되어야하니깐,
	//m_Context->OMSetRenderTargets(1, m_RTV.GetAddressOf(), m_DSV.Get());

	//ViewPort설정
	m_ViewPort.TopLeftX = 0.f;
	m_ViewPort.TopLeftY = 0.f;

	Vec2 vWindowResol = CEngine::GetInst()->GetWindowResolution();
	m_ViewPort.Width = vWindowResol.x;
	m_ViewPort.Height = vWindowResol.y;

	m_ViewPort.MinDepth = 0.f;
	m_ViewPort.MaxDepth = 1.f;

	m_Context->RSSetViewports(1, &m_ViewPort);

	// RasterizerState 생성
	if (FAILED(CreateRasterizerState()))
	{
		MessageBox(nullptr, L"레스터라이져 스테이트 생성 실패", L"Device 초기화 에러", MB_OK);
		return E_FAIL;
	}

	// DepthStencilState 생성
	if (FAILED(CreateDepthStencilState()))
	{
		MessageBox(nullptr, L"DepthStencilState 생성 실패", L"Device 초기화 에러", MB_OK);
		return E_FAIL;
	}

	// BlendState 생성
	if (FAILED(CreateBlendState()))
	{
		MessageBox(nullptr, L"BlendState 생성 실패", L"Device 초기화 에러", MB_OK);
		return E_FAIL;
	}


	// 샘플러 생성
	if (FAILED(CreateSampler()))
	{
		MessageBox(nullptr, L"샘플러 생성 실패", L"Device 초기화 에러", MB_OK);
		return E_FAIL;
	}

	// 상수버퍼 생성
	CreateConstBuffer();

	return S_OK;//반환 실패하면 E_FAIL메크로가 뜸
}


int CDevice::CreateSwapChain()
{
	//swapchange는 dx버전이 바뀌어도 똑같다.

	//스왑체인 설정
	DXGI_SWAP_CHAIN_DESC tDesc = {};

	tDesc.OutputWindow = m_hWnd; //어디에 출력할건지 알아야함
	tDesc.Windowed = true; //창모드 , 전체화면 모드


	tDesc.BufferCount = 1; //버퍼가 front, back 두개여야하는데 buffercount 1개 만들어달라하면 알아서 2개 만들어줌. DX11에서는 1
	tDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;//rendertarget용도로 만들어져야함. swapchain만들때 근데 자동적으로 buffer도 만든다! 버퍼의 용도가 렌더타깃이다.
	tDesc.BufferDesc.Width = (UINT)m_vRenderResolution.x;
	tDesc.BufferDesc.Height = (UINT)m_vRenderResolution.y;
	tDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//픽셀 포맷 red 8bit blue 8bit green 8bit alpha 8bit = 32bit
	tDesc.BufferDesc.RefreshRate.Denominator = 1; //분모, 화면 갱신 비율.송출속도.60hz
	tDesc.BufferDesc.RefreshRate.Numerator = 60; //분자, swapchain이 1/60초가 되면 그때 송출함. 모니터의 한계가 그만큼이기 때문
	tDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;//미지정
	tDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;//미지정


	tDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD; //dxgi swapeffect, 버퍼가 change될때마다 기존 그림 위에 덮어씌운다는뜻
	tDesc.SampleDesc.Count = 1;
	tDesc.SampleDesc.Quality = 0;

	tDesc.Flags = 0;

	
	// 스왚체인 생성
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
	//CreateView까지 오면 이미 RenderTexture의 Backbuffer는 만들어졌음.
	ComPtr<ID3D11Texture2D> tex2D;
	m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)tex2D.GetAddressOf());
	

	// RenderTarget 용 텍스쳐 등록
	m_RTTex = CResMgr::GetInst()->CreateTexture(L"RenderTargetTex", tex2D);

	// DepthStencil 용도 텍스쳐 생성
	// Format : DXGI_FORMAT_D24_UNORM_S8_UINT 픽셀 하나가 4바이트 float, 깊이를 저장할거기 때문
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
	Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;//Solid : 내부를 채운다.
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
	// 깊이 판정은 less로 하지만, 깊이값을 저장안한다. 먼저 그려진 애가 있어서 누군가에게 가려질 수도 있다.
	Desc.DepthEnable = true;
	Desc.DepthFunc = D3D11_COMPARISON_LESS;
	Desc.StencilEnable = false;
	Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	DEVICE->CreateDepthStencilState(&Desc, m_DSState[(UINT)DS_TYPE::NO_WRITE].GetAddressOf());

	// NoTest NoWrite
	// 깊이 판정도 안하고, 본인의 깊이를 남기지 않는다.
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
	Desc.AlphaToCoverageEnable = true; //coverage옵션이 0.5밑이면 그냥 투명임 그래서 반투명한 transparent랑 조합을 못한다.
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
	
	//WrapMode : 텍스쳐가 무한으로 늘어남
	tSamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	tSamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	tSamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	tSamDesc.Filter = D3D11_FILTER_ANISOTROPIC; //이방성 필터링, 주변 색상을 가져와서 보정
	DEVICE->CreateSamplerState(&tSamDesc, m_Sampler[0].GetAddressOf());

	tSamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	tSamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	tSamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	tSamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;//참조한 색상을 그대로 가져옴, 픽셀 게임에 적합함
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
	m_Context->ClearDepthStencilView(m_DSTex->GetDSV().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0); //깊이값을 1로 지정해야지 다른 object들이 최대인 1보다 작은 위치에 기록됨
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

