#include "pch.h"
#include "CBossFireflyScript.h"

CBossFireflyScript::CBossFireflyScript()
	:CScript((UINT)SCRIPT_TYPE::BOSSFIREFLYSCRIPT)
{
}

CBossFireflyScript::~CBossFireflyScript()
{
}


void CBossFireflyScript::begin()
{
	MeshRender()->GetDynamicMaterial();
	Ptr<CTexture> Firefly = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\particles\\firefly.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, Firefly);

}

void CBossFireflyScript::tick()
{
}

void CBossFireflyScript::SaveToLevelFile(FILE* _File)
{
}

void CBossFireflyScript::LoadFromLevelFile(FILE* _FILE)
{
	MeshRender()->GetDynamicMaterial();
	Ptr<CTexture> Firefly = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\particles\\firefly.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, Firefly);
}


