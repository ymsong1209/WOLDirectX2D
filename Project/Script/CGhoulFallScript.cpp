#include "pch.h"
#include "CGhoulFallScript.h"
#include "CGhoulScript.h"
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim2D.h>

CGhoulFallScript::CGhoulFallScript()
	:CScript((UINT)SCRIPT_TYPE::GHOULFALLSCRIPT)
	, m_fFalltime(0.f)
{
	SetActive(false);
}

CGhoulFallScript::~CGhoulFallScript()
{

}
void CGhoulFallScript::begin()
{
}

void CGhoulFallScript::tick()
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

void CGhoulFallScript::Enter()
{
	CGhoulScript* GhoulMainScript = GetOwner()->GetScript<CGhoulScript>();
	GhoulMainScript->SetFall(true);
	Vec3 Pos = Transform()->GetRelativePos();
	Transform()->SetRelativePos(Vec3(Pos.x, Pos.y, 550.f));
	GhoulMainScript->SetGhoulDir(DIR_RIGHT);
	if (GhoulMainScript->GetGhoulDir() & DIR_LEFT) {
		float m_fDegree = 0.f / 180.f * XM_PI;
		Transform()->SetRelativeRot(Vec3(0.f, m_fDegree, 0.f));
		Animator2D()->Play(L"GhoulIdle_Left", true);
	}
	else {
		float m_fDegree = 180.f / 180.f * XM_PI;
		Transform()->SetRelativeRot(Vec3(0.f, m_fDegree, 0.f));
		Animator2D()->Play(L"GhoulIdle_Left", true);
	}
}

void CGhoulFallScript::Exit()
{
}