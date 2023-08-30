#include "pch.h"
#include "CMeteorFloorCrackScript.h"
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim2D.h>

CMeteorFloorCrackScript::CMeteorFloorCrackScript()
	: CScript((UINT)SCRIPT_TYPE::METEORFLOORCRACKSCRIPT)
{
}

CMeteorFloorCrackScript::~CMeteorFloorCrackScript()
{
}


void CMeteorFloorCrackScript::begin()
{
	Animator2D()->LoadAnim(L"animation\\particle\\floorcrack.anim");
	Animator2D()->SetSamplerState(1);
	Animator2D()->Play(L"floorcrack", false);
}

void CMeteorFloorCrackScript::tick()
{
	if (Animator2D()->GetCurAnim()->IsFinish()) {
		DestroyObject(GetOwner());
	}
}

