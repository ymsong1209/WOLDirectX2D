#include "pch.h"
#include "CGhoulAttackTraceScript.h"
#include <Engine/CAnim2D.h>
#include <Engine/CAnimator2D.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include "CPlayerScript.h"
#include "CPlayerHitScript.h"

CGhoulAttackTraceScript::CGhoulAttackTraceScript()
	:CScript((UINT)SCRIPT_TYPE::GHOULATTACKTRACESCRIPT)
{
}

CGhoulAttackTraceScript::~CGhoulAttackTraceScript()
{
}


void CGhoulAttackTraceScript::begin()
{
	Animator2D()->LoadAnim(L"animation\\enemy\\SwordMan\\SwordMan_Attack.anim");
	Animator2D()->Play(L"SwordMan_Attack", false);
	Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\GhoulAttack.wav");
	pSound->Play(1, 0.2f, true);
}

void CGhoulAttackTraceScript::tick()
{
	if (Animator2D()->GetCurAnim()->IsFinish()) {
		Animator2D()->GetCurAnim()->Reset();
		DestroyObject(GetOwner());
	}
}

void CGhoulAttackTraceScript::BeginOverlap(CCollider2D* _Other)
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

void CGhoulAttackTraceScript::OnOverlap(CCollider2D* _Other)
{
}

void CGhoulAttackTraceScript::EndOverlap(CCollider2D* _Other)
{
}
