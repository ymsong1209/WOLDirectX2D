#include "pch.h"
#include "CMageSpawnScript.h"
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim2D.h>
#include "CMageHitBoxScript.h"


CMageSpawnScript::CMageSpawnScript()
	:CScript((UINT)SCRIPT_TYPE::MAGESPAWNSCRIPT)
{
	SetActive(false);
}

CMageSpawnScript::~CMageSpawnScript()
{
}

void CMageSpawnScript::begin()
{
}

void CMageSpawnScript::tick()
{
	if (!IsActive()) return;

	if (Animator2D()->GetCurAnim()->IsFinish()) {
		GetOwner()->AddComponent(new CCollider2D);
		Collider2D()->SetAbsolute(true);
		Collider2D()->SetOffsetScale(Vec2(2.f,2.f));
		Collider2D()->SetOffsetPos(Vec2(0.f, -80.f));
		ChangeState((UINT)SCRIPT_TYPE::MAGEIDLESCRIPT, false);

		vector<CGameObject*> childs = GetOwner()->GetChild();

		CGameObject* HitBox = childs[0];
		CMageHitBoxScript* HitBoxScript = HitBox->GetScript<CMageHitBoxScript>();
		HitBoxScript->AddCollider();
	}
}

void CMageSpawnScript::Enter()
{
	GetOwner()->AddComponent(new CAnimator2D);
	//Animator2D()->LoadAnim(L"animation\\enemy\\Wizard\\Wizard_Death_Left.anim");
	Animator2D()->LoadAnim(L"animation\\enemy\\Wizard\\Wizard_Attack_Left.anim");
	Animator2D()->LoadAnim(L"animation\\enemy\\Wizard\\Wizard_Death.Left.anim");
	Animator2D()->LoadAnim(L"animation\\enemy\\Wizard\\Wizard_Hit_Left.anim");
	Animator2D()->LoadAnim(L"animation\\enemy\\Wizard\\Wizard_Idle_Left.anim");
	Animator2D()->LoadAnim(L"animation\\enemy\\Wizard\\WizardSpawn_Right.anim");
	Animator2D()->LoadAnim(L"animation\\enemy\\Wizard\\Wizard_Walk_Left.anim");

	Animator2D()->SetSamplerState(1);
	Animator2D()->Play(L"WizardSpawn_Right", false);
}

void CMageSpawnScript::Exit()
{
}



