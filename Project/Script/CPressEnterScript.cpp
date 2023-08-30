#include "pch.h"
#include "CPressEnterScript.h"
#include <Engine/CKeyMgr.h>
#include <Engine/CEventMgr.h>

#include "CScriptLevelSaveLoad.h"

CPressEnterScript::CPressEnterScript()
	:CScript((UINT)SCRIPT_TYPE::PRESSENTERSCRIPT)
	, m_fAlphaCoefficient(1.0f)

{
}

CPressEnterScript::~CPressEnterScript()
{
}


void CPressEnterScript::begin()
{
	Ptr<CTexture> UI = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\Press_Enter_Key.png");
	MeshRender()->GetDynamicMaterial();
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, UI);

	m_pMenuBGM = CResMgr::GetInst()->FindRes<CSound>(L"sound\\TitleScreen.wav");
	m_pMenuBGM->Play(0, 0.2, false);
}

void CPressEnterScript::tick()
{
	m_fTime += DT;
	if (1.0 <= m_fTime)
	{
		m_fAlphaCoefficient = m_fAlphaCoefficient * -1;
		m_fTime = 0.f;
	}
	m_fAlpha = m_fAlpha + DT * m_fAlphaCoefficient;
	if (m_fAlpha > 1.0f) {
		m_fAlpha = 1.0f;
	}
	MeshRender()->GetMaterial()->SetScalarParam(FLOAT_0, &m_fAlpha);

	if (KEY_TAP(KEY::ENTER)) {
		CLevel* pLoadedLevel = CScriptLevelSaveLoad::LoadLevel(L"level\\HomeLevel.lv");

		tEvent evn = {};
		evn.Type = EVENT_TYPE::LEVEL_CHANGE;
		evn.wParam = (DWORD_PTR)pLoadedLevel;

		CEventMgr::GetInst()->AddEvent(evn);
	}
}

void CPressEnterScript::SaveToLevelFile(FILE* _File)
{
}

void CPressEnterScript::LoadFromLevelFile(FILE* _File)
{
}


