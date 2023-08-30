#include "pch.h"
#include "CHomeOverlayScript.h"

CHomeOverlayScript::CHomeOverlayScript()
	:CScript((UINT)SCRIPT_TYPE::HOMEOVERLAYSCRIPT)
{
}

CHomeOverlayScript::~CHomeOverlayScript()
{
}


void CHomeOverlayScript::tick()
{
}

void CHomeOverlayScript::begin()
{
	MeshRender()->GetDynamicMaterial();
	Ptr<CTexture> Overlay = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\Map\\HomeOverLay.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, Overlay);
}

void CHomeOverlayScript::SaveToLevelFile(FILE* _File)
{
}

void CHomeOverlayScript::LoadFromLevelFile(FILE* _FILE)
{
	MeshRender()->GetDynamicMaterial();
	Ptr<CTexture> Overlay = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\Map\\HomeOverLay.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, Overlay);
}

