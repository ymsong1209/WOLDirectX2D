#include "pch.h"
#include "CWardrobeScript.h"
#include <Engine/CKeyMgr.h>
#include "CWardrobeUIScript.h"
#include "CWardrobeArrowScript.h"

CWardrobeScript::CWardrobeScript()
	:CScript((UINT)SCRIPT_TYPE::WARDROBESCRIPT)
	,m_bOpen(false)
{

}

CWardrobeScript::~CWardrobeScript()
{
}

void CWardrobeScript::tick()
{
}

void CWardrobeScript::begin()
{
	MeshRender()->GetDynamicMaterial();
	Ptr<CTexture> WardrobeClosed = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\WardrobeClosed.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, WardrobeClosed);
}

void CWardrobeScript::BeginOverlap(CCollider2D* _Other)
{
	CGameObject* WardrobeUI = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"WardrobeUI");
	CWardrobeUIScript* UIScript = WardrobeUI->GetScript<CWardrobeUIScript>();
	if (UIScript->GetOpen() == false) {
		UIScript->Activate();
	}

	CGameObject* ArrowUI = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"WardrobeArrowUI");
	CWardrobeArrowScript* ArrowUIScript = ArrowUI->GetScript<CWardrobeArrowScript>();
	if (ArrowUIScript->GetOpen() == false) {
		ArrowUIScript->Activate();
	}

	MeshRender()->GetDynamicMaterial();
	Ptr<CTexture> WardrobeOpen = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\WardrobeOpen.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, WardrobeOpen);
}

void CWardrobeScript::OnOverlap(CCollider2D* _Other)
{
	CGameObject* WardrobeUI = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"WardrobeUI");
	CWardrobeUIScript* UIScript = WardrobeUI->GetScript<CWardrobeUIScript>();
	if (UIScript->GetOpen() == false) {
		UIScript->Activate();
	}

	CGameObject* ArrowUI = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"WardrobeArrowUI");
	CWardrobeArrowScript* ArrowUIScript = ArrowUI->GetScript<CWardrobeArrowScript>();
	if (ArrowUIScript->GetOpen() == false) {
		ArrowUIScript->Activate();
	}

	MeshRender()->GetDynamicMaterial();
	Ptr<CTexture> WardrobeOpen = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\WardrobeOpen.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, WardrobeOpen);
}

void CWardrobeScript::EndOverlap(CCollider2D* _Other)
{
	CGameObject* WardrobeUI = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"WardrobeUI");
	CWardrobeUIScript* UIScript = WardrobeUI->GetScript<CWardrobeUIScript>();
	if (UIScript->GetOpen() == true) {
		UIScript->Deactivate();
	}

	CGameObject* ArrowUI = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"WardrobeArrowUI");
	CWardrobeArrowScript* ArrowUIScript = ArrowUI->GetScript<CWardrobeArrowScript>();
	if (ArrowUIScript->GetOpen() == true) {
		ArrowUIScript->Deactivate();
	}

	MeshRender()->GetDynamicMaterial();
	Ptr<CTexture> WardrobeClosed = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\WardrobeClosed.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, WardrobeClosed);
}

void CWardrobeScript::SaveToLevelFile(FILE* _File)
{
}

void CWardrobeScript::LoadFromLevelFile(FILE* _FILE)
{
	MeshRender()->GetDynamicMaterial();
	Ptr<CTexture> WardrobeClosed = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\WardrobeClosed.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, WardrobeClosed);
}



