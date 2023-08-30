#include "pch.h"
#include "CTowerScript.h"
#include "CPlayerScript.h"
#include "CPlayerHitScript.h"
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim2D.h>

CTowerScript::CTowerScript()
	:CScript((UINT)SCRIPT_TYPE::TOWERSCRIPT)
{
}

CTowerScript::~CTowerScript()
{
}


void CTowerScript::begin()
{
	Animator2D()->SetSamplerState(1);
	Animator2D()->LoadAnim(L"animation\\bossattack\\tower.anim");
	Animator2D()->Play(L"tower", false);
}

void CTowerScript::tick()
{
	if (Animator2D()->GetCurAnim()->IsFinish()) {
		DestroyObject(GetOwner());
	}
}

void CTowerScript::BeginOverlap(CCollider2D* _Other)
{
	if (_Other->GetOwner()->GetLayerIndex() == CLevelMgr::GetInst()->GetCurLevel()->FindLayerByName(L"Wall")->GetLayerIndex() ||
		_Other->GetOwner()->GetLayerIndex() == CLevelMgr::GetInst()->GetCurLevel()->FindLayerByName(L"PitWall")->GetLayerIndex()) {
		DestroyObject(GetOwner());
	}

	if (_Other->GetOwner()->GetName() == L"PlayerHitBox") {
		CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
		if (Curlevel->GetLayer(_Other->GetOwner()->GetLayerIndex())->GetName() == L"PlayerHitBox") {
			CGameObject* Player = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"Player");
			CPlayerScript* PlayerMainScript = Player->GetScript<CPlayerScript>();
			CPlayerHitScript* PlayerHitScript = Player->GetScript<CPlayerHitScript>();
			if (PlayerMainScript->IsPlayerDeadState() == false) {
				PlayerMainScript->ChangeState((UINT)SCRIPT_TYPE::PLAYERHITSCRIPT, false);
				PlayerHitScript->SetDirection(Vec3(0.f, -1.f, 0.f));
			}
			
		}
	}
}


