#include "pch.h"
#include "CMeteorRingScript.h"
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim2D.h>

CMeteorRingScript::CMeteorRingScript()
	: CScript((UINT)SCRIPT_TYPE::METEORRINGSCRIPT)
{
}

CMeteorRingScript::~CMeteorRingScript()
{
}

void CMeteorRingScript::begin()
{
	Animator2D()->LoadAnim(L"animation\\particle\\Meteorring.anim");
	Animator2D()->Play(L"Meteorring", false);
}

void CMeteorRingScript::tick()
{
	if (Animator2D()->GetCurAnim()->IsFinish()) {
		DestroyObject(GetOwner());
	}
}


