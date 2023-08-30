#include "pch.h"
#include "CGhoulIdleScript.h"
#include "CGhoulScript.h"
#include "CPlayerScript.h"
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CAstarMgr.h>

CGhoulIdleScript::CGhoulIdleScript()
	: CScript((UINT)SCRIPT_TYPE::GHOULIDLESCRIPT)
{
	SetActive(false);
}

CGhoulIdleScript::~CGhoulIdleScript()
{
}

void CGhoulIdleScript::begin()
{
}

void CGhoulIdleScript::tick()
{
	if (!IsActive()) return;
	CGameObject* Player = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"Player");
	CPlayerScript* PlayerMainScript = Player->GetScript<CPlayerScript>();

	Vec3 PlayerPos = Player->Transform()->GetRelativePos();
	//Player의 실제 Pos는 발바닥에 있음
	PlayerPos = Vec3(PlayerPos.x, PlayerPos.y - 50.f, PlayerPos.z);
	Vec3 CurPos = Transform()->GetRelativePos();
	CurPos = Vec3(CurPos.x, CurPos.y - 85.f, CurPos.z);
	m_fTime += DT;
	if (m_fTime > 1.f) {
		Vec2 DestPos = CAstarMgr::GetInst()->SetFind(CurPos, PlayerPos);
		if (DestPos != Vec2(-1.f, -1.f) && PlayerMainScript->IsPlayerOnGround()) {
			ChangeState((UINT)SCRIPT_TYPE::GHOULTRACESCRIPT);
		}
	}
}

void CGhoulIdleScript::Enter()
{
	m_fTime = 0.f;
	CGhoulScript* GhoulMainScript = GetOwner()->GetScript<CGhoulScript>();
	GhoulMainScript->SetGhoulDir(DIR_RIGHT);
	if (GhoulMainScript->GetGhoulDir() & DIR_LEFT) {
		float m_fDegree = 0.f / 180.f * XM_PI;
		Transform()->SetRelativeRot(Vec3(0.f, m_fDegree, 0.f));
		Animator2D()->Play(L"GhoulIdle_Left", true);
	}
	else {
		float m_fDegree = 180.f / 180.f * XM_PI;
		Transform()->SetRelativeRot(Vec3(0.f, m_fDegree, 0.f));
		Animator2D()->Play(L"GhoulIdle_Left", true);
	}

}

void CGhoulIdleScript::Exit()
{
}


