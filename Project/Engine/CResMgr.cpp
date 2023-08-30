#include "pch.h"
#include "CResMgr.h"

#include "CPathMgr.h"

#include "CGameObject.h"
#include "components.h"


CResMgr::CResMgr()
{
}

CResMgr::~CResMgr()
{
}

void CResMgr::init()
{
	InitSound();
	CreateDefaultMesh();
	CreateDefaultGraphicsShader();
	CreateDefaultComputeShader();
	//CreateDefaultMaterial();
	//CreateDefaultPrefab();
	//LoadDefaultTexture();
	//Texture, Material, Prefab은 이제 contentUI에서 자동로딩
}

void CResMgr::InitSound()
{
	FMOD::System_Create(&CSound::g_pFMOD);

	if (nullptr == CSound::g_pFMOD)
	{
		assert(nullptr);
	}

	// 32개 채널 생성
	// 동시에 재생할 수 있는 Sound가 32개
	CSound::g_pFMOD->init(32, FMOD_DEFAULT, nullptr);
}

void CResMgr::tick()
{
	m_Changed = false;
}

void CResMgr::CreateDefaultMesh()
{
	vector<Vtx> vecVtx;
	vector<UINT> vecIdx;
	Vtx v;


	Ptr<CMesh> pMesh = nullptr;

	// ==============
	// PointMesh 생성
	// ==============
	v.vPos = Vec3(0.f, 0.f, 0.f);
	v.vUV = Vec2(0.f, 0.f);
	v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);

	UINT idx = 0;

	pMesh = new CMesh(true);
	pMesh->Create(&v, 1, &idx, 1);
	AddRes(L"PointMesh", pMesh);


	// =============
	// RectMesh 생성
	// =============	
	// 0 --- 1 
	// |  \  |
	// 3 --- 2
	v.vPos = Vec3(-0.5f, 0.5f, 0.f);
	v.vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	v.vUV = Vec2(0.f, 0.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(0.5f, 0.5f, 0.f);
	v.vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	v.vUV = Vec2(1.f, 0.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(0.5f, -0.5f, 0.f);
	v.vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	v.vUV = Vec2(1.f, 1.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(-0.5f, -0.5f, 0.f);
	v.vColor = Vec4(0.f, 0.f, 0.f, 1.f);
	v.vUV = Vec2(0.f, 1.f);
	vecVtx.push_back(v);

	vecIdx.push_back(0);
	vecIdx.push_back(2);
	vecIdx.push_back(3);

	vecIdx.push_back(0);
	vecIdx.push_back(1);
	vecIdx.push_back(2);

	pMesh = new CMesh(true);
	pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	AddRes(L"RectMesh", pMesh); 

	vecIdx.clear();
	vecIdx.push_back(0);
	vecIdx.push_back(1);
	vecIdx.push_back(2);
	vecIdx.push_back(3);
	vecIdx.push_back(0);

	pMesh = new CMesh;
	pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	AddRes(L"RectMesh_Debug", pMesh);

	vecVtx.clear();
	vecIdx.clear();

	// ===========
	// Circle Mesh
	// ===========
	//      3 
	//   4     2
	//  5 --0-- 1	
	// 반지름
	float fRadius = 0.5f;

	// 등분
	UINT Slice = 40;
	// 원의 지름 / 등분 = 각도(theta)
	float fTheta = XM_2PI / (float)Slice;

	// 중심점
	v.vPos = Vec3(0.f, 0.f, 0.f);
	v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	v.vUV = Vec2(0.5f, 0.5f);
	vecVtx.push_back(v);

	// 정점 위치 지정
	for (UINT i = 0; i < Slice; ++i)
	{
		v.vPos = Vec3(fRadius * cosf(fTheta * (float)i), fRadius * sinf(fTheta * (float)i), 0.f);
		v.vUV = Vec2(v.vPos.x + 0.5f, -v.vPos.y + 0.5f);
		vecVtx.push_back(v);
	}

	// 인덱스 설정
	for (UINT i = 0; i < Slice - 1; ++i)
	{
		vecIdx.push_back(0);
		vecIdx.push_back(i + 2);
		vecIdx.push_back(i + 1);
	}

	// 마지막 삼각형
	vecIdx.push_back(0);
	vecIdx.push_back(1);
	vecIdx.push_back(Slice);

	pMesh = new CMesh(true);
	pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	AddRes(L"CircleMesh", pMesh);

	vecIdx.clear();
	for (UINT i = 0; i < Slice; ++i)
	{
		vecIdx.push_back(i + 1);
	}
	vecIdx.push_back(1);

	pMesh = new CMesh(true);
	pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	AddRes(L"CircleMesh_Debug", pMesh);

	vecVtx.clear();
	vecIdx.clear();
}

void CResMgr::CreateDefaultGraphicsShader()
{
	Ptr<CGraphicsShader> pShader = nullptr;

	//// ===============
	//// SetColor Shader
	//// ===============
	//pShader = new CGraphicsShader;
	//pShader->SetKey(L"SetColorShader");
	//pShader->CreateVertexShader(L"shader\\test.fx", "VS_SetColor");
	//pShader->CreatePixelShader(L"shader\\test.fx", "PS_SetColor");

	//pShader->SetRSType(RS_TYPE::CULL_NONE);
	//pShader->SetDSType(DS_TYPE::NO_TEST_NO_WRITE); // 깊이 테스트 진행, 깊이 기록 X
	//pShader->SetBSType(BS_TYPE::DEFAULT);

	//pShader->SetDomain(SHADER_DOMAIN::DOMAIN_TRANSPARENT);

	//AddRes(L"SetColorShader", pShader);


	// ============================
	// Std2DShader
	// RasterizerState      : None
	// BlendState           : Mask
	// DepthStencilState    : Less
	//
	// Parameter
	// g_tex_0              : Output Texture
	// ============================
	pShader = new CGraphicsShader;
	pShader->SetKey(L"Std2DShader");
	pShader->CreateVertexShader(L"shader\\std2d.fx", "VS_Std2D");
	pShader->CreatePixelShader(L"shader\\std2d.fx", "PS_Std2D");

	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::LESS);
	pShader->SetBSType(BS_TYPE::MASK);


	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_MASK);

	// Param
	pShader->AddTexParam(TEX_0, "Output Texture");


	AddRes(pShader->GetKey(), pShader);


	// ======================================
	// Std2DLightShader
	// RasterizerState      : None
	// BlendState           : Mask
	// DepthStencilState    : Less
	//
	// Parameter
	// g_int_1              : NoiseTexture Use
	// g_float_0            : Dissolve Range
	// g_float_1            : Dissolve Thickness
	
	
	// g_tex_0              : Output Texture
	// g_tex_1              : Nomal Texture
	
	// g_tex_7              : SimpleNoise Texture
	
	// g_vec4_0             : Dissolve Color
	// ======================================
	pShader = new CGraphicsShader;
	pShader->SetKey(L"Std2DLightShader");
	pShader->CreateVertexShader(L"shader\\std2d.fx", "VS_Std2DLight");
	pShader->CreatePixelShader(L"shader\\std2d.fx", "PS_Std2DLight");

	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::LESS);
	pShader->SetBSType(BS_TYPE::MASK);

	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_MASK);

	// Param
	pShader->AddScalarParam(INT_1, "Test Int");
	pShader->AddScalarParam(FLOAT_0, "Test Float");
	pShader->AddScalarParam(VEC2_0, "Test Vec2");
	pShader->AddScalarParam(VEC4_0, "Test Vec4");

	pShader->AddTexParam(TEX_0, "Output Texture");
	pShader->AddTexParam(TEX_1, "Output Texture1");
	pShader->AddTexParam(TEX_2, "Output Texture2");


	AddRes(pShader->GetKey(), pShader);


	// =================
	// DebugShape Shader
	// Topology : LineStrip
	// RS_TYPE  : CULL_NONE
	// DS_TYPE  : NO_TEST_NO_WRITE
	// BS_TYPE  : Default
	// g_vec4_0 : OutColor
	// ==================
	pShader = new CGraphicsShader;
	pShader->SetKey(L"DebugShapeShader");
	pShader->CreateVertexShader(L"shader\\debugshape.fx", "VS_DebugShape");
	pShader->CreatePixelShader(L"shader\\debugshape.fx", "PS_DebugShape");

	pShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::NO_TEST_NO_WRITE);
	pShader->SetBSType(BS_TYPE::DEFAULT);

	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_MASK);

	AddRes(pShader->GetKey(), pShader);

	// ============================
	// TileMap Shader
	// 
	// RS_TYPE : CULL_NONE
	// DS_TYPE : LESS
	// BS_TYPE : MASK

	// Parameter
	// g_tex_0 : Tile Atlas Texture
	// ============================
	pShader = new CGraphicsShader;
	pShader->SetKey(L"TileMapShader");
	pShader->CreateVertexShader(L"shader\\tilemap.fx", "VS_TileMap");
	pShader->CreatePixelShader(L"shader\\tilemap.fx", "PS_TileMap");

	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::LESS);
	pShader->SetBSType(BS_TYPE::MASK);

	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_MASK);

	AddRes(pShader->GetKey(), pShader);

	

	// ============================
	// ParticleRender
	// 
	// RS_TYPE : CULL_NONE
	// DS_TYPE : NO_WRITE
	// BS_TYPE : ALPHA_BLEND

	// Parameter
	// g_int_0 : Particle Index
	// 
	// Domain : TRANSPARENT
	// ============================
	pShader = new CGraphicsShader;
	pShader->SetKey(L"ParticleRenderShader");
	pShader->CreateVertexShader(L"shader\\particle_render.fx", "VS_ParticleRender");
	pShader->CreateGeometryShader(L"shader\\particle_render.fx", "GS_ParticleRender");
	pShader->CreatePixelShader(L"shader\\particle_render.fx", "PS_ParticleRender");

	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::NO_WRITE);
	pShader->SetBSType(BS_TYPE::ALPHA_BLEND);
	pShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_TRANSPARENT);

	AddRes(pShader->GetKey(), pShader);

	// ============================
	// GrayShader
	// RS_TYPE : CULL_NONE
	// DS_TYPE : NO_TEST_NO_WRITE
	// BS_TYPE : DEFAULT	 
	// Domain : POSTPROCESS
	// ============================
	pShader = new CGraphicsShader;
	pShader->SetKey(L"GrayShader");
	pShader->CreateVertexShader(L"shader\\postprocess.fx", "VS_GrayShader");
	pShader->CreatePixelShader(L"shader\\postprocess.fx", "PS_GrayShader");
	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::NO_TEST_NO_WRITE);
	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_POSTPROCESS);
	AddRes(pShader->GetKey(), pShader);
	pShader->AddTexParam(TEX_0, "Must Put RTCopyTex");


	// ============================
	// Distortion Shader
	// mesh : RectMesh
	// Domain : DOMAIN_POSTPROCESS
	// g_tex_0 : RederTarget Copy Texture
	// g_tex_1 : Noise Texture
	// ============================
	pShader = new CGraphicsShader;
	pShader->SetKey(L"DistortionShader");
	pShader->CreateVertexShader(L"shader\\postprocess.fx", "VS_Distortion");
	pShader->CreatePixelShader(L"shader\\postprocess.fx", "PS_Distortion");
	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::NO_TEST_NO_WRITE);
	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_POSTPROCESS);
	AddRes(pShader->GetKey(), pShader);
	pShader->AddTexParam(TEX_0, "Must Put RTCopyTex");
	pShader->AddTexParam(TEX_1, "Must Put Any Noise Texture");

	// ============================
	// BlackHole Shader
	// mesh : RectMesh
	// Domain : DOMAIN_POSTPROCESS
	// g_tex_0 : RederTarget Copy Texture
	// ============================
	pShader = new CGraphicsShader;
	pShader->SetKey(L"BlackHoleShader");
	pShader->CreateVertexShader(L"shader\\postprocess.fx", "VS_BlackHole");
	pShader->CreatePixelShader(L"shader\\postprocess.fx", "PS_BlackHole");
	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::NO_TEST_NO_WRITE);
	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_POSTPROCESS);
	AddRes(pShader->GetKey(), pShader);
	pShader->AddTexParam(TEX_0, "Must Put RTCopyTex");
	pShader->AddScalarParam(VEC2_0, "CenterPos");

	// ======================================
	// OutlineShader
	// RasterizerState      : None
	// BlendState           : LESS
	// DepthStencilState    : ALPHA_BLEND
	//
	// Parameter
	
	// g_tex_0              : Output Texture
	// g_tex_1              : Normal Texture

	// g_tex_7              : SimpleNoise Texture

	// g_float_0            : AlphablendPercentage
	// g_vec4_0             : OutlineColor
	// ======================================
	pShader = new CGraphicsShader;
	pShader->SetKey(L"OutlineShader");
	pShader->CreateVertexShader(L"shader\\outline.fx", "VS_Outline");
	pShader->CreatePixelShader(L"shader\\outline.fx", "PS_Outline");

	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::NO_WRITE);
	pShader->SetBSType(BS_TYPE::ALPHA_BLEND);

	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_TRANSPARENT);
	AddRes(pShader->GetKey(), pShader);


	// ======================================
	// PlayerShader
	// RasterizerState      : None
	// BlendState           : Mask
	// DepthStencilState    : Less
	//
	// Parameter
	//#define bAnimUse        g_int_0
	//#define LeftTop         g_vec2_0
	//#define Slice           g_vec2_1
	//#define Offset          g_vec2_2
	//#define BackSize        g_vec2_3
	
	// g_int_1              : NoiseTexture Use
	// g_int_7              : SampleState
	// g_float_0            : Dissolve Range
	// g_float_1            : Dissolve Thickness
	
	
	// g_tex_0              : Output Texture
	// g_tex_1              : Nomal Texture
	
	// g_tex_7              : SimpleNoise Texture
	
	// g_vec4_0             : Dissolve Color
	// g_vec4_1             : CapeColor

	// ======================================
	pShader = new CGraphicsShader;
	pShader->SetKey(L"PlayerShader");
	pShader->CreateVertexShader(L"shader\\PlayerShader.fx", "VS_Player");
	pShader->CreatePixelShader(L"shader\\PlayerShader.fx", "PS_Player");

	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::LESS);
	pShader->SetBSType(BS_TYPE::MASK);

	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_MASK);

	AddRes(pShader->GetKey(), pShader);

	// ======================================
	// PlayerShader_UI
	// RasterizerState      : None
	// BlendState           : Mask
	// DepthStencilState    : Less
	//
	// Parameter
	//#define bAnimUse        g_int_0
	//#define LeftTop         g_vec2_0
	//#define Slice           g_vec2_1
	//#define Offset          g_vec2_2
	//#define BackSize        g_vec2_3

	// g_int_1              : NoiseTexture Use
	// g_int_7              : SampleState
	// g_float_0            : Dissolve Range
	// g_float_1            : Dissolve Thickness


	// g_tex_0              : Output Texture
	// g_tex_1              : Nomal Texture

	// g_tex_7              : SimpleNoise Texture

	// g_vec4_0             : Dissolve Color
	// g_vec4_1             : CapeColor

	// ======================================
	pShader = new CGraphicsShader;
	pShader->SetKey(L"PlayerShader_UI");
	pShader->CreateVertexShader(L"shader\\PlayerShader_UI.fx", "VS_Player");
	pShader->CreatePixelShader(L"shader\\PlayerShader_UI.fx", "PS_Player");

	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::LESS);
	pShader->SetBSType(BS_TYPE::MASK);

	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_UI);

	AddRes(pShader->GetKey(), pShader);

	// ======================================
	// AlphaBlendShader
	// RasterizerState      : None
	// BlendState           : LESS
	// DepthStencilState    : ALPHA_BLEND
	//
	// Parameter

	// g_int_7              : SampleState
	
	// g_tex_0              : Output Texture
	// g_tex_1              : Nomal Texture
	
	// g_tex_7              : SimpleNoise Texture
	
	// g_float_0            : AlphaBlendPercentage
	// ======================================
	pShader = new CGraphicsShader;
	pShader->SetKey(L"AlphaBlendShader");
	pShader->CreateVertexShader(L"shader\\AlphaBlend.fx", "VS_Alpha");
	pShader->CreatePixelShader(L"shader\\AlphaBlend.fx", "PS_Alpha");

	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::NO_WRITE);
	pShader->SetBSType(BS_TYPE::ALPHA_BLEND);

	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_TRANSPARENT);
	AddRes(pShader->GetKey(), pShader);


	// ======================================
	// SkillShader
	// RasterizerState      : None
	// BlendState           : Mask
	// DepthStencilState    : Less
	//
	// Parameter
	//#define bAnimUse        g_int_0
	//#define LeftTop         g_vec2_0
	//#define Slice           g_vec2_1
	//#define Offset          g_vec2_2
	//#define BackSize        g_vec2_3
	
	// g_int_1              : NoiseTexture Use
	// g_int_7              : SampleState
	
	
	// g_tex_0              : Output Texture
	// g_tex_1              : Nomal Texture
	
	// float_0              : Show Percentage
	// ======================================
	pShader = new CGraphicsShader;
	pShader->SetKey(L"SkillShader");
	pShader->CreateVertexShader(L"shader\\PlayerSkill.fx", "VS_PlayerSkill");
	pShader->CreatePixelShader(L"shader\\PlayerSkill.fx", "PS_PlayerSkill");

	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::LESS);
	pShader->SetBSType(BS_TYPE::MASK);

	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_UI);

	AddRes(pShader->GetKey(), pShader);

	// ============================
	// UIShader
	// RasterizerState      : None
	// BlendState           : Mask
	// DepthStencilState    : Less
	//
	// Parameter
	// g_tex_0              : Output Texture
	// ============================
	pShader = new CGraphicsShader;
	pShader->SetKey(L"UIShader");
	pShader->CreateVertexShader(L"shader\\UI.fx", "VS_UI2D");
	pShader->CreatePixelShader(L"shader\\UI.fx", "PS_UI2D");

	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::LESS);
	pShader->SetBSType(BS_TYPE::MASK);


	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_UI);

	AddRes(pShader->GetKey(), pShader);
}

#include "CSetColorShader.h"

void CResMgr::CreateDefaultComputeShader()
{
	Ptr<CComputeShader> pCS = nullptr;

	//// Texture 색상 변경 쉐이더
	pCS = new CSetColorShader(32, 32, 1);
	pCS->SetKey(L"SetColorCS");
	pCS->CreateComputeShader(L"shader\\setcolor.fx", "CS_SetColor");
	AddRes(pCS->GetKey(), pCS);

	// Particle Update 쉐이더
	pCS = new CParticleUpdateShader(128, 1, 1);
	pCS->SetKey(L"ParticleUpdateCS");
	pCS->CreateComputeShader(L"shader\\particle_update.fx", "CS_ParticleUpdate");
	AddRes(pCS->GetKey(), pCS);

}

void CResMgr::CreateDefaultMaterial()
{
	Ptr<CMaterial> pMtrl = nullptr;

	//// Test Material
	//pMtrl = new CMaterial;
	//pMtrl->SetShader(FindRes<CGraphicsShader>(L"TestShader"));
	//AddRes(L"TestMtrl", pMtrl);

	//// Std2D Material
	//pMtrl = new CMaterial(true);
	//pMtrl->SetShader(FindRes<CGraphicsShader>(L"Std2DShader"));
	//AddRes(L"Std2DMtrl", pMtrl);

	//// Std2DAnim Material
	//pMtrl = new CMaterial(true);
	//pMtrl->SetShader(FindRes<CGraphicsShader>(L"Std2DShader"));
	//AddRes(L"Std2DAnimMtrl", pMtrl);

	//// Std2DLight Material
	//pMtrl = new CMaterial(true);
	//pMtrl->SetShader(FindRes<CGraphicsShader>(L"Std2DLightShader"));
	//AddRes(L"Std2DLightMtrl", pMtrl);


	//// Std2DLightAnim Material
	//pMtrl = new CMaterial(true);
	//pMtrl->SetShader(FindRes<CGraphicsShader>(L"Std2DLightShader"));
	//AddRes(L"Std2DAnimLightMtrl", pMtrl);

	//// DebugShape Material
	//pMtrl = new CMaterial(true);
	//pMtrl->SetShader(FindRes<CGraphicsShader>(L"DebugShapeShader"));
	//AddRes(L"DebugShapeMtrl", pMtrl);

	//// TileMap Material
	//pMtrl = new CMaterial(true);
	//pMtrl->SetShader(FindRes<CGraphicsShader>(L"TileMapShader"));
	//AddRes(L"TileMapMtrl", pMtrl);


	//// Particle Render Material
	//pMtrl = new CMaterial(true);
	//pMtrl->SetShader(FindRes<CGraphicsShader>(L"ParticleRenderShader"));
	//AddRes(L"ParticleRenderMtrl", pMtrl);



}


void CResMgr::LoadDefaultTexture()
{
	//Load<CTexture>(L"texture\\Fighter.bmp", L"texture\\Fighter.bmp");
	//Load<CTexture>(L"SmokeTex", L"texture\\smokeparticle.png");
	//Load<CTexture>(L"texture\\Character.png", L"texture\\Character.png");

	//Load<CTexture>(L"texture\\TILE.bmp", L"texture\\TILE.bmp");
	//Load<CTexture>(L"texture\\link.png", L"texture\\link.png");

	//// NoiseTexture
	//Load<CTexture>(L"texture\\Noise\\noise_01.png", L"texture\\Noise\\noise_01.png");
	//Load<CTexture>(L"texture\\Noise\\noise_02.png", L"texture\\Noise\\noise_02.png");
	//Load<CTexture>(L"texture\\Noise\\noise_03.jpg", L"texture\\Noise\\noise_03.jpg");

	//Load<CTexture>(L"texture\\simplenoise.jpg", L"texture\\simplenoise.jpg");
	//Load<CTexture>(L"texture\\simplenoise2.png", L"texture\\simplenoise2.png");
}

void CResMgr::CreateDefaultPrefab()
{
	/*CGameObject* pMissile = new CGameObject;

	pMissile->AddComponent(new CTransform);
	pMissile->AddComponent(new CMeshRender);
	pMissile->AddComponent(new CMissileScript);

	pMissile->Transform()->SetRelativeScale(Vec3(50.f, 50.f, 50.f));

	pMissile->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pMissile->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std2DMtrl"));

	CMissileScript* pMissileScript = pMissile->GetScript<CMissileScript>();
	if (nullptr != pMissileScript)
		pMissileScript->SetSpeed(500.f);

	Ptr<CPrefab> MissilePrefab = new CPrefab;
	MissilePrefab->RegisterProtoObject(pMissile);
	AddRes<CPrefab>(L"MissilePrefab", MissilePrefab);*/
}

Ptr<CTexture> CResMgr::CreateTexture(const wstring& _strKey, UINT _Width, UINT _Height
	, DXGI_FORMAT _pixelformat, UINT _BindFlag, D3D11_USAGE _Usage)
{
	Ptr<CTexture> pTex = FindRes<CTexture>(_strKey);

	assert(nullptr == pTex);

	pTex = new CTexture(true);
	if (FAILED(pTex->Create(_Width, _Height, _pixelformat, _BindFlag, _Usage)))
	{
		assert(nullptr);
	}

	AddRes<CTexture>(_strKey, pTex);

	return pTex;
}

Ptr<CTexture> CResMgr::CreateTexture(const wstring& _strKey, ComPtr<ID3D11Texture2D> _Tex2D)
{
	Ptr<CTexture> pTex = FindRes<CTexture>(_strKey);

	assert(nullptr == pTex);

	pTex = new CTexture(true);
	if (FAILED(pTex->Create(_Tex2D)))
	{
		assert(nullptr);
	}

	AddRes<CTexture>(_strKey, pTex);

	return pTex;
}

void CResMgr::DeleteRes(RES_TYPE _type, const wstring& _strKey)
{
	map<wstring, Ptr<CRes>>::iterator iter = m_arrRes[(UINT)_type].find(_strKey);

	assert(!(iter == m_arrRes[(UINT)_type].end()));

	m_arrRes[(UINT)_type].erase(iter);

	m_Changed = true;
}