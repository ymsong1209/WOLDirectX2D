#include "pch.h"
#include "CPotionScript.h"
#include "CPlayerScript.h"

CPotionScript::CPotionScript()
	:CScript((UINT)SCRIPT_TYPE::POTIONSCRIPT)
	,m_bFull(true)
{
}

CPotionScript::~CPotionScript()
{
}

void CPotionScript::begin()
{
	MeshRender()->GetDynamicMaterial();
	Ptr<CTexture> PotionFull = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\particles\\PotionFull.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, PotionFull);
}

void CPotionScript::tick()
{
}

void CPotionScript::SaveToLevelFile(FILE* _File)
{
}

void CPotionScript::LoadFromLevelFile(FILE* _FILE)
{
	MeshRender()->GetDynamicMaterial();
	Ptr<CTexture> PotionFull = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\particles\\PotionFull.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, PotionFull);
}

void CPotionScript::BeginOverlap(CCollider2D* _Other)
{
	if (m_bFull == false) return;
	if (KEY_TAP(KEY::ENTER)) {
		CGameObject* Player = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"Player");
		CPlayerScript* PlayerMainScript = Player->GetScript<CPlayerScript>();
		PlayerStat stat = PlayerMainScript->GetStat();
		stat.CurHP = 100.0f;
		PlayerMainScript->SetStat(stat);

		Ptr<CSound> HealSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\Heal.wav");
		HealSound->Play(1, 0.3, true);

		Drink();
	}
}

void CPotionScript::OnOverlap(CCollider2D* _Other)
{
	if (m_bFull == false) return;
	if (KEY_TAP(KEY::ENTER)) {
		CGameObject* Player = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"Player");
		CPlayerScript* PlayerMainScript = Player->GetScript<CPlayerScript>();
		PlayerStat stat = PlayerMainScript->GetStat();
		stat.CurHP = 100.0f;
		PlayerMainScript->SetStat(stat);

		Ptr<CSound> HealSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\Heal.wav");
		HealSound->Play(1, 0.6, true);

		Drink();
	}
}

void CPotionScript::EndOverlap(CCollider2D* _Other)
{
}

void CPotionScript::Drink()
{
	m_bFull = false;
	Ptr<CTexture> PotionEmpty = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\particles\\PotionEmpty.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, PotionEmpty);
}


