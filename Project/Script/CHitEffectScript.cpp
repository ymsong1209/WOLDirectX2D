#include "pch.h"
#include "CHitEffectScript.h"
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim2D.h>

CHitEffectScript::CHitEffectScript()
	:CScript((UINT)SCRIPT_TYPE::HITEFFECTSCRIPT)
{
}

CHitEffectScript::~CHitEffectScript()
{
}

void CHitEffectScript::tick()
{
	if (GetOwner()->IsDead()) return;
	if (Animator2D()->GetCurAnim()->IsFinish()) {
		DestroyObject(GetOwner());
	}
}

void CHitEffectScript::begin()
{
	Animator2D()->Play(L"HitEffect", false);
	srand(time(NULL));
	if (rand() % 2 == 0) {
		Transform()->SetRelativeRot(Vec3(0.f, XMConvertToRadians(180.f), 0.f));
	}
}


