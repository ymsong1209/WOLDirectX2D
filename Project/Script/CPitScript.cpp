#include "pch.h"
#include "CPitScript.h"

CPitScript::CPitScript()
	: CScript((UINT)SCRIPT_TYPE::PITSCRIPT)
{
}

CPitScript::~CPitScript()
{
}


void CPitScript::begin()
{
}

void CPitScript::tick()
{
}

void CPitScript::SaveToLevelFile(FILE* _File)
{
}

void CPitScript::LoadFromLevelFile(FILE* _FILE)
{
	MeshRender()->GetDynamicMaterial();
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\Map\\Pit.png"));
}


