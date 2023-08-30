#include "pch.h"
#include "CMageBallIdleScript.h"
#include "CMageBallScript.h"
#include <Engine/CAnim2D.h>
#include <Engine/CAnimator2D.h>

CMageBallIdleScript::CMageBallIdleScript()
	:CScript((UINT)SCRIPT_TYPE::MAGEBALLIDLESCRIPT)
	,m_fAttackTime(0.f)
{
	SetActive(false);
}

CMageBallIdleScript::~CMageBallIdleScript()
{
}


void CMageBallIdleScript::begin()
{
}

void CMageBallIdleScript::tick()
{
	if (!IsActive()) return;
	m_fAttackTime += DT;
	if (m_fAttackTime > 3.0f) {
		ChangeState((UINT)SCRIPT_TYPE::MAGEBALLTRACESCRIPT, false);
	}
}

void CMageBallIdleScript::Enter()
{
	Animator2D()->Play(L"WizardBall_Idle", true);
	m_fAttackTime = 0.f;
}

void CMageBallIdleScript::Exit()
{
	m_fAttackTime = 0.f;
}

