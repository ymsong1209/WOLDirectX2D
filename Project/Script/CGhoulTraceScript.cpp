#include "pch.h"
#include "CGhoulTraceScript.h"
#include "CGhoulScript.h"
#include <Engine/CAstarMgr.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim2D.h>
#include "CPlayerScript.h"

CGhoulTraceScript::CGhoulTraceScript()
	: CScript((UINT)SCRIPT_TYPE::GHOULTRACESCRIPT)
	, m_iMovingdirection(0)
	, m_fForce(250.f)
{
	SetActive(false);
}

CGhoulTraceScript::~CGhoulTraceScript()
{
}


void CGhoulTraceScript::begin()
{
}

void CGhoulTraceScript::tick()
{
	if (!IsActive()) return;
	CGhoulScript* GhoulMainScript = GetOwner()->GetScript<CGhoulScript>();
	CGameObject* Player = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"Player");
	Vec3 PlayerPos = Player->Transform()->GetRelativePos();
	Vec3 PlayerScale = Player->Transform()->GetRelativeScale();
	//Player의 실제 Pos는 발바닥에 있음
	PlayerPos = Vec3(PlayerPos.x, PlayerPos.y - 50.f, PlayerPos.z);
	Vec3 CurPos = Transform()->GetRelativePos();
	Vec3 MonScale = Transform()->GetRelativeScale();
	CurPos = Vec3(CurPos.x, CurPos.y - 85.f, CurPos.z);

	if (PlayerPos.x < CurPos.x) {
		GhoulMainScript->SetGhoulDir(DIR_LEFT);
	}
	else {
		GhoulMainScript->SetGhoulDir(DIR_RIGHT);
	}

	if (GhoulMainScript->GetGhoulDir() != m_iMovingdirection) {
		if (GhoulMainScript->GetGhoulDir() == DIR_RIGHT) {
			m_iMovingdirection = DIR_RIGHT;
			float m_fDegree = 0.f / 180.f * XM_PI;
			Transform()->SetRelativeRot(Vec3(0.f, m_fDegree, 0.f));
			Animator2D()->Play(L"GhoulWalk_Right", true);
		}
		else if (GhoulMainScript->GetGhoulDir() == DIR_LEFT) {
			m_iMovingdirection = DIR_LEFT;
			float m_fDegree = 180.f / 180.f * XM_PI;
			Transform()->SetRelativeRot(Vec3(0.f, m_fDegree, 0.f));
			Animator2D()->Play(L"GhoulWalk_Right", true);
		}
	}

	m_fTime += DT;
	//AStar는 0.1초마다 한번씩
	if (m_fTime > 0.1f) {
		Vec2 DestPos = CAstarMgr::GetInst()->SetFind(CurPos, PlayerPos);
		if (DestPos == Vec2(0.f, 0.f)) {
			CGameObject* Player = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"Player");
			CPlayerScript* PlayerMainScript = Player->GetScript<CPlayerScript>();
			if (PlayerMainScript->IsPlayerOnGround()) {
				ChangeState((UINT)SCRIPT_TYPE::GHOULATTACKSCRIPT);
				GhoulMainScript->SetPlayerPos(Player->Transform()->GetRelativePos());
			}
			else {
				ChangeState((UINT)SCRIPT_TYPE::GHOULIDLESCRIPT, false);
			}

		}
		else if (DestPos == Vec2(-1.f, -1.f)) {
			ChangeState((UINT)SCRIPT_TYPE::GHOULIDLESCRIPT, false);
		}
		else {
			//이동을 한다.
			Vec2 Direction = Vec2(DestPos.x - CurPos.x, DestPos.y - CurPos.y);
			Direction.Normalize();
			RigidBody()->SetVelocity(Vec2(Direction.x * m_fForce, Direction.y * m_fForce));

		}
	}


}

void CGhoulTraceScript::Enter()
{
	m_fTime = 0.f;
	CGhoulScript* GhoulMainScript = GetOwner()->GetScript<CGhoulScript>();
	if (GhoulMainScript->GetGhoulDir() == DIR_RIGHT) {
		m_iMovingdirection = DIR_RIGHT;
		float m_fDegree = 0.f / 180.f * XM_PI;
		Transform()->SetRelativeRot(Vec3(0.f, m_fDegree, 0.f));
		Animator2D()->Play(L"GhoulWalk_Right", true);
	}
	else if (GhoulMainScript->GetGhoulDir() == DIR_LEFT) {
		m_iMovingdirection = DIR_LEFT;
		float m_fDegree = 180.f / 180.f * XM_PI;
		Transform()->SetRelativeRot(Vec3(0.f, m_fDegree, 0.f));
		Animator2D()->Play(L"GhoulWalk_Right", true);
	}
}

void CGhoulTraceScript::Exit()
{
	m_fTime = 0.f;
	RigidBody()->SetVelocity(Vec2(0.f, 0.f));
}
