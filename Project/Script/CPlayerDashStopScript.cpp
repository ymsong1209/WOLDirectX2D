#include "pch.h"
#include "CPlayerDashStopScript.h"
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim2D.h>
#include "CPlayerScript.h"

CPlayerDashStopScript::CPlayerDashStopScript()
	: CScript((UINT)SCRIPT_TYPE::PLAYERDASHSTOPSCRIPT)
	, m_bIsLeftorRight(true)
	, m_bTick(true)
{
	SetActive(false);
}

CPlayerDashStopScript::~CPlayerDashStopScript()
{
}

void CPlayerDashStopScript::begin()
{
}

void CPlayerDashStopScript::tick()
{
	if (!IsActive()) return;
	CPlayerScript* PlayerMainScript = GetOwner()->GetScript<CPlayerScript>();
	int Direction = PlayerMainScript->GetPlayerDir();
	if (!m_bIsLeftorRight) {
		if (m_bTick) {
			m_bTick = false;
			return;
		}
		ChangeState((UINT)SCRIPT_TYPE::PLAYERSLIDESCRIPT);
		if (Direction & DIR_UP) {
			PlayerMainScript->SetPlayerDir(DIR_UP);
		}
		else if (Direction & DIR_DOWN) {
			PlayerMainScript->SetPlayerDir(DIR_DOWN);
		}
	}
	if (Animator2D()->GetCurAnim()->IsFinish()) {
		ChangeState((UINT)SCRIPT_TYPE::PLAYERSLIDESCRIPT);
		if (Direction & DIR_RIGHT) {
			PlayerMainScript->SetPlayerDir(DIR_RIGHT);
		}
		else if (Direction & DIR_LEFT) {
			PlayerMainScript->SetPlayerDir(DIR_LEFT);
		}
	}
}

void CPlayerDashStopScript::Enter()
{
	m_bTick = true;
	CPlayerScript* PlayerMainScript = GetOwner()->GetScript<CPlayerScript>();
	//상,하가 좌,우보다 우선임
	if ((PlayerMainScript->GetPlayerDir() & DIR_UP) || PlayerMainScript->GetPlayerDir() & DIR_DOWN) {
		m_bIsLeftorRight = false;
	}
	else if (PlayerMainScript->GetPlayerDir() & DIR_RIGHT) {
		Animator2D()->Play(L"Player_Dash_Stop_Right", false);
	}
	else if (PlayerMainScript->GetPlayerDir() & DIR_LEFT) {
		Animator2D()->Play(L"Player_Dash_Stop_Left", false);
	}
	
	RigidBody()->SetVelocity(Vec2(0.f, 0.f));
}

void CPlayerDashStopScript::Exit()
{
	Animator2D()->GetCurAnim()->Reset();
	m_bIsLeftorRight = true;
	m_bTick = true;
}

void CPlayerDashStopScript::BeginOverlap(CCollider2D* _Other)
{
	if (!IsActive()) return;
	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
	CPlayerScript* PlayerMainScript = GetOwner()->GetScript<CPlayerScript>();
	if (Curlevel->GetLayer(_Other->GetOwner()->GetLayerIndex())->GetName() == L"Pit") {
		ChangeState((UINT)SCRIPT_TYPE::PLAYERFALLSCRIPT, false);
		//상,하가 좌,우보다 우선임
		if ((PlayerMainScript->GetPlayerDir() & DIR_UP)) {
			PlayerMainScript->SetPlayerDir(DIR_UP);
		}
		else if (PlayerMainScript->GetPlayerDir() & DIR_DOWN) {
			PlayerMainScript->SetPlayerDir(DIR_DOWN);
		}
		else if (PlayerMainScript->GetPlayerDir() & DIR_RIGHT) {
			PlayerMainScript->SetPlayerDir(DIR_RIGHT);
		}
		else if (PlayerMainScript->GetPlayerDir() & DIR_LEFT) {
			PlayerMainScript->SetPlayerDir(DIR_LEFT);
		}
		else {
			assert(nullptr);
		}
	}
}

void CPlayerDashStopScript::OnOverlap(CCollider2D* _Other)
{
	if (!IsActive()) return;
	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
	CPlayerScript* PlayerMainScript = GetOwner()->GetScript<CPlayerScript>();
	if (Curlevel->GetLayer(_Other->GetOwner()->GetLayerIndex())->GetName() == L"Pit") {
		// pit 2개에 겹치면 changestate가 2번 호출됨.
		// ChangeState는 한번만 일어난다.
		ChangeState((UINT)SCRIPT_TYPE::PLAYERFALLSCRIPT, false);
		//상,하가 좌,우보다 우선임
		if ((PlayerMainScript->GetPlayerDir() & DIR_UP)) {
			PlayerMainScript->SetPlayerDir(DIR_UP);
		}
		else if (PlayerMainScript->GetPlayerDir() & DIR_DOWN) {
			PlayerMainScript->SetPlayerDir(DIR_DOWN);
		}
		else if (PlayerMainScript->GetPlayerDir() & DIR_RIGHT) {
			PlayerMainScript->SetPlayerDir(DIR_RIGHT);
		}
		else if (PlayerMainScript->GetPlayerDir() & DIR_LEFT) {
			PlayerMainScript->SetPlayerDir(DIR_LEFT);
		}
		else {
			assert(nullptr);
		}
	}
}

void CPlayerDashStopScript::EndOverlap(CCollider2D* _Other)
{
	if (!IsActive()) return;
}



