#include "pch.h"
#include "CWardrobeUIScript.h"

CWardrobeUIScript::CWardrobeUIScript()
	:CScript((UINT)SCRIPT_TYPE::WARDROBEUISCRIPT)
	,m_bOpen(false)
{
}

CWardrobeUIScript::~CWardrobeUIScript()
{

}
void CWardrobeUIScript::tick()
{
	
}

void CWardrobeUIScript::begin()
{
	MeshRender()->GetDynamicMaterial();
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, nullptr);
}

void CWardrobeUIScript::SaveToLevelFile(FILE* _File)
{
}

void CWardrobeUIScript::LoadFromLevelFile(FILE* _FILE)
{
	MeshRender()->GetDynamicMaterial();
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, nullptr);
}

void CWardrobeUIScript::Activate()
{
	m_bOpen = true;
	Ptr<CTexture> UI = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\wardrobe.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, UI);
}

void CWardrobeUIScript::Deactivate()
{
	m_bOpen = false;
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, nullptr);
}



