#include "pch.h"
#include "CMerchantScript.h"

CMerchantScript::CMerchantScript()
	:CScript((UINT)SCRIPT_TYPE::MERCHANTSCRIPT)
{
}

CMerchantScript::~CMerchantScript()
{
}

void CMerchantScript::begin()
{
	MeshRender()->GetDynamicMaterial();
	Ptr<CTexture> Merchant = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\particles\\Merchant.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, Merchant);
	int i = 1;
	MeshRender()->GetMaterial()->SetScalarParam(INT_7, &i);
}

void CMerchantScript::tick()
{
	//int i = 1;
	//MeshRender()->GetMaterial()->SetScalarParam(INT_7, &i);
}

void CMerchantScript::SaveToLevelFile(FILE* _File)
{
}

void CMerchantScript::LoadFromLevelFile(FILE* _FILE)
{
	MeshRender()->GetDynamicMaterial();
	Ptr<CTexture> Merchant = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\particles\\Merchant.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, Merchant);
	int i = 1;
	MeshRender()->GetMaterial()->SetScalarParam(INT_7, &i);
}

void CMerchantScript::Laugh()
{
	srand(time(NULL));
	if (rand() % 2 == 0) {
		Ptr<CSound> Laugh = CResMgr::GetInst()->FindRes<CSound>(L"sound\\Artisan.wav");
		Laugh->Play(1, 0.5, true);
	}
	else {
		Ptr<CSound> Laugh = CResMgr::GetInst()->FindRes<CSound>(L"sound\\Artisan1.wav");
		Laugh->Play(1, 0.5, true);
	}
	
}


