#include "pch.h"
#include "CSwordManFallScript.h"
#include "CSwordManScript.h"
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim2D.h>

CSwordManFallScript::CSwordManFallScript()
	:CScript((UINT)SCRIPT_TYPE::SWORDMANFALLSCRIPT)
	,m_fFalltime(0.f)
{
	SetActive(false);
}

CSwordManFallScript::~CSwordManFallScript()
{

}
void CSwordManFallScript::begin()
{
}

void CSwordManFallScript::tick()
{
	if (!IsActive()) return;

	Vec3 Scale = Transform()->GetRelativeScale();
	Vec3 Rot = Transform()->GetRelativeRot();
	Scale.x -= DT * 200;
	Scale.y -= DT * 200;
	Rot.z += DT * 15;
	Transform()->SetRelativeScale(Scale);
	Transform()->SetRelativeRot(Rot);
	m_fFalltime += DT;
	if (m_fFalltime > 0.7f) {
		DestroyObject(GetOwner());
	}
}

void CSwordManFallScript::Enter()
{
	CSwordManScript* SwordManScript = GetOwner()->GetScript<CSwordManScript>();
	SwordManScript->SetFall(true);
	Vec3 Pos = Transform()->GetRelativePos();
	Transform()->SetRelativePos(Vec3(Pos.x, Pos.y, 550.f));
	SwordManScript->SetSwordManDir(DIR_RIGHT);
	if (SwordManScript->GetSwordManDir() & DIR_LEFT) {
		float m_fDegree = 0.f / 180.f * XM_PI;
		Transform()->SetRelativeRot(Vec3(0.f, m_fDegree, 0.f));
		Animator2D()->Play(L"SwordMan_Idle_Left", true);
	}
	else {
		float m_fDegree = 180.f / 180.f * XM_PI;
		Transform()->SetRelativeRot(Vec3(0.f, m_fDegree, 0.f));
		Animator2D()->Play(L"SwordMan_Idle_Left", true);
	}
}

void CSwordManFallScript::Exit()
{
}


