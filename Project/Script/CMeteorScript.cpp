#include "pch.h"
#include "CMeteorScript.h"
#include "CMeteorRingScript.h"
#include "CMeteorSmokeParticleScript.h"
#include "CMeteorFloorCrackScript.h"
#include "CMeteorDamageZoneScript.h"
#include "CMeteorSpawnCircleScript.h"
#include "CPlayerCameraScript.h"

CMeteorScript::CMeteorScript()
	: CScript((UINT)SCRIPT_TYPE::METEORSCRIPT)
	, m_vLandPos(0.f,0.f,0.f)
	, m_bMeteorRingSpawn(false)
{
}

CMeteorScript::~CMeteorScript()
{
}


void CMeteorScript::begin()
{
	/*m_vFallStartPos = Vec3(m_vLandPos.x - 800.f - (Transform()->GetRelativeScale().y / 2.f * cos(38.f / 180.f * XM_PI)),
						  m_vLandPos.y + 800.f * tan(38.f / 180.f * XM_PI) + (Transform()->GetRelativeScale().y / 2.f * sin(38.f / 180.f * XM_PI))
						, 1.f);*/
	m_vFallStartPos = Vec3(		m_vLandPos.x - 800.f
							,	m_vLandPos.y + 800.f * tan(38.f / 180.f * XM_PI)
							,	1.f);
	Transform()->SetRelativePos(m_vFallStartPos);
	Animator2D()->SetSamplerState(1);
	Animator2D()->LoadAnim(L"animation\\particle\\Meteor.anim");
	Animator2D()->Play(L"Meteor", false);
	Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\FlameChargeUp.wav");
	pSound->Play(1, 0.2f, true);
}

void CMeteorScript::tick()
{
	m_vFallStartPos.x += DT * 500;
	m_vFallStartPos.y -= DT * 500 * tan(38.f / 180.f * XM_PI);
	m_fFallTime += DT;
	Transform()->SetRelativePos(Vec3(m_vFallStartPos.x, m_vFallStartPos.y, 200.f));
	if (m_vFallStartPos.x + (Transform()->GetRelativeScale().y / 2.f * cos(38.f / 180.f * XM_PI)) > m_vLandPos.x) {
		DestroyObject(GetOwner());
		if (GetOwner()->IsDead()) return;
		Ptr<CPrefab> SmokePrefab = CResMgr::GetInst()->FindRes<CPrefab>(L"prefab\\SmokeParticle.prefab");
		CGameObject* Smoke = SmokePrefab->Instantiate();
		Smoke->SetName(L"MeteorSmoke");
		Smoke->AddComponent(new CMeteorSmokeParticleScript);
		SpawnGameObject(Smoke, Vec3(m_vLandPos.x + 30.f, m_vLandPos.y + 30.f, 20.f), L"Default");

		CGameObject* FloorCrack = new CGameObject;
		FloorCrack->SetName(L"FloorCrack");
		FloorCrack->AddComponent(new CTransform);
		FloorCrack->AddComponent(new CMeshRender);
		FloorCrack->AddComponent(new CAnimator2D);
		FloorCrack->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
		FloorCrack->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"material\\Std2DLightMtrl.mtrl"));
		FloorCrack->MeshRender()->GetDynamicMaterial();
		FloorCrack->AddComponent(new CMeteorFloorCrackScript);
		FloorCrack->Transform()->SetRelativeScale(Vec3(200.f, 100.f, 1.f));
		SpawnGameObject(FloorCrack,Vec3(m_vLandPos.x, m_vLandPos.y, 30.f), L"Default");

		CGameObject* zone = new CGameObject;
		zone->SetName(L"MeteorDamageZone");
		zone->AddComponent(new CTransform);
		zone->AddComponent(new CCollider2D);
		zone->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::CIRCLE);
		zone->Transform()->SetRelativePos(m_vFallStartPos);
		zone->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		zone->Collider2D()->SetAbsolute(false);
		zone->Collider2D()->SetOffsetScale(Vec2(1.f, 1.f));
		zone->SetLifeSpan(1.0f);
		zone->AddComponent(new CMeteorDamageZoneScript);
		SpawnGameObject(zone, m_vLandPos, L"PlayerProjectile");


		DestroyObject(m_pSpawnCircle);

		CGameObject* Camera = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"MainCamera");
		CPlayerCameraScript* CameraScript = Camera->GetScript<CPlayerCameraScript>();
		CameraScript->CameraShake(1.0f, 10.0f, 100.f);

		Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\Explosion2.wav");
		pSound->Play(1, 0.2f, true);
	}
	Vec3 CurPos = Transform()->GetRelativePos();
	if (m_fFallTime > 1.0f && m_bMeteorRingSpawn == false) {
		m_bMeteorRingSpawn = true;
		CGameObject* Meteorring = new CGameObject;
		Meteorring->SetName(L"MeteorRing");
		Meteorring->AddComponent(Transform()->Clone());
		Meteorring->AddComponent(new CMeshRender);
		Meteorring->AddComponent(new CAnimator2D);
		Meteorring->Transform()->SetRelativeScale(Vec3(500.f, 200.f, 1.f));
		Meteorring->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
		Meteorring->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"material\\Std2DLightMtrl.mtrl"));
		Meteorring->MeshRender()->GetDynamicMaterial();
	
		Meteorring->AddComponent(new CMeteorRingScript);
		SpawnGameObject(Meteorring, CurPos, L"Default");
	
	}
}


