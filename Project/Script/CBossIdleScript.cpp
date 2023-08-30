#include "pch.h"
#include "CBossIdleScript.h"
#include "CBossScript.h"

CBossIdleScript::CBossIdleScript()
	:CScript((UINT)SCRIPT_TYPE::BOSSIDLESCRIPT)
{
	SetActive(false);
}

CBossIdleScript::~CBossIdleScript()
{
}

void CBossIdleScript::begin()
{
}

void CBossIdleScript::tick()
{
	if (!IsActive()) return;
}

void CBossIdleScript::Enter()
{
	Animator2D()->Play(L"Boss_Idle", true);
}

void CBossIdleScript::Exit()
{
}


