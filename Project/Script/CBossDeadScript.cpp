#include "pch.h"
#include "CBossDeadScript.h"
#include "CBossScript.h"
#include "CBossWaveScript.h"
#include "CBossUIScript.h"
#include "CBossHPScript.h"
#include "CPortalSummonEffectScript.h"
#include "CPortalParticleScript.h"
#include "CMapPortalScript.h"

CBossDeadScript::CBossDeadScript()
	:CScript((UINT)SCRIPT_TYPE::BOSSDEADSCRIPT)
	,m_bSummoned(false)
{
	SetActive(false);
}

CBossDeadScript::~CBossDeadScript()
{
}

void CBossDeadScript::begin()
{
}

void CBossDeadScript::tick()
{
	if (!IsActive()) return;
	m_fTime += DT;

	if (m_fTime > 4.0f) {
		Transform()->SetRelativePos(Vec3(3000.f, 300.f, 0.f));
		CGameObject* BossUI = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"BossUI");
		CBossUIScript* UIScript = BossUI->GetScript<CBossUIScript>();
		UIScript->Deactivate();

		CGameObject* BossHP = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"BossHP");
		CBossHPScript* HPScript = BossHP->GetScript<CBossHPScript>();
		HPScript->Deactivate();

		if (m_bSummoned == false) {
			CGameObject* Teleport = CResMgr::GetInst()->FindRes<CPrefab>(L"prefab\\MapPortal.prefab")->Instantiate();
			CMapPortalScript* TeleportScript = Teleport->GetScript<CMapPortalScript>();
			TeleportScript->SetPortalNum(4);
			SpawnGameObject(Teleport, Vec3(0.f, 0.f, 380.f), L"Portal");

			CGameObject* PortalParticle = CResMgr::GetInst()->FindRes<CPrefab>(L"prefab\\PortalParticle.prefab")->Instantiate();
			SpawnGameObject(PortalParticle, Vec3(0.f, 50.f, 380.f), L"Portal");

			CGameObject* PortalSummonEffect = CResMgr::GetInst()->FindRes<CPrefab>(L"prefab\\PortalSummonEffect.prefab")->Instantiate();
			SpawnGameObject(PortalSummonEffect, Vec3(0.f, 50.f, 290.f), L"Portal");
			m_bSummoned = true;
		}
		
		
	}
}

void CBossDeadScript::Enter()
{
	RigidBody()->SetVelocity(Vec2(0.f, 0.f));
	Vec3 Pos = Transform()->GetRelativePos();
	Transform()->SetRelativePos(Vec3(0.f, 0.f, Pos.z));
	Animator2D()->Play(L"Boss_Down", true);

	CGameObject* BossWave = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"BossWave");
	CBossWaveScript* WaveScript = BossWave->GetScript<CBossWaveScript>();
	WaveScript->Deactivate();
}

void CBossDeadScript::Exit()
{
}


