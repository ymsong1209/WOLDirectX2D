#include "pch.h"
#include "CGhoulHitScript.h"
#include "CGhoulScript.h"
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim2D.h>


CGhoulHitScript::CGhoulHitScript()
	:CScript((UINT)SCRIPT_TYPE::GHOULHITSCRIPT)
{
	SetActive(false);
}

CGhoulHitScript::~CGhoulHitScript()
{
}


void CGhoulHitScript::begin()
{

}

void CGhoulHitScript::tick()
{
	if (!IsActive()) return;
	if (Animator2D()->GetCurAnim()->IsFinish()) {
		Animator2D()->GetCurAnim()->Reset();
		ChangeState((UINT)SCRIPT_TYPE::GHOULIDLESCRIPT, false);
	}
}

void CGhoulHitScript::Enter()
{
	CGhoulScript* GhoulMainScript = GetOwner()->GetScript<CGhoulScript>();
	GhoulMainScript->SetHit(true);
	int CurHp = GhoulMainScript->GetGhoulHP();
	GhoulMainScript->SetGhoulHp(--CurHp);
	if (GhoulMainScript->GetGhoulDir() & DIR_LEFT) {
		float m_fDegree = 180.f / 180.f * XM_PI;
		Transform()->SetRelativeRot(Vec3(0.f, m_fDegree, 0.f));
		Animator2D()->Play(L"GhoulHit_Right", false);
	}
	else {
		float m_fDegree = 0.f / 180.f * XM_PI;
		Transform()->SetRelativeRot(Vec3(0.f, m_fDegree, 0.f));
		Animator2D()->Play(L"GhoulHit_Right", false);
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
	else{
		Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\EnemyHurt4.wav");
		pSound->Play(1, 0.2f, true);
	}
	Ptr<CPrefab> HitEffectPrefab = CResMgr::GetInst()->FindRes<CPrefab>(L"prefab\\HitEffect.prefab");
	CGameObject* HitEffect = HitEffectPrefab->Instantiate();
	Vec3 MonPos = Transform()->GetRelativePos();
	SpawnGameObject(HitEffect, Vec3(MonPos.x, MonPos.y, MonPos.z - 10), L"Default");
}

void CGhoulHitScript::Exit()
{
	CGhoulScript* GhoulMainScript = GetOwner()->GetScript<CGhoulScript>();
	GhoulMainScript->SetHit(false);
}

