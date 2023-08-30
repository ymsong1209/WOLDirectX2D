#include "pch.h"
#include "CHomeFloorScript.h"

CHomeFloorScript::CHomeFloorScript()
	:CScript((UINT)SCRIPT_TYPE::HOMEFLOORSCRIPT)
{
}

CHomeFloorScript::~CHomeFloorScript()
{
}


void CHomeFloorScript::tick()
{
}

void CHomeFloorScript::begin()
{
	MeshRender()->GetDynamicMaterial();
	Ptr<CTexture> Floor = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\Map\\HomeFloor.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, Floor);

	Ptr<CSound> Bgm = CResMgr::GetInst()->FindRes<CSound>(L"sound\\PlayerRoom.wav");
	Bgm->Play(0, 0.2, true);
}

void CHomeFloorScript::SaveToLevelFile(FILE* _File)
{
}

void CHomeFloorScript::LoadFromLevelFile(FILE* _FILE)
{
	MeshRender()->GetDynamicMaterial();
	Ptr<CTexture> Floor = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\Map\\HomeFloor.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, Floor);
}

