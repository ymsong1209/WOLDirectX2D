#include "pch.h"
#include "CDashEffectScript.h"
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim2D.h>

CDashEffectScript::CDashEffectScript()
	:CScript((UINT)SCRIPT_TYPE::DASHEFFECTSCRIPT)
{
}

CDashEffectScript::~CDashEffectScript()
{
}


void CDashEffectScript::begin()
{
	Animator2D()->Play(L"Dash", false);
}

void CDashEffectScript::tick()
{
	if (GetOwner()->IsDead()) return;

	if (Animator2D()->GetCurAnim()->IsFinish()) {
		DestroyObject(GetOwner());
	}
}



