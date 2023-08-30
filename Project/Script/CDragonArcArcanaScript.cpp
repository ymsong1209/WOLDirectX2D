#include "pch.h"
#include "CDragonArcArcanaScript.h"
#include "CPlayerScript.h"
#include "CMerchantScript.h"

CDragonArcArcanaScript::CDragonArcArcanaScript()
	:CScript((UINT)SCRIPT_TYPE::DRAGONARCARCANASCRIPT)
{
}

CDragonArcArcanaScript::~CDragonArcArcanaScript()
{
}

void CDragonArcArcanaScript::begin()
{
	MeshRender()->GetDynamicMaterial();
	Ptr<CTexture> Arcana = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\DragonArcArcana.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, Arcana);
}

void CDragonArcArcanaScript::tick()
{
}

void CDragonArcArcanaScript::SaveToLevelFile(FILE* _File)
{
}

void CDragonArcArcanaScript::LoadFromLevelFile(FILE* _FILE)
{
	MeshRender()->GetDynamicMaterial();
	Ptr<CTexture> Arcana = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\DragonArcArcana.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, Arcana);
}

void CDragonArcArcanaScript::BeginOverlap(CCollider2D* _Other)
{
	Ptr<CTexture> Arcana = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\DragonArcEmpowered.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, Arcana);

	if (KEY_TAP(KEY::ENTER)) {
		CGameObject* Player = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"Player");
		CPlayerScript* PlayerMainScript = Player->GetScript<CPlayerScript>();

		if (PlayerMainScript->GetLBtnSkill() == PLAYER_SKILL::NONE) {
			PlayerMainScript->SetSkill(PLAYER_ATTACKBUTTON::LBTN, PLAYER_SKILL::DRAGONBREATH, 3.f);
		}
		else if (PlayerMainScript->GetRBtnSkill() == PLAYER_SKILL::NONE) {
			PlayerMainScript->SetSkill(PLAYER_ATTACKBUTTON::RBTN, PLAYER_SKILL::DRAGONBREATH, 3.f);
		}
		else if (PlayerMainScript->GetQSkill() == PLAYER_SKILL::NONE) {
			PlayerMainScript->SetSkill(PLAYER_ATTACKBUTTON::Q, PLAYER_SKILL::DRAGONBREATH, 3.f);
		}
		else if (PlayerMainScript->GetESkill() == PLAYER_SKILL::NONE) {
			PlayerMainScript->SetSkill(PLAYER_ATTACKBUTTON::E, PLAYER_SKILL::DRAGONBREATH, 3.f);
		}
		else if (PlayerMainScript->GetRSkill() == PLAYER_SKILL::NONE) {
			PlayerMainScript->SetSkill(PLAYER_ATTACKBUTTON::R, PLAYER_SKILL::DRAGONBREATH, 3.f);
		}
		else {
			//스킬이 현재 5개만 구현되어있어서 6번째 스킬 획득 시 나오는건 구현안해놨음
			assert(nullptr);
		}

		Ptr<CSound> equip = CResMgr::GetInst()->FindRes<CSound>(L"sound\\Equip.wav");
		equip->Play(1, 0.2, true);

		CGameObject* Merchant = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"Merchant");
		CMerchantScript* MerchantMainScript = Merchant->GetScript<CMerchantScript>();
		MerchantMainScript->Laugh();
		DestroyObject(GetOwner());
	}
}

void CDragonArcArcanaScript::OnOverlap(CCollider2D* _Other)
{
	Ptr<CTexture> Arcana = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\DragonArcEmpowered.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, Arcana);

	if (KEY_TAP(KEY::ENTER)) {
		CGameObject* Player = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"Player");
		CPlayerScript* PlayerMainScript = Player->GetScript<CPlayerScript>();

		if (PlayerMainScript->GetLBtnSkill() == PLAYER_SKILL::NONE) {
			PlayerMainScript->SetSkill(PLAYER_ATTACKBUTTON::LBTN, PLAYER_SKILL::DRAGONBREATH, 3.f);
		}
		else if (PlayerMainScript->GetRBtnSkill() == PLAYER_SKILL::NONE) {
			PlayerMainScript->SetSkill(PLAYER_ATTACKBUTTON::RBTN, PLAYER_SKILL::DRAGONBREATH, 3.f);
		}
		else if (PlayerMainScript->GetQSkill() == PLAYER_SKILL::NONE) {
			PlayerMainScript->SetSkill(PLAYER_ATTACKBUTTON::Q, PLAYER_SKILL::DRAGONBREATH, 3.f);
		}
		else if (PlayerMainScript->GetESkill() == PLAYER_SKILL::NONE) {
			PlayerMainScript->SetSkill(PLAYER_ATTACKBUTTON::E, PLAYER_SKILL::DRAGONBREATH, 3.f);
		}
		else if (PlayerMainScript->GetRSkill() == PLAYER_SKILL::NONE) {
			PlayerMainScript->SetSkill(PLAYER_ATTACKBUTTON::R, PLAYER_SKILL::DRAGONBREATH, 3.f);
		}
		else {
			//스킬이 현재 5개만 구현되어있어서 6번째 스킬 획득 시 나오는건 구현안해놨음
			assert(nullptr);
		}

		Ptr<CSound> equip = CResMgr::GetInst()->FindRes<CSound>(L"sound\\Equip.wav");
		equip->Play(1, 0.2, true);

		CGameObject* Merchant = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"Merchant");
		CMerchantScript* MerchantMainScript = Merchant->GetScript<CMerchantScript>();
		MerchantMainScript->Laugh();

		DestroyObject(GetOwner());
	}
}

void CDragonArcArcanaScript::EndOverlap(CCollider2D* _Other)
{
	MeshRender()->GetDynamicMaterial();
	Ptr<CTexture> Arcana = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\DragonArcArcana.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, Arcana);
}

