#include "pch.h"
#include "TestBoss.h"
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>
#include <Engine/CGameObject.h>
#include <Engine/components.h>
#include <Engine/CResMgr.h>
#include <Engine/CCollisionMgr.h>
#include <Engine/CDevice.h>

#include <Engine/CAnim2D.h>

#include <Script/CPlayerCameraScript.h>
#include <Script/CMonsterScript.h>
#include <Script/CFireParticleScript.h>
#include <Script/CSnowParticleScript.h>
#include <Script/CRainParticleScript.h>
#include <Script/CExplosionParticleScript.h>

#include <Script/CMousePointerScript.h>


#include <Script/CPlayerScript.h>
#include <Script/CPlayerAttackScript.h>
#include <Script/CPlayerIdleScript.h>
#include <Script/CPlayerWalkScript.h>
#include <Script/CPlayerDashScript.h>
#include <Script/CPlayerDashStopScript.h>
#include <Script/CPlayerSlideScript.h>
#include <Script/CPlayerFallScript.h>
#include <Script/CPlayerHitBoxScript.h>
#include <Script/CPlayerDeadScript.h>
#include <Script/CPlayerHitScript.h>

#include <Script/CBossFloorScript.h>
#include <Script/CBossPitScript.h>
#include <Script/CBossWallScript.h>

#include <Engine/CSetColorShader.h>

#include <Script/CSwordManDeadScript.h>
#include <Script/CSwordManHitBoxScript.h>
#include <Script/CSwordManHitScript.h>
#include <Script/CSwordManIdleScript.h>
#include <Script/CSwordManScript.h>
#include <Script/CSwordManTraceScript.h>
#include <Script/CSwordManAttackScript.h>

#include <Script/CMapScript.h>

#include "CLevelSaveLoad.h"
#include <Engine/CEventMgr.h>

void CreateTestBossLevel()
{
	//return;

	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	//pCurLevel->SetName(L"TestLevel");
	pCurLevel->ChangeState(LEVEL_STATE::STOP);

	//// 텍스쳐 색칠하기
	//// 1. CreateTexture
	//Ptr<CTexture> pCreateTex = CResMgr::GetInst()->CreateTexture(
	//	L"SampleTexture"
	//	, CDevice::GetInst()->GetRenderResolution().x, CDevice::GetInst()->GetRenderResolution().y
	//	, DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM
	//	, D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE
	//	, D3D11_USAGE_DEFAULT);

	//// 2. ComputeShader 로 텍스쳐 색 변경하기
	//Ptr<CSetColorShader> pCS = (CSetColorShader*)CResMgr::GetInst()->FindRes<CComputeShader>(L"SetColorCS").Get();
	//pCS->SetTargetTexture(pCreateTex);
	//pCS->SetColor(Vec3(0.f, 1.f, 1.f));
	//pCS->Execute();


	// Layer 이름설정
	pCurLevel->GetLayer(0)->SetName(L"Default");
	pCurLevel->GetLayer(1)->SetName(L"Tile");
	pCurLevel->GetLayer(2)->SetName(L"Player");
	pCurLevel->GetLayer(3)->SetName(L"Monster");
	pCurLevel->GetLayer(4)->SetName(L"PlayerProjectile");
	pCurLevel->GetLayer(5)->SetName(L"MonsterProjectile");
	pCurLevel->GetLayer(6)->SetName(L"Pit");
	pCurLevel->GetLayer(7)->SetName(L"PlayerHitBox");
	pCurLevel->GetLayer(8)->SetName(L"Wall");
	pCurLevel->GetLayer(9)->SetName(L"PitWall");
	pCurLevel->GetLayer(10)->SetName(L"MonsterHitBox");
	pCurLevel->GetLayer(11)->SetName(L"Wave");



	// Main Camera Object 생성
	CGameObject* pMainCam = new CGameObject;
	pMainCam->SetName(L"MainCamera");

	pMainCam->AddComponent(new CTransform);
	pMainCam->AddComponent(new CCamera);
	pMainCam->AddComponent(new CPlayerCameraScript);


	pMainCam->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
	pMainCam->Camera()->SetCameraIndex(0);		// MainCamera 로 설정
	pMainCam->Camera()->SetLayerMaskAll(true);	// 모든 레이어 체크


	SpawnGameObject(pMainCam, Vec3(0.f, 0.f, 0.f), 0);



	//CGameObject* pMainCam2 = new CGameObject;
	//pMainCam2->SetName(L"MainCamera2");

	//pMainCam2->AddComponent(new CTransform);
	//pMainCam2->AddComponent(new CCamera);


	//pMainCam2->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
	//pMainCam2->Camera()->SetCameraIndex(1);		// MainCamera 로 설정
	//pMainCam2->Camera()->SetLayerMaskAll(true);	// 모든 레이어 체크


	//SpawnGameObject(pMainCam2, Vec3(100.f, 0.f, 0.f), 0);


	// 광원 추가
	CGameObject* pLightObj = new CGameObject;
	pLightObj->SetName(L"Point Light");

	pLightObj->AddComponent(new CTransform);
	pLightObj->AddComponent(new CLight2D);

	pLightObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 0.f));
	//pLightObj->Transform()->SetRelativeRot(Vec3(0.f, 0.f, XM_PI / 2.f));

	pLightObj->Light2D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	pLightObj->Light2D()->SetLightDiffuse(Vec3(1.f, 1.f, 1.f));
	pLightObj->Light2D()->SetRadius(1000.f);
	pLightObj->Light2D()->SetAngle(45.f);

	SpawnGameObject(pLightObj, Vec3(0.f, 0.f, 0.f), 0);



	// 오브젝트 생성
	CGameObject* pParent = new CGameObject;
	pParent->SetName(L"Player");
	pParent->AddComponent(new CTransform);
	pParent->AddComponent(new CMeshRender);
	pParent->AddComponent(new CCollider2D);
	pParent->AddComponent(new CAnimator2D);
	pParent->AddComponent(new CFSM);
	pParent->AddComponent(new CRigidBody);
	pParent->AddComponent(new CPlayerScript);
	pParent->AddComponent(new CPlayerIdleScript);
	pParent->AddComponent(new CPlayerWalkScript);
	pParent->AddComponent(new CPlayerAttackScript);
	pParent->AddComponent(new CPlayerDashScript);
	pParent->AddComponent(new CPlayerDashStopScript);
	pParent->AddComponent(new CPlayerSlideScript);
	pParent->AddComponent(new CPlayerFallScript);
	pParent->AddComponent(new CPlayerDeadScript);
	pParent->AddComponent(new CPlayerHitScript);


	Ptr<CTexture> NoiseTex = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\simplenoise.jpg");

	pParent->Transform()->SetRelativePos(Vec3(100.f, 100.f, 450.f));
	pParent->Transform()->SetRelativeScale(Vec3(150.f, 150.f, 1.f));

	pParent->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pParent->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"material\\PlayerMtrl.mtrl"));

	pParent->MeshRender()->GetMaterial()->SetTexParam(TEX_7, NoiseTex);

	pParent->Collider2D()->SetAbsolute(true);
	pParent->Collider2D()->SetOffsetPos(Vec2(6.f, -50.f));
	pParent->Collider2D()->SetOffsetScale(Vec2(2.f, 2.f));
	pParent->Animator2D()->SetSamplerState(1);
	SpawnGameObject(pParent, Vec3(0.f, 0.f, 250.f), L"Player");


	CGameObject* pHitBox = new CGameObject;

	pHitBox->SetName(L"PlayerHitBox");
	pHitBox->AddComponent(new CTransform);
	pHitBox->AddComponent(new CCollider2D);

	pHitBox->Transform()->SetAbsolute(false);
	pHitBox->Transform()->SetRelativePos(Vec3(100.f, 100.f, 500.f));
	pHitBox->Transform()->SetRelativeScale(Vec3(150.f, 150.f, 1.f));
	pHitBox->Collider2D()->SetAbsolute(true);
	pHitBox->Collider2D()->SetOffsetPos(Vec2(5.f, 0.f));
	pHitBox->Collider2D()->SetOffsetScale(Vec2(40.f, 100.f));
	pHitBox->AddComponent(new CPlayerHitBoxScript);
	SpawnGameObject(pHitBox, Vec3(0.f, 0.f, 0.f), L"PlayerHitBox");


	
	CGameObject* pMapFloor = new CGameObject;
	pMapFloor->SetName(L"Floor");

	pMapFloor->AddComponent(new CTransform);
	pMapFloor->AddComponent(new CMeshRender);
	pMapFloor->AddComponent(new CBossFloorScript);
	pMapFloor->Transform()->SetRelativePos(Vec3(0.f, 0.f, 300.f));
	pMapFloor->Transform()->SetRelativeScale(Vec3(3200.f, 1920.f, 1.f));
	pMapFloor->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pMapFloor->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"material\\Std2DLightMtrl.mtrl"));
	pMapFloor->MeshRender()->GetDynamicMaterial();
	pMapFloor->MeshRender()->GetMaterial()->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\Map\\bossFloor.png"));
	SpawnGameObject(pMapFloor, Vec3(0.f, 0.f, 300.f), L"Default");


	CGameObject* pMapWall = new CGameObject;
	pMapWall->SetName(L"MapWall");

	pMapWall->AddComponent(new CTransform);
	pMapWall->AddComponent(new CMeshRender);
	pMapWall->AddComponent(new CBossWallScript);
	pMapWall->Transform()->SetRelativePos(Vec3(0.f, 0.f, 400.f));
	pMapWall->Transform()->SetRelativeScale(Vec3(3200.f, 1920.f, 1.f));
	pMapWall->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pMapWall->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"material\\Std2DLightMtrl.mtrl"));
	pMapWall->MeshRender()->GetDynamicMaterial();
	pMapWall->MeshRender()->GetMaterial()->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\Map\\bosswall.png"));
	SpawnGameObject(pMapWall, Vec3(0.f, 0.f, 400.f), L"Default");


	CGameObject* pMapPit = new CGameObject;
	pMapPit->SetName(L"MapPit");

	pMapPit->AddComponent(new CTransform);
	pMapPit->AddComponent(new CMeshRender);
	pMapPit->AddComponent(new CBossPitScript);

	pMapPit->Transform()->SetRelativePos(Vec3(0.f, 0.f, 400.f));
	pMapPit->Transform()->SetRelativeScale(Vec3(3200.f, 1920.f, 1.f));
	pMapPit->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pMapPit->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"material\\Std2DLightMtrl.mtrl"));
	pMapPit->MeshRender()->GetDynamicMaterial();
	pMapPit->MeshRender()->GetMaterial()->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\Map\\bossPit.png"));
	SpawnGameObject(pMapPit, Vec3(0.f, 0.f, 500.f), L"Default");



	// MouseObject
	CGameObject* MousePointer = new CGameObject;
	MousePointer->SetName(L"MousePointer");
	MousePointer->AddComponent(new CTransform);
	MousePointer->AddComponent(new CMeshRender);
	MousePointer->AddComponent(new CMousePointerScript);

	SpawnGameObject(MousePointer, Vec3(0.f, 0.f, 0.f), 0);



	// 충돌 시킬 레이어 짝 지정
	CCollisionMgr::GetInst()->LayerCheck(L"PlayerHitBox", L"MonsterProjectile");
	CCollisionMgr::GetInst()->LayerCheck(L"Player", L"Wall");
	CCollisionMgr::GetInst()->LayerCheck(L"Player", L"Pit");
	CCollisionMgr::GetInst()->LayerCheck(L"Player", L"PitWall");


	CLevel* pLoadedLevel = CLevelSaveLoad::LoadLevel(L"level\\MainMenu.lv");

	tEvent evn = {};
	evn.Type = EVENT_TYPE::LEVEL_CHANGE;
	evn.wParam = (DWORD_PTR)pLoadedLevel;

	CEventMgr::GetInst()->AddEvent(evn);
}
