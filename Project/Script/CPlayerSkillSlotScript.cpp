#include "pch.h"
#include "CPlayerSkillSlotScript.h"
#include "CPlayerScript.h"
#include "CESkillSlotScript.h"
#include "CLBtnSkillSlotScript.h"
#include "CQSkillSlotScript.h"
#include "CRBtnSkillSlotScript.h"
#include "CRSkillSlotScript.h"
#include "CSelectedSkillSlotScript.h"
#include "CSkillArrowScript.h"
#include "CSkillYellowArrowScript.h"

CPlayerSkillSlotScript::CPlayerSkillSlotScript()
	:CScript((UINT)SCRIPT_TYPE::PLAYERSKILLSLOTSCRIPT)
	,m_bUIActive(false)
{
}

CPlayerSkillSlotScript::~CPlayerSkillSlotScript()
{
}

void CPlayerSkillSlotScript::begin()
{
	MeshRender()->GetDynamicMaterial();
	m_bUIActive = false;
	m_pChangeSkill = nullptr;

}

void CPlayerSkillSlotScript::tick()
{
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, m_pChangeSkill);
}

void CPlayerSkillSlotScript::SaveToLevelFile(FILE* _File)
{
}

void CPlayerSkillSlotScript::LoadFromLevelFile(FILE* _File)
{
	m_pChangeSkill = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\ChangeSkill.png");
	MeshRender()->GetDynamicMaterial();
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, m_pChangeSkill);
}

void CPlayerSkillSlotScript::Activate()
{
	CGameObject* LBtnSkillSlot = CLevelMgr::GetInst()->FindParentObjectByName(L"LBtnSkillSlot");
	CLBtnSkillSlotScript* LBtnSkillSlotScript = LBtnSkillSlot->GetScript<CLBtnSkillSlotScript>();
	LBtnSkillSlotScript->Activate();

	CGameObject* RBtnSkillSlot = CLevelMgr::GetInst()->FindParentObjectByName(L"RBtnSkillSlot");
	CRBtnSkillSlotScript* RBtnSkillSlotScript = RBtnSkillSlot->GetScript<CRBtnSkillSlotScript>();
	RBtnSkillSlotScript->Activate();

	CGameObject* QSkillSlot = CLevelMgr::GetInst()->FindParentObjectByName(L"QSkillSlot");
	CQSkillSlotScript* QSkillSlotScript = QSkillSlot->GetScript<CQSkillSlotScript>();
	QSkillSlotScript->Activate();

	CGameObject* ESkillSlot = CLevelMgr::GetInst()->FindParentObjectByName(L"ESkillSlot");
	CESkillSlotScript* ESkillSlotScript = ESkillSlot->GetScript<CESkillSlotScript>();
	ESkillSlotScript->Activate();

	CGameObject* RSkillSlot = CLevelMgr::GetInst()->FindParentObjectByName(L"RSkillSlot");
	CRSkillSlotScript* RSkillSlotScript = RSkillSlot->GetScript<CRSkillSlotScript>();
	RSkillSlotScript->Activate();

	CGameObject* SelectedSkillSlot = CLevelMgr::GetInst()->FindParentObjectByName(L"SelectedSkillSlot");
	CSelectedSkillSlotScript* SelectedSkillSlotScript = SelectedSkillSlot->GetScript<CSelectedSkillSlotScript>();
	SelectedSkillSlotScript->Activate();

	CGameObject* SkillArrow = CLevelMgr::GetInst()->FindParentObjectByName(L"SkillArrow");
	CSkillArrowScript* ArrowScript = SkillArrow->GetScript<CSkillArrowScript>();
	ArrowScript->Activate();
	
	CGameObject* SkillYellowArrow = CLevelMgr::GetInst()->FindParentObjectByName(L"SkillYellowArrow");
	CSkillYellowArrowScript* YellowArrowScript = SkillYellowArrow->GetScript<CSkillYellowArrowScript>();
	YellowArrowScript->Activate();
	
	m_bUIActive = true;
	m_pChangeSkill = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\ChangeSkill.png");
}

void CPlayerSkillSlotScript::Deactivate()
{
	CGameObject* LBtnSkillSlot = CLevelMgr::GetInst()->FindParentObjectByName(L"LBtnSkillSlot");
	CLBtnSkillSlotScript* LBtnSkillSlotScript = LBtnSkillSlot->GetScript<CLBtnSkillSlotScript>();
	LBtnSkillSlotScript->Deactivate();

	CGameObject* RBtnSkillSlot = CLevelMgr::GetInst()->FindParentObjectByName(L"RBtnSkillSlot");
	CRBtnSkillSlotScript* RBtnSkillSlotScript = RBtnSkillSlot->GetScript<CRBtnSkillSlotScript>();
	RBtnSkillSlotScript->Deactivate();

	CGameObject* QSkillSlot = CLevelMgr::GetInst()->FindParentObjectByName(L"QSkillSlot");
	CQSkillSlotScript* QSkillSlotScript = QSkillSlot->GetScript<CQSkillSlotScript>();
	QSkillSlotScript->Deactivate();

	CGameObject* ESkillSlot = CLevelMgr::GetInst()->FindParentObjectByName(L"ESkillSlot");
	CESkillSlotScript* ESkillSlotScript = ESkillSlot->GetScript<CESkillSlotScript>();
	ESkillSlotScript->Deactivate();

	CGameObject* RSkillSlot = CLevelMgr::GetInst()->FindParentObjectByName(L"RSkillSlot");
	CRSkillSlotScript* RSkillSlotScript = RSkillSlot->GetScript<CRSkillSlotScript>();
	RSkillSlotScript->Deactivate();

	CGameObject* SelectedSkillSlot = CLevelMgr::GetInst()->FindParentObjectByName(L"SelectedSkillSlot");
	CSelectedSkillSlotScript* SelectedSkillSlotScript = SelectedSkillSlot->GetScript<CSelectedSkillSlotScript>();
	SelectedSkillSlotScript->Deactivate();

	CGameObject* SkillArrow = CLevelMgr::GetInst()->FindParentObjectByName(L"SkillArrow");
	CSkillArrowScript* ArrowScript = SkillArrow->GetScript<CSkillArrowScript>();
	ArrowScript->Deactivate();

	CGameObject* SkillYellowArrow = CLevelMgr::GetInst()->FindParentObjectByName(L"SkillYellowArrow");
	CSkillYellowArrowScript* YellowArrowScript = SkillYellowArrow->GetScript<CSkillYellowArrowScript>();
	YellowArrowScript->Deactivate();

	m_bUIActive = false;
	m_pChangeSkill = nullptr;
}



