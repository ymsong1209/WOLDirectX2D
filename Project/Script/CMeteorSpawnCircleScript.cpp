#include "pch.h"
#include "CMeteorSpawnCircleScript.h"
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim2D.h>


CMeteorSpawnCircleScript::CMeteorSpawnCircleScript()
	:CScript((UINT)SCRIPT_TYPE::METEORSPAWNCIRCLESCRIPT)
{
}

CMeteorSpawnCircleScript::~CMeteorSpawnCircleScript()
{
}

void CMeteorSpawnCircleScript::begin()
{
	Animator2D()->LoadAnim(L"animation\\particle\\castingcircle.anim");
	Animator2D()->Play(L"castingcircle", false);
}

void CMeteorSpawnCircleScript::tick()
{
	int a = 0;
	/*if (Animator2D()->GetCurAnim()->IsFinish()) {
		DestroyObject(GetOwner());
	}*/
}

