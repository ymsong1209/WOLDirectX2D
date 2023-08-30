#include "pch.h"
#include "CBossFloorScript.h"
#include "CMapScript.h"
#include <Engine/CAstarMgr.h>


CBossFloorScript::CBossFloorScript()
	: CScript((UINT)SCRIPT_TYPE::BOSSFLOORSCRIPT)
{

}

CBossFloorScript::~CBossFloorScript()
{
}


void CBossFloorScript::begin()
{
	
}

void CBossFloorScript::tick()
{

}


void CBossFloorScript::SaveToLevelFile(FILE* _File)
{
	
}

void CBossFloorScript::LoadFromLevelFile(FILE* _FILE)
{
	MeshRender()->GetDynamicMaterial();
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\Map\\bossFloor.png"));
}


