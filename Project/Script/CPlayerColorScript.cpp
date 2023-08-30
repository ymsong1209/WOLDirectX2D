#include "pch.h"
#include "CPlayerColorScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CGameObject.h>


CPlayerColorScript::CPlayerColorScript()
	: CScript((UINT)SCRIPT_TYPE::PLAYERCOLORSCRIPT)
	, m_vColor()
{
	AddScriptParam(SCRIPT_PARAM::VEC4, &m_vColor, "Color");
}

CPlayerColorScript::~CPlayerColorScript()
{
}

void CPlayerColorScript::begin()
{
}

void CPlayerColorScript::tick()
{
	CLevel* CurLevel = CLevelMgr::GetInst()->GetCurLevel();
	CGameObject* Player = CurLevel->FindObjectByName(L"Player");
	Player->MeshRender()->GetDynamicMaterial()->SetScalarParam(VEC4_0, m_vColor);

	if (KEY_PRESSED(KEY::Z))
	{
		Vec3 vRot = Transform()->GetRelativeRot();
		vRot.z += DT * XM_PI;
		Transform()->SetRelativeRot(vRot);
	}
	if (KEY_PRESSED(KEY::X))
	{
		Vec3 vScale = Transform()->GetRelativeScale();
		vScale.x += 1 * DT;
		vScale.y += DT;
		vScale.z += DT;
		Transform()->SetRelativeScale(vScale);
	}

}