#include "pch.h"
#include "CPlayerHPScript.h"
#include "CPlayerScript.h"
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>


CPlayerHPScript::CPlayerHPScript()
	:CScript((UINT)SCRIPT_TYPE::PLAYERHPSCRIPT)
{
}

CPlayerHPScript::~CPlayerHPScript()
{
}


void CPlayerHPScript::begin()
{
	Ptr<CTexture> HpTex = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\UI_HPBAR.png");
	MeshRender()->GetDynamicMaterial()->SetTexParam(TEX_0, HpTex);
}

void CPlayerHPScript::tick()
{
	CGameObject* Player = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"Player");
	CPlayerScript* Script = Player->GetScript<CPlayerScript>();
	PlayerStat PStat = Script->GetStat();
	int hp = PStat.CurHP;
	Transform()->SetRelativeScale(Vec3(375.f / 100.f * (float)hp, 50.f, 1.f));
	Transform()->SetRelativePos(Vec3(-485.f - 375.f / 2.f + Transform()->GetRelativeScale().x / 2.f, 377.f, 2.f));
}

void CPlayerHPScript::SaveToLevelFile(FILE* _File)
{
}

void CPlayerHPScript::LoadFromLevelFile(FILE* _File)
{
	Ptr<CTexture> HpTex = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\UI_HPBAR.png");
	MeshRender()->GetDynamicMaterial()->SetTexParam(TEX_0, HpTex);
}

