#include "pch.h"
#include "CSkillYellowArrowScript.h"

CSkillYellowArrowScript::CSkillYellowArrowScript()
	:CScript((UINT)SCRIPT_TYPE::SKILLYELLOWARROWSCRIPT)
	, m_bUIActive(false)
	, m_pArrowTex(nullptr)
	, m_iCurBtn(-1)
{
	AddScriptParam(SCRIPT_PARAM::INT, &m_iCurBtn, "CurArrowNum");
}

CSkillYellowArrowScript::~CSkillYellowArrowScript()
{
}


void CSkillYellowArrowScript::begin()
{
	m_iCurBtn = -1;
	m_bUIActive = false;
	MeshRender()->GetDynamicMaterial();
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, nullptr);
}

void CSkillYellowArrowScript::tick()
{
	if (m_bUIActive) {
		if (m_iCurBtn != -1) {
			MeshRender()->GetMaterial()->SetTexParam(TEX_0, m_pArrowTex);
			if (m_iCurBtn == 0) {
				Transform()->SetRelativePos(Vec3(-331.f, -77.f, 2.f));
				Transform()->SetRelativeRot(Vec3(XMConvertToRadians(180.f), 0.f, 0.f));
			}
			else if (m_iCurBtn == 1) {
				Transform()->SetRelativePos(Vec3(-66.f, -77.f, 2.f));
				Transform()->SetRelativeRot(Vec3(XMConvertToRadians(180.f), 0.f, 0.f));
			}
			else if (m_iCurBtn == 2) {
				Transform()->SetRelativePos(Vec3(63.f, -77.f, 2.f));
				Transform()->SetRelativeRot(Vec3(XMConvertToRadians(180.f), 0.f, 0.f));
			}
			else if (m_iCurBtn == 3) {
				Transform()->SetRelativePos(Vec3(197.f, -77.f, 2.f));
				Transform()->SetRelativeRot(Vec3(XMConvertToRadians(180.f), 0.f, 0.f));
			}
			else if (m_iCurBtn == 4) {
				Transform()->SetRelativePos(Vec3(422.f, 10.f, 2.f));
				Transform()->SetRelativeRot(Vec3(XMConvertToRadians(180.f), 0.f, XMConvertToRadians(90.f)));
			}
		}
		else {
			MeshRender()->GetMaterial()->SetTexParam(TEX_0, nullptr);
		}
	}
	else {
		MeshRender()->GetMaterial()->SetTexParam(TEX_0, nullptr);
	}
}

void CSkillYellowArrowScript::SaveToLevelFile(FILE* _File)
{
}

void CSkillYellowArrowScript::LoadFromLevelFile(FILE* _File)
{
	m_pArrowTex = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\ArrowLeftLargeYellow.png");
	MeshRender()->GetDynamicMaterial();
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, m_pArrowTex);
}

void CSkillYellowArrowScript::Activate()
{
	m_bUIActive = true;
	m_iCurBtn = -1;
	m_pArrowTex = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\ArrowLeftLargeYellow.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, nullptr);
}

void CSkillYellowArrowScript::Deactivate()
{
	m_bUIActive = false;
	m_iCurBtn = -1;
	m_pArrowTex = nullptr;
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, nullptr);
}


