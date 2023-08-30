#include "pch.h"
#include "CWallScript.h"

CWallScript::CWallScript()
	: CScript((UINT)SCRIPT_TYPE::WALLSCRIPT)
{
}

CWallScript::~CWallScript()
{
}

void CWallScript::begin()
{
}

void CWallScript::tick()
{
}

void CWallScript::SaveToLevelFile(FILE* _File)
{
}

void CWallScript::LoadFromLevelFile(FILE* _FILE)
{
	MeshRender()->GetDynamicMaterial();
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\Map\\Wall.png"));
}



