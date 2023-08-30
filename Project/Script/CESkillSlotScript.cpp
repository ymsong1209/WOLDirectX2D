#include "pch.h"
#include "CESkillSlotScript.h"
#include "CPlayerScript.h"


CESkillSlotScript::CESkillSlotScript()
	:CScript((UINT)SCRIPT_TYPE::ESKILLSLOTSCRIPT)
	,m_bUIActive(false)
	,m_pNormalAttack(nullptr)
	,m_pFireDragon(nullptr)
	,m_pIceCrystal(nullptr)
	,m_pMeteor(nullptr)
	,m_pWaterBall(nullptr)
	,m_pChaosBall(nullptr)
	,m_pNone(nullptr)
	,m_pCurSkillTex(nullptr)
{
}

CESkillSlotScript::~CESkillSlotScript()
{
}


void CESkillSlotScript::begin()
{
	MeshRender()->GetDynamicMaterial();
	m_bUIActive = false;
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, nullptr);
}

void CESkillSlotScript::tick()
{
	if (m_bUIActive) {
		CGameObject* Player = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"Player");
		CPlayerScript* PlayerMainScript = Player->GetScript<CPlayerScript>();
		PLAYER_SKILL ESkill = PlayerMainScript->GetSkillPerBtn(3);
		switch (ESkill)
		{
		case PLAYER_SKILL::NORMALATTACK: {
			m_pCurSkillTex = m_pNormalAttack;
		}
									   break;
		case PLAYER_SKILL::SNOWFLAKE:
		{
			m_pCurSkillTex = m_pIceCrystal;
		}
		break;
		case PLAYER_SKILL::DRAGONBREATH: {
			m_pCurSkillTex = m_pFireDragon;
		}
									   break;
		case PLAYER_SKILL::METEOR: {
			m_pCurSkillTex = m_pMeteor;
		}
								 break;
		case PLAYER_SKILL::WATERBALL: {
			m_pCurSkillTex = m_pWaterBall;
		}
									break;
		case PLAYER_SKILL::NONE: {
			m_pCurSkillTex = m_pNone;
		}
							   break;
		case PLAYER_SKILL::END: {
			assert(nullptr);
		}
							  break;
		default:
			break;
		}

		MeshRender()->GetMaterial()->SetTexParam(TEX_0, m_pCurSkillTex);
	}
}

void CESkillSlotScript::SaveToLevelFile(FILE* _File)
{
}

void CESkillSlotScript::LoadFromLevelFile(FILE* _File)
{
	MeshRender()->GetDynamicMaterial();
	m_pNormalAttack = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\NORMAL_ATTACK_ICON.png");
	m_pFireDragon = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\FIRE_DRAGON_ICON.png");
	m_pIceCrystal = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\ICE_CRYSTAL_ICON.png");
	m_pMeteor = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\Meteor.png");
	m_pWaterBall = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\WATERBALL_ICON.png");
	m_pChaosBall = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\CHAOSBALL_ICON.png");
	m_pNone = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\SkillBtn.png");

	MeshRender()->GetMaterial()->SetTexParam(TEX_0, m_pNone);
}

void CESkillSlotScript::Activate()
{
	m_bUIActive = true;
	CGameObject* Player = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"Player");
	CPlayerScript* PlayerMainScript = Player->GetScript<CPlayerScript>();
	PLAYER_SKILL ESkill = PlayerMainScript->GetSkillPerBtn(3);
	switch (ESkill)
	{
	case PLAYER_SKILL::NORMALATTACK: {
		m_pCurSkillTex = m_pNormalAttack;
	}
		break;
	case PLAYER_SKILL::SNOWFLAKE:
	{
		m_pCurSkillTex = m_pIceCrystal;
	}
		break;
	case PLAYER_SKILL::DRAGONBREATH: {
		m_pCurSkillTex = m_pFireDragon;
	}
		break;
	case PLAYER_SKILL::METEOR: {
		m_pCurSkillTex = m_pMeteor;
	}
		break;
	case PLAYER_SKILL::WATERBALL: {
		m_pCurSkillTex = m_pWaterBall;
	}
		break;
	case PLAYER_SKILL::NONE: {
		m_pCurSkillTex = m_pNone;
	}
		break;
	case PLAYER_SKILL::END: {
		assert(nullptr);
	}
		break;
	default:
		break;
	}

	MeshRender()->GetMaterial()->SetTexParam(TEX_0, m_pCurSkillTex);
}

void CESkillSlotScript::Deactivate()
{
	m_bUIActive = false;
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, nullptr);
	m_pCurSkillTex = nullptr;
}

