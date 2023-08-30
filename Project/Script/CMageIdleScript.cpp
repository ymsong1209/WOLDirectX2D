#include "pch.h"
#include "CMageIdleScript.h"
#include <Engine/CResMgr.h>
#include "CMageScript.h"
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

CMageIdleScript::CMageIdleScript()
	: CScript((UINT)SCRIPT_TYPE::MAGEIDLESCRIPT)
	, m_fAttackCoolTime(0.f)
{
	SetActive(false);
}

CMageIdleScript::~CMageIdleScript()
{
}

void CMageIdleScript::begin()
{
}

void CMageIdleScript::tick()
{
	if (!IsActive()) return;
	CMageScript* MageMainScript = GetOwner()->GetScript<CMageScript>();
	m_fAttackCoolTime += DT;
	CGameObject* Player = CLevelMgr::GetInst()->FindParentObjectByName(L"Player");
	Vec3 PlayerPos = Player->Transform()->GetRelativePos();
	Vec3 CurPos = Transform()->GetRelativePos();

	if (CurPos.x < PlayerPos.x) {
		if (MageMainScript->GetMageDir() == DIR_LEFT) {
			MageMainScript->SetMageDir(DIR_RIGHT);
			float m_fDegree = 180.f / 180.f * XM_PI;
			Transform()->SetRelativeRot(Vec3(0.f, m_fDegree, 0.f));
			Animator2D()->Play(L"Wizard_Idle_Left", true);
		}
	}
	else {
		if (MageMainScript->GetMageDir() == DIR_RIGHT) {
			MageMainScript->SetMageDir(DIR_LEFT);
			float m_fDegree = 0.f / 180.f * XM_PI;
			Transform()->SetRelativeRot(Vec3(0.f, m_fDegree, 0.f));
			Animator2D()->Play(L"Wizard_Idle_Left", true);
		}
	}

	if (m_fAttackCoolTime > 5.0f) {
		ChangeState((UINT)SCRIPT_TYPE::MAGEATTACKSCRIPT, false);
		m_fAttackCoolTime = 0.f;
	}
}

void CMageIdleScript::Enter()
{
	m_fAttackCoolTime = 0.f;
	CMageScript* MageMainScript = GetOwner()->GetScript<CMageScript>();
	Vec3 Pos = Transform()->GetRelativePos();
	Transform()->SetRelativePos(Vec3(Pos.x, Pos.y, 350.f));

	if (MageMainScript->GetMageDir() & DIR_LEFT) {
		float m_fDegree = 0.f / 180.f * XM_PI;
		Transform()->SetRelativeRot(Vec3(0.f, m_fDegree, 0.f));
		Animator2D()->Play(L"Wizard_Idle_Left", true);
	}
	else {
		float m_fDegree = 180.f / 180.f * XM_PI;
		Transform()->SetRelativeRot(Vec3(0.f, m_fDegree, 0.f));
		Animator2D()->Play(L"Wizard_Idle_Left", true);
	}
}

void CMageIdleScript::Exit()
{
}



