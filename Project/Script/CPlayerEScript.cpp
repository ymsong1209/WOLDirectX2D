#include "pch.h"
#include "CPlayerEScript.h"
#include "CPlayerScript.h"


CPlayerEScript::CPlayerEScript()
	:CScript((UINT)SCRIPT_TYPE::PLAYERESCRIPT)
{
}

CPlayerEScript::~CPlayerEScript()
{
}

void CPlayerEScript::begin()
{
	MeshRender()->GetDynamicMaterial();
}

void CPlayerEScript::tick()
{
	CGameObject* Player = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"Player");
	CPlayerScript* PlayerMainScript = Player->GetScript<CPlayerScript>();
	PLAYER_SKILL Skill = PlayerMainScript->GetESkill();
	m_fCoolTime = PlayerMainScript->GetECoolTime();
	m_fCurCoolTime = PlayerMainScript->GetECurCoolTime();
	switch (Skill)
	{
	case PLAYER_SKILL::NORMALATTACK: {
		m_pCurSkill = m_pNormalAttack;
	}
								   break;
	case PLAYER_SKILL::SNOWFLAKE: {
		m_pCurSkill = m_pIceCrystal;
	}
								break;
	case PLAYER_SKILL::DRAGONBREATH: {
		m_pCurSkill = m_pFireDragon;
	}
								   break;
	case PLAYER_SKILL::METEOR: {
		m_pCurSkill = m_pMeteor;
	}
							 break;
	case PLAYER_SKILL::WATERBALL: {
		if (PlayerMainScript->GetStat().CurMP > 99.f) {
			m_pCurSkill = m_pChaosBall;
		}
		else {
			m_pCurSkill = m_pWaterBall;
		}
	}
								break;
	case PLAYER_SKILL::NONE:
	{
		m_pCurSkill = m_pNone;
	}
	break;
	case PLAYER_SKILL::END:
		break;
	default:
		break;
	}

	//CurCoolTime이 0초이면 다시 재생할 수 있음 -> scalarparam에는 반대로 넣어줘야함
	if (m_fCoolTime != 0.f) {
		m_fCoolPercentage = 1.f - m_fCurCoolTime / m_fCoolTime;
	}
	else {
		m_fCoolPercentage = 1.f;
	}


	MeshRender()->GetMaterial()->SetTexParam(TEX_0, m_pCurSkill);
	MeshRender()->GetMaterial()->SetScalarParam(FLOAT_0, &m_fCoolPercentage);
}

void CPlayerEScript::SaveToLevelFile(FILE* _File)
{
}

void CPlayerEScript::LoadFromLevelFile(FILE* _File)
{
	MeshRender()->GetDynamicMaterial();
	m_pNormalAttack = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\NORMAL_ATTACK_ICON.png");
	m_pFireDragon = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\FIRE_DRAGON_ICON.png");
	m_pIceCrystal = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\ICE_CRYSTAL_ICON.png");
	m_pMeteor = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\Meteor.png");
	m_pWaterBall = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\WATERBALL_ICON.png");
	m_pChaosBall = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\CHAOSBALL_ICON.png");
	m_pNone = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\SkillBtn.png");
}



