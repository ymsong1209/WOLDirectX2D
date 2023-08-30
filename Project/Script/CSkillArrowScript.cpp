#include "pch.h"
#include "CSkillArrowScript.h"
#include <Engine/CKeyMgr.h>
#include "CSelectedSkillSlotScript.h"

CSkillArrowScript::CSkillArrowScript()
	:CScript((UINT)SCRIPT_TYPE::SKILLARROWSCRIPT)
	,m_bUIActive(false)
	,m_pArrowTex(nullptr)
	,m_iCurBtn(0)
{
	AddScriptParam(SCRIPT_PARAM::INT, &m_iCurBtn, "CurArrowNum");
}

CSkillArrowScript::~CSkillArrowScript()
{
}

void CSkillArrowScript::begin()
{
	m_iCurBtn = 0;
	m_bUIActive = false;
	MeshRender()->GetDynamicMaterial();
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, nullptr);
}

void CSkillArrowScript::tick()
{
	if (m_bUIActive) {
		CGameObject* Player = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"Player");
		CPlayerScript* PlayerMainScript = Player->GetScript<CPlayerScript>();
		if (m_iCurBtn == 0) {
			Transform()->SetRelativePos(Vec3(-331.f, -77.f, 1.f));
			Transform()->SetRelativeRot(Vec3(XMConvertToRadians(180.f), 0.f, 0.f));
		}
		else if (m_iCurBtn == 1) {
			Transform()->SetRelativePos(Vec3(-66.f, -77.f, 1.f));
			Transform()->SetRelativeRot(Vec3(XMConvertToRadians(180.f), 0.f, 0.f));
		}
		else if (m_iCurBtn == 2) {
			Transform()->SetRelativePos(Vec3(63.f, -77.f, 1.f));
			Transform()->SetRelativeRot(Vec3(XMConvertToRadians(180.f), 0.f, 0.f));
		}
		else if (m_iCurBtn == 3) {
			Transform()->SetRelativePos(Vec3(197.f, -77.f, 1.f));
			Transform()->SetRelativeRot(Vec3(XMConvertToRadians(180.f), 0.f, 0.f));
		}
		else if (m_iCurBtn == 4) {
			Transform()->SetRelativePos(Vec3(422.f, 10.f, 1.f));
			Transform()->SetRelativeRot(Vec3(XMConvertToRadians(180.f), 0.f, XMConvertToRadians(90.f)));
		}


		CGameObject* SelectedSkill = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"SelectedSkillSlot");
		CSelectedSkillSlotScript* SelectedSkillScript = SelectedSkill->GetScript<CSelectedSkillSlotScript>();
		if (KEY_TAP(KEY::RIGHT)) {
			++m_iCurBtn;
			if (m_iCurBtn > 4) {
				m_iCurBtn = 4;
			}
			Ptr<CSound> MoveSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\MenuMove.wav");
			MoveSound->Play(1, 0.2, true);
		}
		else if (KEY_TAP(KEY::LEFT)) {
			--m_iCurBtn;
			if (m_iCurBtn < 0) {
				m_iCurBtn = 0;
			}
			Ptr<CSound> MoveSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\MenuMove.wav");
			MoveSound->Play(1, 0.3, true);
		}
	}
}

void CSkillArrowScript::SaveToLevelFile(FILE* _File)
{
}

void CSkillArrowScript::LoadFromLevelFile(FILE* _File)
{
	m_pArrowTex = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\ArrowLeftLarge.png");
	MeshRender()->GetDynamicMaterial();
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, m_pArrowTex);
}

void CSkillArrowScript::Activate()
{
	m_bUIActive = true;
	m_iCurBtn = 0;
	m_pArrowTex = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\ArrowLeftLarge.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, m_pArrowTex);
}

void CSkillArrowScript::Deactivate()
{
	m_bUIActive = false;
	m_iCurBtn = 0;
	m_pArrowTex = nullptr;
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, m_pArrowTex);
}


