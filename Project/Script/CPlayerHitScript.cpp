#include "pch.h"
#include "CPlayerHitScript.h"
#include "CPlayerScript.h"
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim2D.h>

CPlayerHitScript::CPlayerHitScript()
	:CScript((UINT)SCRIPT_TYPE::PLAYERHITSCRIPT)
	,m_vDirection(0.f,0.f,0.f)
	,m_fForce(50.f)
{
	SetActive(false);
}

CPlayerHitScript::~CPlayerHitScript()
{
}


void CPlayerHitScript::begin()
{
}

void CPlayerHitScript::tick()
{
	if (!IsActive()) return;
	if (abs(RigidBody()->GetVelocity().x) < 0.1f && abs(RigidBody()->GetVelocity().y) < 0.1f) {
		ChangeState((UINT)SCRIPT_TYPE::PLAYERIDLESCRIPT, false);
	}

}

void CPlayerHitScript::Enter()
{
	CPlayerScript* PlayerMainScript = GetOwner()->GetScript<CPlayerScript>();

	PlayerStat stat = PlayerMainScript->GetStat();
	stat.CurHP = stat.CurHP - 10;
	if (stat.CurHP < 0) stat.CurHP = 0;
	PlayerMainScript->SetStat(stat);

	RigidBody()->SetVelocity(Vec2(0.f, 0.f));
	if (m_vDirection == Vec3(0.f, 0.f, 0.f)) {
		m_fForce = 0.f;
	}

	m_vDirection.Normalize();
	if (abs(m_vDirection.x) < abs(m_vDirection.y)) {
		//아래에서 위로 침 -> player는 아래를 바라봐야함
		if (m_vDirection.y > 0.f) {
			PlayerMainScript->SetPlayerDir(DIR_DOWN);
			Animator2D()->Play(L"Player_Hit_Down", true);
		}
		//위에서 아래로 침 -> player는 위를 바라봐야함
		else {
			PlayerMainScript->SetPlayerDir(DIR_UP);
			Animator2D()->Play(L"Player_Hit_Up", true);
		}
	}
	else {
		//왼쪽에서 오른쪽로 침 -> player는 왼쪽를 바라봐야함
		if (m_vDirection.x > 0.f) {
			PlayerMainScript->SetPlayerDir(DIR_LEFT);
			Animator2D()->Play(L"Player_Hit_Left", true);
		}
		//오른쪽에서 왼쪽으로 침 -> player는 오른쪽를 바라봐야함
		else {
			PlayerMainScript->SetPlayerDir(DIR_RIGHT);
			Animator2D()->Play(L"Player_Hit_Right", true);
		}
	}
	RigidBody()->SetVelocity(Vec2(m_vDirection.x * m_fForce, m_vDirection.y * m_fForce));
	
	srand(time(NULL));
	if (rand() % 3 == 0) {
		Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\Hit1.wav");
		pSound->Play(1, 0.25f, true);
	}
	else if (rand() % 3 == 1) {
		Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\Hit2.wav");
		pSound->Play(1, 0.25f, true);
	}
	else if (rand() % 3 == 2) {
		Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\Hit3.wav");
		pSound->Play(1, 0.25f, true);
	}
}

void CPlayerHitScript::Exit()
{
	m_vDirection = Vec3(0.f, 0.f, 0.f);
	m_fForce = 50.f;
}


