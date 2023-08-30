#include "pch.h"
#include "CWaterBallArcanaScript.h"
#include "CPlayerScript.h"
#include "CMerchantScript.h"

CWaterBallArcanaScript::CWaterBallArcanaScript()
	:CScript((UINT)SCRIPT_TYPE::WATERBALLARCANASCRIPT)
{
}

CWaterBallArcanaScript::~CWaterBallArcanaScript()
{
}


void CWaterBallArcanaScript::begin()
{
	MeshRender()->GetDynamicMaterial();
	Ptr<CTexture> Arcana = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\WaterBallArcana.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, Arcana);
}

void CWaterBallArcanaScript::tick()
{
}

void CWaterBallArcanaScript::SaveToLevelFile(FILE* _File)
{
}

void CWaterBallArcanaScript::LoadFromLevelFile(FILE* _FILE)
{
	MeshRender()->GetDynamicMaterial();
	Ptr<CTexture> Arcana = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\WaterBallArcana.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, Arcana);
}

void CWaterBallArcanaScript::BeginOverlap(CCollider2D* _Other)
{
	Ptr<CTexture> Arcana = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\WaterBallEmpowered.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, Arcana);

	if (KEY_TAP(KEY::ENTER)) {
		CGameObject* Player = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"Player");
		CPlayerScript* PlayerMainScript = Player->GetScript<CPlayerScript>();

		if (PlayerMainScript->GetLBtnSkill() == PLAYER_SKILL::NONE) {
			PlayerMainScript->SetSkill(PLAYER_ATTACKBUTTON::LBTN, PLAYER_SKILL::WATERBALL, 2.f);
		}
		else if (PlayerMainScript->GetRBtnSkill() == PLAYER_SKILL::NONE) {
			PlayerMainScript->SetSkill(PLAYER_ATTACKBUTTON::RBTN, PLAYER_SKILL::WATERBALL, 2.f);
		}
		else if (PlayerMainScript->GetQSkill() == PLAYER_SKILL::NONE) {
			PlayerMainScript->SetSkill(PLAYER_ATTACKBUTTON::Q, PLAYER_SKILL::WATERBALL, 2.f);
		}
		else if (PlayerMainScript->GetESkill() == PLAYER_SKILL::NONE) {
			PlayerMainScript->SetSkill(PLAYER_ATTACKBUTTON::E, PLAYER_SKILL::WATERBALL, 2.f);
		}
		else if (PlayerMainScript->GetRSkill() == PLAYER_SKILL::NONE) {
			PlayerMainScript->SetSkill(PLAYER_ATTACKBUTTON::R, PLAYER_SKILL::WATERBALL, 2.f);
		}
		else {
			//스킬이 현재 5개만 구현되어있어서 6번째 스킬 획득 시 나오는건 구현안해놨음
			assert(nullptr);
		}

		Ptr<CSound> equip = CResMgr::GetInst()->FindRes<CSound>(L"sound\\Equip.wav");
		equip->Play(1, 0.2, true);
		DestroyObject(GetOwner());
	}
}

void CWaterBallArcanaScript::OnOverlap(CCollider2D* _Other)
{

	Ptr<CTexture> Arcana = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\WaterBallEmpowered.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, Arcana);

	if (KEY_TAP(KEY::ENTER)) {
		CGameObject* Player = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"Player");
		CPlayerScript* PlayerMainScript = Player->GetScript<CPlayerScript>();
		
		if (PlayerMainScript->GetLBtnSkill() == PLAYER_SKILL::NONE) {
			PlayerMainScript->SetSkill(PLAYER_ATTACKBUTTON::LBTN, PLAYER_SKILL::WATERBALL, 2.f);
		}
		else if (PlayerMainScript->GetRBtnSkill() == PLAYER_SKILL::NONE) {
			PlayerMainScript->SetSkill(PLAYER_ATTACKBUTTON::RBTN, PLAYER_SKILL::WATERBALL, 2.f);
		}
		else if (PlayerMainScript->GetQSkill() == PLAYER_SKILL::NONE) {
			PlayerMainScript->SetSkill(PLAYER_ATTACKBUTTON::Q, PLAYER_SKILL::WATERBALL, 2.f);
		}
		else if (PlayerMainScript->GetESkill() == PLAYER_SKILL::NONE) {
			PlayerMainScript->SetSkill(PLAYER_ATTACKBUTTON::E, PLAYER_SKILL::WATERBALL, 2.f);
		}
		else if (PlayerMainScript->GetRSkill() == PLAYER_SKILL::NONE) {	
			PlayerMainScript->SetSkill(PLAYER_ATTACKBUTTON::R, PLAYER_SKILL::WATERBALL, 2.f);
		}
		else {
			//스킬이 현재 5개만 구현되어있어서 6번째 스킬 획득 시 나오는건 구현안해놨음
			assert(nullptr);
		}

		CGameObject* Merchant = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"Merchant");
		CMerchantScript* MerchantMainScript = Merchant->GetScript<CMerchantScript>();
		MerchantMainScript->Laugh();

		Ptr<CSound> equip = CResMgr::GetInst()->FindRes<CSound>(L"sound\\Equip.wav");
		equip->Play(1, 0.2, true);
		DestroyObject(GetOwner());
	}
}

void CWaterBallArcanaScript::EndOverlap(CCollider2D* _Other)
{
	Ptr<CTexture> Arcana = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\WaterBallArcana.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, Arcana);
}


