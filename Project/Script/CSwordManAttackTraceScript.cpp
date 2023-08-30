#include "pch.h"
#include "CSwordManAttackTraceScript.h"
#include <Engine/CAnim2D.h>
#include <Engine/CAnimator2D.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include "CPlayerScript.h"
#include "CPlayerHitScript.h"

CSwordManAttackTraceScript::CSwordManAttackTraceScript()
	:CScript((UINT)SCRIPT_TYPE::SWORDMANATTACKTRACESCRIPT)
{
}

CSwordManAttackTraceScript::~CSwordManAttackTraceScript()
{
}


void CSwordManAttackTraceScript::begin()
{
	Animator2D()->LoadAnim(L"animation\\enemy\\SwordMan\\SwordMan_Attack.anim");
	Animator2D()->Play(L"SwordMan_Attack", false);
	float degree = m_fInputangle / 180.f * XM_PI;
	m_vDirection = Vec3(cos(degree), sin(degree), 1.f);
}

void CSwordManAttackTraceScript::tick()
{
	if (Animator2D()->GetCurAnim()->IsFinish()) {
		Animator2D()->GetCurAnim()->Reset();
		DestroyObject(GetOwner());
	}
}

void CSwordManAttackTraceScript::BeginOverlap(CCollider2D* _Other)
{
	
	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
	if (Curlevel->GetLayer(_Other->GetOwner()->GetLayerIndex())->GetName() == L"PlayerHitBox") {
		CGameObject* Player = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"Player");
		CPlayerScript* PlayerMainScript = Player->GetScript<CPlayerScript>();
		CPlayerHitScript* PlayerHitScript = Player->GetScript<CPlayerHitScript>();
		if (PlayerMainScript->IsPlayerDeadState() == false) {
			PlayerMainScript->ChangeState((UINT)SCRIPT_TYPE::PLAYERHITSCRIPT, false);
			PlayerHitScript->SetDirection(m_vDirection);
		}
	}
}

void CSwordManAttackTraceScript::OnOverlap(CCollider2D* _Other)
{
}

void CSwordManAttackTraceScript::EndOverlap(CCollider2D* _Other)
{
}


