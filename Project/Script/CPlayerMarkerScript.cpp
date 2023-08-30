#include "pch.h"
#include "CPlayerMarkerScript.h"
#include "CPlayerScript.h"
#include "CMousePointerScript.h"

CPlayerMarkerScript::CPlayerMarkerScript()
	:CScript((UINT)SCRIPT_TYPE::PLAYERMARKERSCRIPT)
	,m_fAlpha(1.f)
{
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fAlpha, "Alpha");
}

CPlayerMarkerScript::~CPlayerMarkerScript()
{
}


void CPlayerMarkerScript::begin()
{
	MeshRender()->GetDynamicMaterial();
	Ptr<CTexture> Marker = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\particles\\PlayerMarker.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, Marker);
}

void CPlayerMarkerScript::tick()
{
	CGameObject* MousePointer = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"MousePointer");
	CMousePointerScript* MouseScript = MousePointer->GetScript<CMousePointerScript>();

	CGameObject* Player = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"Player");

	Vec3 MousePos = MouseScript->GetMousePos();
	Vec3 PlayerPos = Player->Transform()->GetRelativePos();

	
	// calculate the slope of the line from A to B
	double slope = (MousePos.y - PlayerPos.y) / (MousePos.x - PlayerPos.x);
	// calculate the angle between the x-axis and the line in radians
	double angle = atan(slope);
	// convert radians to degrees
	angle = angle * 180.0 / XM_PI;
	// if the slope is negative, add 180 degrees to get the acute angle
	if (slope < 0) {
		angle += 180.0;
	}
	// if the slope is positive and y2 < y1, add 360 degrees
	if (MousePos.y < PlayerPos.y) {
		angle += 180.0;
	}
	Vec3 vRotation = (Vec3(0.f, 0.f, angle) / 180.f) * XM_PI;
	
	Transform()->SetRelativeRot(vRotation);
	
	int i = 1;
	MeshRender()->GetMaterial()->SetScalarParam(INT_7, &i);
	MeshRender()->GetMaterial()->SetScalarParam(FLOAT_0, &m_fAlpha);
}

void CPlayerMarkerScript::SaveToLevelFile(FILE* _File)
{
}

void CPlayerMarkerScript::LoadFromLevelFile(FILE* _File)
{
	MeshRender()->GetDynamicMaterial();
	Ptr<CTexture> Marker = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\particles\\PlayerMarker.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, Marker);
}



