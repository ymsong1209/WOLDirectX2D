#include "pch.h"
#include "CBossPitScript.h"

CBossPitScript::CBossPitScript()
	: CScript((UINT)SCRIPT_TYPE::BOSSPITSCRIPT)
{
}

CBossPitScript::~CBossPitScript()
{
}


void CBossPitScript::begin()
{
}

void CBossPitScript::tick()
{
}

void CBossPitScript::SaveToLevelFile(FILE* _File)
{
}

void CBossPitScript::LoadFromLevelFile(FILE* _FILE)
{
	MeshRender()->GetDynamicMaterial();
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\Map\\bossPit.png"));
}
