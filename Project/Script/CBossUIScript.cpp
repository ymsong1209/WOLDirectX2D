#include "pch.h"
#include "CBossUIScript.h"

CBossUIScript::CBossUIScript()
	:CScript((UINT)SCRIPT_TYPE::BOSSUISCRIPT)
{
}

CBossUIScript::~CBossUIScript()
{
}


void CBossUIScript::begin()
{
	MeshRender()->GetDynamicMaterial();
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, nullptr);
	int i = 1;
	MeshRender()->GetMaterial()->SetScalarParam(INT_7, &i);
}

void CBossUIScript::tick()
{
	int i = 1;
	MeshRender()->GetMaterial()->SetScalarParam(INT_7, &i);
}

void CBossUIScript::SaveToLevelFile(FILE* _File)
{
}

void CBossUIScript::LoadFromLevelFile(FILE* _File)
{
	Ptr<CTexture> UITex = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\BossUI.png");
	MeshRender()->GetDynamicMaterial();
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, UITex);
}

void CBossUIScript::Activate()
{
	m_bUIActive = true;
	Ptr<CTexture> UITex = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\BossUI.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, UITex);
}

void CBossUIScript::Deactivate()
{
	m_bUIActive = false;
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, nullptr);

}

