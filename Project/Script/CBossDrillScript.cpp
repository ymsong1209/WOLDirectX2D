#include "pch.h"
#include "CBossDrillScript.h"
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim2D.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CEventMgr.h>
#include "CPlayerScript.h"
#include "CPlayerHitScript.h"

CBossDrillScript::CBossDrillScript()
	:CScript((UINT)SCRIPT_TYPE::BOSSDRILLSCRIPT)
	,m_bRotate(false)
{
}

CBossDrillScript::~CBossDrillScript()
{
}

void CBossDrillScript::begin()
{
	
}

void CBossDrillScript::tick()
{
	if (m_bRotate) return;

	if (Animator2D()->GetCurAnim()->IsFinish()) {
		m_bRotate = true;
		Animator2D()->Play(L"Boss_Drill_Rotate", true);
	
	}
}

void CBossDrillScript::init()
{
	CLayer* layer = CLevelMgr::GetInst()->GetCurLevel()->FindLayerByName(L"MonsterProjectile");
	GetOwner()->SetLayerIndex(layer->GetLayerIndex());

	// 이벤트 매니저를 통해서 처리한다.
	tEvent evn = {};
	evn.Type = EVENT_TYPE::ADD_CHILD;
	evn.wParam = (DWORD_PTR)m_pOwner;
	evn.lParam = (DWORD_PTR)GetOwner();
	CEventMgr::GetInst()->AddEvent(evn);


	Animator2D()->LoadAnim(L"animation\\bossattack\\Boss_Drill_Spawn.anim");
	Animator2D()->LoadAnim(L"animation\\bossattack\\Boss_Drill_Rotate.anim");
	Animator2D()->Play(L"Boss_Drill_Spawn", false);
}


void CBossDrillScript::BeginOverlap(CCollider2D* _Other)
{
	if (_Other->GetOwner()->GetName() == L"PlayerHitBox" ) {
		CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
		if (Curlevel->GetLayer(_Other->GetOwner()->GetLayerIndex())->GetName() == L"PlayerHitBox") {
			CGameObject* Player = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"Player");
			CPlayerScript* PlayerMainScript = Player->GetScript<CPlayerScript>();
			CPlayerHitScript* PlayerHitScript = Player->GetScript<CPlayerHitScript>();

			if (PlayerMainScript->IsPlayerDeadState() == false) {
				PlayerMainScript->ChangeState((UINT)SCRIPT_TYPE::PLAYERHITSCRIPT, false);
				PlayerHitScript->SetDirection(Vec3(0.f,-1.f,0.f));
			}

		}
		Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\EarthPebble.wav");
		pSound->Play(1, 0.2, true);
	}
}

