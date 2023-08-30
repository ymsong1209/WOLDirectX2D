#include "pch.h"
#include "CPlayerFaceUIScript.h"
#include <Engine/CResMgr.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include "CPlayerScript.h"

CPlayerFaceUIScript::CPlayerFaceUIScript()
	:CScript((UINT)SCRIPT_TYPE::PLAYERFACEUISCRIPT)
{
}

CPlayerFaceUIScript::~CPlayerFaceUIScript()
{
}


void CPlayerFaceUIScript::begin()
{
}

void CPlayerFaceUIScript::tick()
{
	Transform()->SetRelativeScale(Vec3(500.f, 120.f, 1.f));
	Transform()->SetRelativePos(Vec3(-536.f, 359.f, 1.f));

	CGameObject* Player = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"Player");
	CPlayerScript* Script = Player->GetScript<CPlayerScript>();
	Vec4 Color = Script->GetCapeColor();

	MeshRender()->GetMaterial()->SetScalarParam(VEC4_1, Color);
	int i = 1;
	MeshRender()->GetMaterial()->SetScalarParam(INT_7, &i);
}

void CPlayerFaceUIScript::SaveToLevelFile(FILE* _File)
{
}

void CPlayerFaceUIScript::LoadFromLevelFile(FILE* _File)
{
	MeshRender()->GetDynamicMaterial();
	Ptr<CTexture> Face = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\Player_UI.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, Face);
}

