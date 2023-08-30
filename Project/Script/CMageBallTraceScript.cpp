#include "pch.h"
#include "CMageBallTraceScript.h"
#include "CMageBallScript.h"
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim2D.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

CMageBallTraceScript::CMageBallTraceScript()
	:CScript((UINT)SCRIPT_TYPE::MAGEBALLTRACESCRIPT)
{
	SetActive(false);
}

CMageBallTraceScript::~CMageBallTraceScript()
{
}


void CMageBallTraceScript::begin()
{
	
}

void CMageBallTraceScript::tick()
{
	if (!IsActive()) return;
	CGameObject* Player = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"Player");
	Vec3 CurPos = Transform()->GetRelativePos();
	Vec3 PlayerPos = Player->Transform()->GetRelativePos();
	// calculate the slope of the line from A to B
	double slope = (PlayerPos.y - CurPos.y) / (PlayerPos.x - CurPos.x);
	// calculate the angle between the x-axis and the line in radians
	double angle = atan(slope);
	// convert radians to degrees
	angle = angle * 180.0 / XM_PI;
	// if the slope is negative, add 180 degrees to get the acute angle
	if (slope < 0) {
		angle += 180.f;
	}
	// if the slope is positive and y2 < y1, add 360 degrees
	if (PlayerPos.y < CurPos.y) {
		angle += 180.f;
	}
	Vec3 vRotation = (Vec3(0.f, 0.f, angle) / 180.f) * XM_PI;
	Transform()->SetRelativeRot(vRotation);

	m_fAttackCoolTime += DT;
	if (m_fAttackCoolTime > 2.0f) {
		ChangeState((UINT)SCRIPT_TYPE::MAGEBALLATTACKSCRIPT, false);
	}
}

void CMageBallTraceScript::Enter()
{
	m_fAttackCoolTime = 0.f;
	Animator2D()->Play(L"WizardBall_Change", false);
	Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\MageFireballForm.wav");
	pSound->Play(1, 0.2, true);
}

void CMageBallTraceScript::Exit()
{
	m_fAttackCoolTime = 0.f;
	Animator2D()->GetCurAnim()->Reset();
}


