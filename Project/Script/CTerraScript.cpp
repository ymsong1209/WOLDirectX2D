#include "pch.h"
#include "CTerraScript.h"
#include "CTowerScript.h"
#include "CBossLeapAttackScript.h"

CTerraScript::CTerraScript()
	:CScript((UINT)SCRIPT_TYPE::TERRASCRIPT)
	,m_fTime(0.f)
	,m_fAccTime(0.f)
{
}

CTerraScript::~CTerraScript()
{
}


void CTerraScript::begin()
{
	m_vDirection = Vec2(m_vPlayerPos.x - m_vBossPos.x, m_vPlayerPos.y - m_vBossPos.y);
	m_vDirection.Normalize();
	Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\EarthLoop.wav");
	m_pTerraSound = pSound.Get();
	m_pTerraSound->Play(0, 0.2, true);
}

void CTerraScript::tick()
{
	m_fTime += DT;
	m_fAccTime += DT;
	if (m_fAccTime > 5.f) {
		m_pTerraSound->Stop();
		DestroyObject(GetOwner());
	}
	if (m_fTime > 0.15f) {
		CGameObject* Tower = new CGameObject;
		Tower->SetName(L"Tower");
		Tower->AddComponent(new CTransform);
		Tower->AddComponent(new CMeshRender);
		Tower->AddComponent(new CAnimator2D);
		Tower->AddComponent(new CCollider2D);
		Tower->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
		Tower->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"material\\Std2DLightMtrl.mtrl"));
		Tower->Transform()->SetRelativePos(Vec3(m_vBossPos.x + m_fAccTime * 300.f * m_vDirection.x,
												m_vBossPos.y + m_fAccTime * 300.f * m_vDirection.y,
												m_vBossPos.z));
		Tower->Transform()->SetRelativeScale(Vec3(80.f, 150.f, 1.f));
		Tower->Collider2D()->SetAbsolute(false);
		Tower->Collider2D()->SetOffsetScale(Vec2(1.f, 1.f));
		Tower->AddComponent(new CTowerScript);
		SpawnGameObject(Tower, Tower->Transform()->GetRelativePos(), L"MonsterProjectile");

		CGameObject* FloorCrack = new CGameObject;
		FloorCrack->SetName(L"FloorCrack");
		FloorCrack->AddComponent(new CTransform);
		FloorCrack->AddComponent(new CMeshRender);
		FloorCrack->AddComponent(new CAnimator2D);
		FloorCrack->AddComponent(new CBossLeapAttackScript);
		FloorCrack->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
		FloorCrack->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"material\\Std2DLightMtrl.mtrl"));
		FloorCrack->Transform()->SetRelativeScale(80.f, 80.f, 1.f);
		FloorCrack->Animator2D()->SetSamplerState(1);
		Vec3 TowerPos = Tower->Transform()->GetRelativePos();
		
		SpawnGameObject(FloorCrack, Vec3(TowerPos.x, TowerPos.y - 75.f, TowerPos.z + 10.f), L"Default");
	
		
		m_fTime = 0.f;
	}
}