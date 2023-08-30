#include "pch.h"
#include "CBossLeapAttackScript.h"
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim2D.h>
#include <Engine/CEventMgr.h>

CBossLeapAttackScript::CBossLeapAttackScript()
	:CScript((UINT)SCRIPT_TYPE::BOSSLEAPATTACKSCRIPT)
{
}

CBossLeapAttackScript::~CBossLeapAttackScript()
{
}

void CBossLeapAttackScript::begin()
{
	Animator2D()->LoadAnim(L"animation\\particle\\floorcrack.anim");
	Animator2D()->Play(L"floorcrack", false);
}

void CBossLeapAttackScript::tick()
{
	if (Animator2D()->GetCurAnim()->IsFinish()) {
		DestroyObject(GetOwner());
	}
}




