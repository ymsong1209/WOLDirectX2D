#include "pch.h"
#include "CMerchantRugScript.h"


CMerchantRugScript::CMerchantRugScript()
	:CScript((UINT)SCRIPT_TYPE::MERCHANTRUGSCRIPT)
{
}

CMerchantRugScript::~CMerchantRugScript()
{
}

void CMerchantRugScript::begin()
{
	MeshRender()->GetDynamicMaterial();
	Ptr<CTexture> Rug = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\particles\\Rug.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, Rug);
	int i = 1;
	MeshRender()->GetMaterial()->SetScalarParam(INT_7, &i);
}

void CMerchantRugScript::tick()
{
}

void CMerchantRugScript::SaveToLevelFile(FILE* _File)
{
}

void CMerchantRugScript::LoadFromLevelFile(FILE* _FILE)
{
	MeshRender()->GetDynamicMaterial();
	Ptr<CTexture> Rug = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\particles\\Rug.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, Rug);
	int i = 1;
	MeshRender()->GetMaterial()->SetScalarParam(INT_7, &i);
}

