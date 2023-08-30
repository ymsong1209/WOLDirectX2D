#include "pch.h"
#include "CPlayerIdleScript.h"

#include <Engine/CKeyMgr.h>
#include "CScriptMgr.h"
#include "CMousePointerScript.h"
#include "CPlayerScript.h"



CPlayerIdleScript::CPlayerIdleScript()
	: CScript((UINT)SCRIPT_TYPE::PLAYERIDLESCRIPT)
	, m_bIdleToWalk(false)
	, m_iWalkKeyCheck(0)
{
	SetActive(false);
}

CPlayerIdleScript::~CPlayerIdleScript()
{
}


void CPlayerIdleScript::begin()
{
	if (!IsActive()) return;
	
}

void CPlayerIdleScript::tick()
{
	if (!IsActive()) return;
	if (KEY_TAP(KEY::F)) {
		ChangeState((UINT)SCRIPT_TYPE::PLAYERDEADSCRIPT, false);
	}

	CPlayerScript* PlayerMainScript = GetOwner()->GetScript<CPlayerScript>();
	if (PlayerMainScript->GetPlayerDir() ==  DIR_RIGHT) {
		Animator2D()->Play(L"Player_Idle_Right", true);
	}
	else if (PlayerMainScript->GetPlayerDir() == DIR_UP) {
		Animator2D()->Play(L"Player_Idle_Up", true);
	}
	else if (PlayerMainScript->GetPlayerDir() == DIR_LEFT) {
		Animator2D()->Play(L"Player_Idle_Left", true);
	}
	else if (PlayerMainScript->GetPlayerDir() == DIR_DOWN){
		Animator2D()->Play(L"Player_Idle_Down", true);
	}
	else {
		assert(nullptr);
	}
	

	//State Change : Walk//
	m_iWalkKeyCheck = PlayerMainScript->GetPlayerDir();
	if (KEY_TAP(KEY::W) || KEY_PRESSED(KEY::W) ||
		KEY_TAP(KEY::A) || KEY_PRESSED(KEY::A) ||
		KEY_TAP(KEY::S) || KEY_PRESSED(KEY::S) ||
		KEY_TAP(KEY::D) || KEY_PRESSED(KEY::D)) {
		
		PlayerMainScript->SetPlayerDir(0);
	}
	if (KEY_TAP(KEY::W) || KEY_PRESSED(KEY::W)) {
		if (!(KEY_TAP(KEY::S) || (KEY_PRESSED(KEY::S)))) {
			PlayerMainScript->SetPlayerDir(PlayerMainScript->GetPlayerDir() | DIR_UP);
			m_bIdleToWalk = true;
		}
	}
	if (KEY_TAP(KEY::A) || KEY_PRESSED(KEY::A)) {
		if (!(KEY_TAP(KEY::D) || (KEY_PRESSED(KEY::D)))) {
			PlayerMainScript->SetPlayerDir(PlayerMainScript->GetPlayerDir() | DIR_LEFT);
			m_bIdleToWalk = true;
		}
	}
	if (KEY_TAP(KEY::S) || KEY_PRESSED(KEY::S)) {
		if (!(KEY_TAP(KEY::W) || (KEY_PRESSED(KEY::W)))) {
			PlayerMainScript->SetPlayerDir(PlayerMainScript->GetPlayerDir() | DIR_DOWN);
			m_bIdleToWalk = true;
		}
	}
	if (KEY_TAP(KEY::D) || KEY_PRESSED(KEY::D)) {
		if (!(KEY_TAP(KEY::A) || (KEY_PRESSED(KEY::A)))) {
			PlayerMainScript->SetPlayerDir(PlayerMainScript->GetPlayerDir() | DIR_RIGHT);
			m_bIdleToWalk = true;
		}
	}
	if (m_bIdleToWalk)
	{
		m_bIdleToWalk = false;
		ChangeState((UINT)SCRIPT_TYPE::PLAYERWALKSCRIPT);
	}
	else {
		PlayerMainScript->SetPlayerDir(m_iWalkKeyCheck);
	}


	//StateChange - Dash//
	if (KEY_TAP(KEY::SPACE)) {
		ChangeState((UINT)SCRIPT_TYPE::PLAYERDASHSCRIPT);
	}
	//StateChange - Attack//
	ChangeToAttack();
	

}



void CPlayerIdleScript::ChangeToAttack()
{
	//GetMousePointer------------//
	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
	CPlayerScript* PlayerMainScript = GetOwner()->GetScript<CPlayerScript>();

	if (KEY_TAP(KEY::LBTN)) {
		if (PlayerMainScript->GetCurCoolTimePerBtn(PLAYER_ATTACKBUTTON::LBTN) <= 0.f) {
			PlayerMainScript->SetAttackBtn(PLAYER_ATTACKBUTTON::LBTN);
			ChangeDir();
			ChangeState((UINT)SCRIPT_TYPE::PLAYERATTACKSCRIPT);
		}
	}
	else if (KEY_TAP(KEY::RBTN)) {
		if (PlayerMainScript->GetCurCoolTimePerBtn(PLAYER_ATTACKBUTTON::RBTN) <= 0.f) {
			PlayerMainScript->SetAttackBtn(PLAYER_ATTACKBUTTON::RBTN);
			ChangeDir();
			ChangeState((UINT)SCRIPT_TYPE::PLAYERATTACKSCRIPT);
		}
		
	}
	else if (KEY_TAP(KEY::Q)) {
		if (PlayerMainScript->GetCurCoolTimePerBtn(PLAYER_ATTACKBUTTON::Q) <= 0.f) {
			PlayerMainScript->SetAttackBtn(PLAYER_ATTACKBUTTON::Q);
			ChangeDir();
			ChangeState((UINT)SCRIPT_TYPE::PLAYERATTACKSCRIPT);
		}
		
	}
	else if (KEY_TAP(KEY::E)) {
		if (PlayerMainScript->GetCurCoolTimePerBtn(PLAYER_ATTACKBUTTON::E) <= 0.f) {
			PlayerMainScript->SetAttackBtn(PLAYER_ATTACKBUTTON::E);
			ChangeDir();
			ChangeState((UINT)SCRIPT_TYPE::PLAYERATTACKSCRIPT);
		}
		
	}
	else if (KEY_TAP(KEY::R)) {
		if (PlayerMainScript->GetCurCoolTimePerBtn(PLAYER_ATTACKBUTTON::R) <= 0.f) {
			PlayerMainScript->SetAttackBtn(PLAYER_ATTACKBUTTON::R);
			ChangeDir();
			ChangeState((UINT)SCRIPT_TYPE::PLAYERATTACKSCRIPT);
		}
		
	}
}

void CPlayerIdleScript::ChangeDir()
{
	//GetMousePointer------------//
	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
	CGameObject* mouse = Curlevel->FindParentObjectByName(L"MousePointer");
	CPlayerScript* PlayerMainScript = GetOwner()->GetScript<CPlayerScript>();
	CMousePointerScript* MouseScript = mouse->GetScript<CMousePointerScript>();
	Vec4 Mousepos = MouseScript->GetMousePos();
	Vec3 OwnerPos = GetOwner()->Transform()->GetRelativePos();

	// Calculate the angle between the player and the mouse
	double dx = Mousepos.x - OwnerPos.x;
	double dy = Mousepos.y - OwnerPos.y;
	double angle = atan2(dy, dx) * 180 / XM_PI;

	// Convert the angle to a direction
	if (angle > -45 && angle <= 45) {
		PlayerMainScript->SetPlayerDir(DIR_RIGHT);
	}
	else if (angle > 45 && angle <= 135) {
		PlayerMainScript->SetPlayerDir(DIR_UP);
	}
	else if (angle > 135 || angle <= -135) {
		PlayerMainScript->SetPlayerDir(DIR_LEFT);
	}
	else {
		PlayerMainScript->SetPlayerDir(DIR_DOWN);
	}
}

void CPlayerIdleScript::Enter()
{
	RigidBody()->SetVelocity(Vec2(0.f, 0.f));
}

void CPlayerIdleScript::Exit()
{
	m_bIdleToWalk = false;
}