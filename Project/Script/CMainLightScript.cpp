#include "pch.h"
#include "CMainLightScript.h"

CMainLightScript::CMainLightScript()
	:CScript((UINT)SCRIPT_TYPE::MAINLIGHTSCRIPT)
	,m_bDark(false)
	,m_fTime(1.0f)
	,m_fAccTime(0.f)
{
}

CMainLightScript::~CMainLightScript()
{
}

void CMainLightScript::begin()
{
}

void CMainLightScript::tick()
{
	m_fTime += DT;
	m_fAccTime += DT;
	if (m_bDark) {
		float pow = 1.0 - m_fTime;
		if (pow < 0.3f) pow = 0.3f;
		Light2D()->SetLightDiffuse(Vec3(pow, pow, pow));
		if (m_fAccTime > 6.0f) {
			SetToDay();
		}
	}
	else {
		float pow = 0.3f + m_fTime;
		if (pow > 1.0f) pow = 1.0f;
		Light2D()->SetLightDiffuse(Vec3(pow, pow, pow));
	}
}

void CMainLightScript::SetToDark()
{
	m_bDark = true;
	m_fTime = 0.f;
	m_fAccTime = 0.f;
}

void CMainLightScript::SetToDay()
{
	m_bDark = false;
	m_fTime = 0.f;
	m_fAccTime = 0.f;
}

