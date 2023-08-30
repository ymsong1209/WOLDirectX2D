#include "pch.h"
#include "CPlayerSkillBarScript.h"

CPlayerSkillBarScript::CPlayerSkillBarScript()
	:CScript((UINT)SCRIPT_TYPE::PLAYERSKILLBARSCRIPT)
{
}

CPlayerSkillBarScript::~CPlayerSkillBarScript()
{
}

void CPlayerSkillBarScript::begin()
{
	Ptr<CTexture>  SkillBar = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\SkillBar.png");
	MeshRender()->GetDynamicMaterial();
	MeshRender()->GetDynamicMaterial()->SetTexParam(TEX_0, SkillBar);
}

void CPlayerSkillBarScript::tick()
{
}

void CPlayerSkillBarScript::SaveToLevelFile(FILE* _File)
{
}

void CPlayerSkillBarScript::LoadFromLevelFile(FILE* _File)
{
	Ptr<CTexture>  SkillBar = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\SkillBar.png");
	MeshRender()->GetDynamicMaterial();
	MeshRender()->GetDynamicMaterial()->SetTexParam(TEX_0, SkillBar);
}
