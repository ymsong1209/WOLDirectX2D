#include "pch.h"
#include "CBossWallScript.h"

CBossWallScript::CBossWallScript()
	: CScript((UINT)SCRIPT_TYPE::BOSSWALLSCRIPT)
{
}

CBossWallScript::~CBossWallScript()
{
}

void CBossWallScript::begin()
{
}

void CBossWallScript::tick()
{
}

void CBossWallScript::SaveToLevelFile(FILE* _File)
{
}

void CBossWallScript::LoadFromLevelFile(FILE* _FILE)
{
	MeshRender()->GetDynamicMaterial();
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\Map\\bosswall.png"));
}

