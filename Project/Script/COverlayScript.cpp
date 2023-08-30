#include "pch.h"
#include "COverlayScript.h"
#include <Engine/CMeshRender.h>



COverlayScript::COverlayScript()
	: CScript((UINT)SCRIPT_TYPE::OVERLAYSCRIPT)
{
}

COverlayScript::~COverlayScript()
{
}


void COverlayScript::begin()
{
}

void COverlayScript::tick()
{
}

void COverlayScript::SaveToLevelFile(FILE* _File)
{
}

void COverlayScript::LoadFromLevelFile(FILE* _FILE)
{
	GetOwner()->MeshRender()->GetDynamicMaterial();
	GetOwner()->MeshRender()->GetMaterial()->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\Map\\Overlay.png"));
}
