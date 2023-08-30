#include "pch.h"
#include "CMageBallScript.h"
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim2D.h>

CMageBallScript::CMageBallScript()
	:CScript((UINT)SCRIPT_TYPE::MAGEBALLSCRIPT)
	,m_bIsDeadState(false)
{
}

CMageBallScript::~CMageBallScript()
{
}


void CMageBallScript::begin()
{
	Animator2D()->LoadAnim(L"animation\\enemy\\Wizard\\WizardBall_Idle.anim");
	Animator2D()->LoadAnim(L"animation\\enemy\\Wizard\\WizardBall_Change.anim");
	Animator2D()->LoadAnim(L"animation\\enemy\\Wizard\\WizardBall_Attack.anim");
	Animator2D()->LoadAnim(L"animation\\enemy\\Wizard\\WizardBall_Spawn.anim");
	ChangeState((UINT)SCRIPT_TYPE::MAGEBALLSPAWNSCRIPT, false);
}

void CMageBallScript::tick()
{
}

void CMageBallScript::Enter()
{
}

void CMageBallScript::Exit()
{
}

void CMageBallScript::BeginOverlap(CCollider2D* _Other)
{

}

void CMageBallScript::OnOverlap(CCollider2D* _Other)
{
}

void CMageBallScript::EndOverlap(CCollider2D* _Other)
{
}

