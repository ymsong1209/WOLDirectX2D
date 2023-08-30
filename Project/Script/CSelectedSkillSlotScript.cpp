#include "pch.h"
#include "CSelectedSkillSlotScript.h"
#include "CPlayerScript.h"
#include <Engine/CKeyMgr.h>
#include "CSkillArrowScript.h"
#include "CSkillYellowArrowScript.h"

CSelectedSkillSlotScript::CSelectedSkillSlotScript()
	:CScript((UINT)SCRIPT_TYPE::SELECTEDSKILLSLOTSCRIPT)
	,m_bUIActive(false)
	,m_pNormalAttack(nullptr)
	,m_pFireDragon(nullptr)
	,m_pIceCrystal(nullptr)
	,m_pMeteor(nullptr)
	,m_pWaterBall(nullptr)
	,m_pChaosBall(nullptr)
	,m_pNone(nullptr)
	,m_pCurSkillTex(nullptr)
	,m_pSelectedSkill(PLAYER_SKILL::NONE)
	,m_pSelectedAttackBtn(PLAYER_ATTACKBUTTON::NONE)
	,m_fSelectedSkillCoolTime(0.f)
	,m_iSelectedArrowNum(-1)
	,m_pDestSkill(PLAYER_SKILL::NONE)
	,m_pDestAttackBtn(PLAYER_ATTACKBUTTON::NONE)
	, m_fDestSkillCoolTime(0.f)
{
}

CSelectedSkillSlotScript::~CSelectedSkillSlotScript()
{
}


void CSelectedSkillSlotScript::begin()
{
	m_bUIActive = false;
	m_iSelectedArrowNum = -1;
	m_pSelectedSkill = PLAYER_SKILL::NONE;
	m_fSelectedSkillCoolTime = 0.f;
	m_pSelectedAttackBtn = PLAYER_ATTACKBUTTON::NONE;
	MeshRender()->GetDynamicMaterial();
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, nullptr);
}

void CSelectedSkillSlotScript::tick()
{
	if (m_bUIActive) {
		//현재 선택된 스킬 목록 표시
		switch (m_pSelectedSkill)
		{
		case PLAYER_SKILL::NORMALATTACK: {
			m_pCurSkillTex = m_pNormalAttack;
		}
			break;
		case PLAYER_SKILL::SNOWFLAKE: {
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

		if (KEY_TAP(KEY::ENTER)) {
			CGameObject* Arrow = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"SkillArrow");
			CSkillArrowScript* ArrowScript = Arrow->GetScript<CSkillArrowScript>();

			CGameObject* Player = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"Player");
			CPlayerScript* PlayerMainScript = Player->GetScript<CPlayerScript>();

			CGameObject* YellowArrow = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"SkillYellowArrow");
			CSkillYellowArrowScript* YellowArrowScript = YellowArrow->GetScript<CSkillYellowArrowScript>();

			int ArrowNum = ArrowScript->GetArrowNum();
			//같은걸 두번 골랐을 경우
			if (m_iSelectedArrowNum == ArrowNum) return;

			//선택 스킬 슬롯에 스킬이 설정되어있음
			if (m_iSelectedArrowNum != -1) {
				if (ArrowNum == 0) {
					m_pDestAttackBtn = PLAYER_ATTACKBUTTON::LBTN;
				}
				else if (ArrowNum == 1) {
					m_pDestAttackBtn = PLAYER_ATTACKBUTTON::RBTN;
				}
				else if (ArrowNum == 2) {
					m_pDestAttackBtn = PLAYER_ATTACKBUTTON::Q;
				}
				else if (ArrowNum == 3) {
					m_pDestAttackBtn = PLAYER_ATTACKBUTTON::E;
				}
				else if (ArrowNum == 4) {
					m_pDestAttackBtn = PLAYER_ATTACKBUTTON::R;
				}
				else {
					assert(nullptr);
				}

				m_pDestSkill = PlayerMainScript->GetSkillPerBtn(ArrowNum);
				m_fDestSkillCoolTime = PlayerMainScript->GetCoolTimePerSkill(ArrowNum);

				if (PlayerMainScript->ChangePlayerSkill(m_pDestAttackBtn, m_pDestSkill, m_fDestSkillCoolTime,
					m_pSelectedAttackBtn, m_pSelectedSkill, m_fSelectedSkillCoolTime) == 2) {
					//실패
					Ptr<CSound> SoundError = CResMgr::GetInst()->FindRes<CSound>(L"sound\\MenuError.wav");
					SoundError->Play(1, 0.3, true);
				}
				else {
					//성공
					Ptr<CSound> Equip = CResMgr::GetInst()->FindRes<CSound>(L"sound\\Equip.wav");
					m_iSelectedArrowNum = -1;
					m_pSelectedSkill = PLAYER_SKILL::NONE;
					m_fSelectedSkillCoolTime = 0.f;
					m_pSelectedAttackBtn = PLAYER_ATTACKBUTTON::NONE;
					Equip->Play(1, 0.3, true);
					YellowArrowScript->SetArrowNum(-1);
				}
			}
			//선택된 스킬이 없을 경우 arrow가 가리키고 있는 스킬을 들고옴
			else {
				//selectedArrowNum이 -1이여야함. 아무것도 들어있으면 안됨
				if (m_iSelectedArrowNum != -1) assert(nullptr);

				m_iSelectedArrowNum = ArrowNum;
				YellowArrowScript->SetArrowNum(m_iSelectedArrowNum);
				if (ArrowNum == 0) {
					m_pSelectedAttackBtn = PLAYER_ATTACKBUTTON::LBTN;
				}
				else if (ArrowNum == 1) {
					m_pSelectedAttackBtn = PLAYER_ATTACKBUTTON::RBTN;
				}
				else if (ArrowNum == 2) {
					m_pSelectedAttackBtn = PLAYER_ATTACKBUTTON::Q;
				}
				else if (ArrowNum == 3) {
					m_pSelectedAttackBtn = PLAYER_ATTACKBUTTON::E;
				}
				else if (ArrowNum == 4) {
					m_pSelectedAttackBtn = PLAYER_ATTACKBUTTON::R;
				}
				else {
					assert(nullptr);
				}
				
				m_pSelectedSkill =  PlayerMainScript->GetSkillPerBtn(ArrowNum);
				m_fSelectedSkillCoolTime =  PlayerMainScript->GetCoolTimePerSkill(ArrowNum);
			}
		}
		
	}
}

void CSelectedSkillSlotScript::SaveToLevelFile(FILE* _File)
{
}

void CSelectedSkillSlotScript::LoadFromLevelFile(FILE* _File)
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

void CSelectedSkillSlotScript::Activate()
{
	m_bUIActive = true;
	m_pSelectedSkill = PLAYER_SKILL::NONE;
	m_iSelectedArrowNum = -1;
	m_fSelectedSkillCoolTime = 0.f;
	m_pSelectedAttackBtn = PLAYER_ATTACKBUTTON::NONE;
	m_pCurSkillTex = m_pNone;
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, m_pCurSkillTex);
}

void CSelectedSkillSlotScript::Deactivate()
{
	m_bUIActive = false;
	m_pSelectedSkill = PLAYER_SKILL::NONE;
	m_iSelectedArrowNum = -1;
	m_fSelectedSkillCoolTime = 0.f;
	m_pSelectedAttackBtn = PLAYER_ATTACKBUTTON::NONE;
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, nullptr);
}


