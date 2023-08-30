#include "pch.h"
#include "CMainMenuScript.h"
#include <Engine/CDevice.h>

CMainMenuScript::CMainMenuScript()
	:CScript((UINT)SCRIPT_TYPE::MAINMENUSCRIPT)
{
}

CMainMenuScript::~CMainMenuScript()
{
}

void CMainMenuScript::begin()
{
	Ptr<CTexture> BG = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\MainMenu.png");
	MeshRender()->GetDynamicMaterial();
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, BG);

	Vec2 Scale = CDevice::GetInst()->GetRenderResolution();
	Transform()->SetRelativeScale(Scale.x, Scale.y, 1.f);
}

void CMainMenuScript::tick()
{
}

void CMainMenuScript::SaveToLevelFile(FILE* _File)
{
}

void CMainMenuScript::LoadFromLevelFile(FILE* _File)
{
	Ptr<CTexture> BG = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\MainMenu.png");
	MeshRender()->GetDynamicMaterial();
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, BG);

	Vec2 Scale = CDevice::GetInst()->GetRenderResolution();
	Transform()->SetRelativeScale(Scale.x, Scale.y, 1.f);
}


