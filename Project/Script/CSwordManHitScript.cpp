#include "pch.h"
#include "CSwordManHitScript.h"
#include "CSwordManScript.h"
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim2D.h>


CSwordManHitScript::CSwordManHitScript()
	:CScript((UINT)SCRIPT_TYPE::SWORDMANHITSCRIPT)
{
	SetActive(false);
}

CSwordManHitScript::~CSwordManHitScript()
{
}


void CSwordManHitScript::begin()
{
	
}

void CSwordManHitScript::tick()
{
	if (!IsActive()) return;
	if (Animator2D()->GetCurAnim()->IsFinish()) {
		Animator2D()->GetCurAnim()->Reset();
		ChangeState((UINT)SCRIPT_TYPE::SWORDMANIDLESCRIPT, false);
	}
}

void CSwordManHitScript::Enter()
{
	CSwordManScript* SwordManMainScript = GetOwner()->GetScript<CSwordManScript>();
	SwordManMainScript->SetHit(true);
	int CurHp = SwordManMainScript->GetSwordManHP();
	SwordManMainScript->SetSwordManHp(--CurHp);
	if (SwordManMainScript->GetSwordManDir() & DIR_LEFT) {
		float m_fDegree = 0.f / 180.f * XM_PI;
		Transform()->SetRelativeRot(Vec3(0.f, m_fDegree, 0.f));
		Animator2D()->Play(L"SwordMan_Hit_Left", false);
	}
	else {
		float m_fDegree = 180.f / 180.f * XM_PI;
		Transform()->SetRelativeRot(Vec3(0.f, m_fDegree, 0.f));
		Animator2D()->Play(L"SwordMan_Hit_Left", false);
	}
	srand(time(NULL));
	if (rand() % 5 == 0) {
		Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\EnemyHurt0.wav");
		pSound->Play(1, 0.2f, true);
	}
	else if (rand() % 5 == 1) {
		Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\EnemyHurt1.wav");
		pSound->Play(1, 0.2f, true);
	}
	else if (rand() % 5 == 2) {
		Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\EnemyHurt2.wav");
		pSound->Play(1, 0.2f, true);
	}
	else if (rand() % 5 == 3) {
		Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\EnemyHurt3.wav");
		pSound->Play(1, 0.2f, true);
	}
	else {
		Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\EnemyHurt4.wav");
		pSound->Play(1, 0.2f, true);
	}

	Ptr<CPrefab> HitEffectPrefab = CResMgr::GetInst()->FindRes<CPrefab>(L"prefab\\HitEffect.prefab");
	CGameObject* HitEffect = HitEffectPrefab->Instantiate();
	Vec3 MonPos = Transform()->GetRelativePos();
	SpawnGameObject(HitEffect, Vec3(MonPos.x, MonPos.y, MonPos.z - 10), L"Default");
}

void CSwordManHitScript::Exit()
{
	CSwordManScript* SwordManMainScript = GetOwner()->GetScript<CSwordManScript>();
	SwordManMainScript->SetHit(false);
}

