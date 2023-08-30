#include "pch.h"
#include "CBossEnterScript.h"
#include "CBossScript.h"
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim2D.h>
#include "CBossHPScript.h"
#include "CBossUIScript.h"

CBossEnterScript::CBossEnterScript()
	:CScript((UINT)SCRIPT_TYPE::BOSSENTERSCRIPT)
{
	SetActive(false);
}

CBossEnterScript::~CBossEnterScript()
{
}


void CBossEnterScript::begin()
{
}

void CBossEnterScript::tick()
{
	if (!IsActive()) return;
	if (Animator2D()->GetCurAnim()->IsFinish()) {
		Animator2D()->GetCurAnim()->Reset();
		ChangeState((UINT)SCRIPT_TYPE::BOSSATTACKSCRIPT, false);
	}
}

void CBossEnterScript::Enter()
{
	Animator2D()->SetSamplerState(1);
	Animator2D()->Play(L"Boss_Clap", false);

	CGameObject* BossUI = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"BossUI");
	CBossUIScript* UIScript = BossUI->GetScript<CBossUIScript>();
	UIScript->Activate();

	CGameObject* BossHP = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"BossHP");
	CBossHPScript* HPScript = BossHP->GetScript<CBossHPScript>();
	HPScript->Activate();
}

void CBossEnterScript::Exit()
{
	Animator2D()->GetCurAnim()->Reset();
}

