#include "pch.h"
#include "CSwordManSpawnScript.h"
#include "CSwordManScript.h"
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim2D.h>
#include "CSwordManHitBoxScript.h"

CSwordManSpawnScript::CSwordManSpawnScript()
	:CScript((UINT)SCRIPT_TYPE::SWORDMANSPAWNSCRIPT)
{
	SetActive(false);
}

CSwordManSpawnScript::~CSwordManSpawnScript()
{
}

void CSwordManSpawnScript::begin()
{
}

void CSwordManSpawnScript::tick()
{
	if (!IsActive()) return;
	if (Animator2D()->GetCurAnim()->IsFinish()) {
		GetOwner()->AddComponent(new CCollider2D);
		Collider2D()->SetAbsolute(true);
		Collider2D()->SetOffsetPos(Vec2(0.f, -80.f));
		Collider2D()->SetOffsetScale(Vec2(2.f, 2.f));
		
		vector<CGameObject*> childs = GetOwner()->GetChild();
		
		CGameObject* HitBox = childs[0];
		CSwordManHitBoxScript* HitBoxScript = HitBox->GetScript<CSwordManHitBoxScript>();
		HitBoxScript->AddCollider();

		ChangeState((UINT)SCRIPT_TYPE::SWORDMANIDLESCRIPT, false);
	}
}

void CSwordManSpawnScript::Enter()
{
	GetOwner()->AddComponent(new CAnimator2D);
	Animator2D()->LoadAnim(L"animation\\enemy\\SwordMan\\SwordMan_Attack_Left.anim");
	Animator2D()->LoadAnim(L"animation\\enemy\\SwordMan\\SwordMan_AttackReady_Left.anim");
	Animator2D()->LoadAnim(L"animation\\enemy\\SwordMan\\SwordMan_Death_Left.anim");
	Animator2D()->LoadAnim(L"animation\\enemy\\SwordMan\\SwordMan_Hit_Left.anim");
	Animator2D()->LoadAnim(L"animation\\enemy\\SwordMan\\SwordMan_Idle_Left.anim");
	Animator2D()->LoadAnim(L"animation\\enemy\\SwordMan\\SwordMan_Spawn_Leftover.anim");
	Animator2D()->LoadAnim(L"animation\\enemy\\SwordMan\\SwordMan_Spawn_Right.anim");
	Animator2D()->LoadAnim(L"animation\\enemy\\SwordMan\\SwordMan_Walk_Left.anim");

	Animator2D()->SetSamplerState(1);
	Animator2D()->Play(L"SwordMan_Spawn_Right", false);

}

void CSwordManSpawnScript::Exit()
{
}
