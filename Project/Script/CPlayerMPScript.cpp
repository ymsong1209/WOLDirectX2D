#include "pch.h"
#include "CPlayerMPScript.h"
#include "CPlayerScript.h"
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>


CPlayerMPScript::CPlayerMPScript()
	:CScript((UINT)SCRIPT_TYPE::PLAYERMPSCRIPT)
{
}

CPlayerMPScript::~CPlayerMPScript()
{
}

void CPlayerMPScript::begin()
{
	Ptr<CTexture> MpTex = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\UI_MANABAR.png");
	MeshRender()->GetDynamicMaterial()->SetTexParam(TEX_0, MpTex);
}

void CPlayerMPScript::tick()
{
	CGameObject* Player = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"Player");
	CPlayerScript* Script = Player->GetScript<CPlayerScript>();
	PlayerStat PStat = Script->GetStat();
	int mp = PStat.CurMP;
	Transform()->SetRelativeScale(Vec3(294.f / 100.f * (float)mp, 30.f, 1.f));
	Transform()->SetRelativePos(Vec3(-523.f - 294.f / 2.f + Transform()->GetRelativeScale().x / 2.f, 330.f, 2.f));
}

void CPlayerMPScript::SaveToLevelFile(FILE* _File)
{
}

void CPlayerMPScript::LoadFromLevelFile(FILE* _File)
{
	Ptr<CTexture> MpTex = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\UI_MANABAR.png");
	MeshRender()->GetDynamicMaterial()->SetTexParam(TEX_0, MpTex);
}


