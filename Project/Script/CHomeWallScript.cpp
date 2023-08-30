#include "pch.h"
#include "CHomeWallScript.h"

CHomeWallScript::CHomeWallScript()
	:CScript((UINT)SCRIPT_TYPE::HOMEWALLSCRIPT)
{
}

CHomeWallScript::~CHomeWallScript()
{
}


void CHomeWallScript::tick()
{
}

void CHomeWallScript::begin()
{
	MeshRender()->GetDynamicMaterial();
	Ptr<CTexture> HomeWall = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\Map\\HomeWall.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, HomeWall);
}

void CHomeWallScript::SaveToLevelFile(FILE* _File)
{
}

void CHomeWallScript::LoadFromLevelFile(FILE* _FILE)
{
	MeshRender()->GetDynamicMaterial();
	Ptr<CTexture> HomeWall = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\Map\\HomeWall.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, HomeWall);
}

