#include "pch.h"
#include "CGhoulSpawnScript.h"
#include "CGhoulScript.h"
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim2D.h>
#include "CGhoulHitBoxScript.h"

CGhoulSpawnScript::CGhoulSpawnScript()
	:CScript((UINT)SCRIPT_TYPE::GHOULSPAWNSCRIPT)
{
	SetActive(false);
}

CGhoulSpawnScript::~CGhoulSpawnScript()
{
}

void CGhoulSpawnScript::begin()
{
}

void CGhoulSpawnScript::tick()
{
	if (!IsActive()) return;
	if (Animator2D()->GetCurAnim()->IsFinish()) {
		GetOwner()->AddComponent(new CCollider2D);
		Collider2D()->SetAbsolute(true);
		Collider2D()->SetOffsetPos(Vec2(0.f, -85.f));
		Collider2D()->SetOffsetScale(Vec2(2.f, 2.f));

		vector<CGameObject*> childs = GetOwner()->GetChild();

		CGameObject* HitBox = childs[0];
		CGhoulHitBoxScript* HitBoxScript = HitBox->GetScript<CGhoulHitBoxScript>();
		HitBoxScript->AddCollider();

		ChangeState((UINT)SCRIPT_TYPE::GHOULIDLESCRIPT, false);
	}
}

void CGhoulSpawnScript::Enter()
{
	GetOwner()->AddComponent(new CAnimator2D);
	Animator2D()->LoadAnim(L"animation\\enemy\\Ghoul\\GhoulAttack_Left.anim");
	Animator2D()->LoadAnim(L"animation\\enemy\\Ghoul\\GhoulAttackReady_Left.anim");
	Animator2D()->LoadAnim(L"animation\\enemy\\Ghoul\\GhoulDead_Right.anim");
	Animator2D()->LoadAnim(L"animation\\enemy\\Ghoul\\GhoulIdle_Left.anim");
	Animator2D()->LoadAnim(L"animation\\enemy\\Ghoul\\GhoulWalk_Right.anim");
	Animator2D()->LoadAnim(L"animation\\enemy\\Ghoul\\GhoulHit_Right.anim");
	Animator2D()->LoadAnim(L"animation\\enemy\\AppearEnemy.anim");

	Animator2D()->SetSamplerState(1);
	Animator2D()->Play(L"AppearEnemy", false);

}

void CGhoulSpawnScript::Exit()
{
}