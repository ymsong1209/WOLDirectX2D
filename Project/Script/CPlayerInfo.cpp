#include "pch.h"
#include "CPlayerInfo.h"

CPlayerInfo::CPlayerInfo()
	: m_ELBtnSkill(PLAYER_SKILL::NORMALATTACK)
	, m_ERBtnSkill(PLAYER_SKILL::NONE)
	, m_EQSkill(PLAYER_SKILL::NONE)
	, m_EESkill(PLAYER_SKILL::NONE)
	, m_ERSkill(PLAYER_SKILL::NONE)
	, m_fLBtnCoolTime(0.f)
	, m_fRBtnCoolTime(0.f)
	, m_fECoolTime(0.f)
	, m_fQCoolTime(0.f)
	, m_fRCoolTime(0.f)
{
	m_Stat.MaxHP = 100.f;
	m_Stat.MaxMP = 100.f;
	m_Stat.CurHP = 100.f;
	m_Stat.CurMP = 50.f;
	m_vCapeColor = Vec4(1.f, 1.f, 1.f, 1.f);

}
CPlayerInfo::~CPlayerInfo() {

}