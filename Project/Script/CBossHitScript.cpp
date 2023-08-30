#include "pch.h"
#include "CBossHitScript.h"
#include "CBossScript.h"
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim2D.h>
#include "CBossFlexScript.h"

CBossHitScript::CBossHitScript()
	:CScript((UINT)SCRIPT_TYPE::BOSSHITSCRIPT)
{
	SetActive(false);
}

CBossHitScript::~CBossHitScript()
{
}

void CBossHitScript::begin()
{
}

void CBossHitScript::tick()
{
	if (!IsActive()) return;
	m_fTime += DT;

	if (Animator2D()->GetCurAnim()->IsFinish()) {
		
		ChangeState((UINT)SCRIPT_TYPE::BOSSFLEXSCRIPT, false);
	}
}

void CBossHitScript::Enter()
{
	Animator2D()->Play(L"Boss_Hurt", false);
}

void CBossHitScript::Exit()
{
	Animator2D()->GetCurAnim()->Reset();
	CBossFlexScript* script = GetOwner()->GetScript<CBossFlexScript>();
	script->AddFlexTime(m_fTime);
	m_fTime = 0.f;
}


