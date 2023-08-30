#include "pch.h"
#include "CSwordManTraceScript.h"
#include "CSwordManScript.h"
#include <Engine/CAstarMgr.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim2D.h>
#include "CPlayerScript.h"

CSwordManTraceScript::CSwordManTraceScript()
	: CScript((UINT)SCRIPT_TYPE::SWORDMANTRACESCRIPT)
	, m_iMovingdirection(0)
	, m_fForce(250.f)
{
	SetActive(false);
}

CSwordManTraceScript::~CSwordManTraceScript()
{
}


void CSwordManTraceScript::begin()
{
}

void CSwordManTraceScript::tick()
{
	if (!IsActive()) return;
	CSwordManScript* SwordManScript = GetOwner()->GetScript<CSwordManScript>();
	CGameObject* Player = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"Player");
	Vec3 PlayerPos = Player->Transform()->GetRelativePos();
	Vec3 PlayerScale = Player->Transform()->GetRelativeScale();
	//Player의 실제 Pos는 발바닥에 있음
	PlayerPos = Vec3(PlayerPos.x, PlayerPos.y - 50.f, PlayerPos.z);
	Vec3 CurPos = Transform()->GetRelativePos();
	Vec3 MonScale = Transform()->GetRelativeScale();
	CurPos = Vec3(CurPos.x, CurPos.y - 80.f, CurPos.z);

	if (PlayerPos.x < CurPos.x) {
		SwordManScript->SetSwordManDir(DIR_LEFT);
	}
	else {
		SwordManScript->SetSwordManDir(DIR_RIGHT);
	}

	if (SwordManScript->GetSwordManDir() != m_iMovingdirection) {
		if (SwordManScript->GetSwordManDir() == DIR_RIGHT) {
			m_iMovingdirection = DIR_RIGHT;
			float m_fDegree = 180.f / 180.f * XM_PI;
			Transform()->SetRelativeRot(Vec3(0.f, m_fDegree, 0.f));
			Animator2D()->Play(L"SwordMan_Walk_Left", true);
		}
		else if (SwordManScript->GetSwordManDir() == DIR_LEFT) {
			m_iMovingdirection = DIR_LEFT;
			float m_fDegree = 0.f / 180.f * XM_PI;
			Transform()->SetRelativeRot(Vec3(0.f, m_fDegree, 0.f));
			Animator2D()->Play(L"SwordMan_Walk_Left", true);
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
				ChangeState((UINT)SCRIPT_TYPE::SWORDMANATTACKSCRIPT);
				SwordManScript->SetPlayerPos(Player->Transform()->GetRelativePos());
			}
			else {
				ChangeState((UINT)SCRIPT_TYPE::SWORDMANIDLESCRIPT, false);
			}
		
		}
		else if (DestPos == Vec2(-1.f, -1.f)) {
			ChangeState((UINT)SCRIPT_TYPE::SWORDMANIDLESCRIPT, false);
		}
		else {
			//이동을 한다.
			Vec2 Direction = Vec2(DestPos.x - CurPos.x, DestPos.y - CurPos.y);
			Direction.Normalize();
			RigidBody()->SetVelocity(Vec2(Direction.x * m_fForce, Direction.y * m_fForce));

		}
	}
	

}

void CSwordManTraceScript::Enter()
{
	m_fTime = 0.f;
	CSwordManScript* SwordManScript = GetOwner()->GetScript<CSwordManScript>();
	if (SwordManScript->GetSwordManDir() == DIR_RIGHT) {
		m_iMovingdirection = DIR_RIGHT;
		float m_fDegree = 180.f / 180.f * XM_PI;
		Transform()->SetRelativeRot(Vec3(0.f, m_fDegree, 0.f));
		Animator2D()->Play(L"SwordMan_Walk_Left", true);
	}
	else if (SwordManScript->GetSwordManDir() == DIR_LEFT) {
		m_iMovingdirection = DIR_LEFT;
		float m_fDegree = 0.f / 180.f * XM_PI;
		Transform()->SetRelativeRot(Vec3(0.f, m_fDegree, 0.f));
		Animator2D()->Play(L"SwordMan_Walk_Left", true);
	}
}

void CSwordManTraceScript::Exit()
{
	m_fTime = 0.f;
	RigidBody()->SetVelocity(Vec2(0.f, 0.f));
}



