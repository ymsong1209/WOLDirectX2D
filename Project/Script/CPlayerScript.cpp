#include "pch.h"
#include "CPlayerScript.h"

#include <Engine/CTimeMgr.h>
#include <Engine/CLevelMgr.h>

#include <Engine/CMeshRender.h>
#include <Engine/CParticleSystem.h>
#include <Engine/CMaterial.h>

#include <Engine/ProceduralGenerationAlgorithms.h>
#include "CMissileScript.h"
#include "CMousePointerScript.h"

#include "CPlayerInfo.h"
#include <Engine/CLevelMgr.h>

#include "CPlayerSkillSlotScript.h"

CPlayerScript::CPlayerScript()
	: CScript((UINT)SCRIPT_TYPE::PLAYERSCRIPT)
	, m_iPlayerDir()
	, m_fSpeed(300.f)
	, m_vCapeColor(1.0f,0.0f,1.0f,1.0f)
	, m_ELBtnSkill(PLAYER_SKILL::NONE)
	, m_ERBtnSkill(PLAYER_SKILL::NONE)
	, m_EQSkill(PLAYER_SKILL::NONE)
	, m_EESkill(PLAYER_SKILL::NONE)
	, m_ERSkill(PLAYER_SKILL::NONE)
	, m_EAttackBtn(PLAYER_ATTACKBUTTON::NONE)
	, m_fLBtnCoolTime(0.f)
	, m_fRBtnCoolTime(0.f)
	, m_fECoolTime(0.f)
	, m_fQCoolTime(0.f)
	, m_fRCoolTime(0.f)
	, m_fLBtnCurCoolTime(0.f)
	, m_fRBtnCurCoolTime(0.f)
	, m_fECurCoolTime(0.f)
	, m_fQCurCoolTime(0.f)
	, m_fRCurCoolTime(0.f)
	, m_pTileMap(nullptr)
{
	m_iPlayerDir |= DIR_DOWN;
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fSpeed, "Speed");
	AddScriptParam(SCRIPT_PARAM::INT, &m_iPlayerDir, "PlayerDir");
	AddScriptParam(SCRIPT_PARAM::VEC4, &m_vCapeColor, "CapeColor");
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fAngle, "Angle");
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_Stat.CurHP, "CurHp");
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_Stat.CurMP, "CurMp");
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_Stat.MaxHP, "MaxHp");
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_Stat.MaxMP, "MaxMp");
	m_Stat = CPlayerInfo::GetInst()->GetStat();

	m_ELBtnSkill = CPlayerInfo::GetInst()->GetLBtnSkill();
	m_ERBtnSkill = CPlayerInfo::GetInst()->GetRBtnSkill();
	m_EQSkill = CPlayerInfo::GetInst()->GetQSkill();
	m_EESkill = CPlayerInfo::GetInst()->GetESkill();
	m_ERSkill = CPlayerInfo::GetInst()->GetRSkill();
	
	m_fLBtnCoolTime = CPlayerInfo::GetInst()->GetLBtnCoolTime();
	m_fRBtnCoolTime = CPlayerInfo::GetInst()->GetRBtnCoolTime();
	m_fECoolTime = CPlayerInfo::GetInst()->GetECoolTime();
	m_fQCoolTime = CPlayerInfo::GetInst()->GetQCoolTime();
	m_fRCoolTime = CPlayerInfo::GetInst()->GetRCoolTime();

	m_vCapeColor = CPlayerInfo::GetInst()->GetCapeColor();

}

CPlayerScript::CPlayerScript(const CPlayerScript& _other)
	: CScript((UINT)SCRIPT_TYPE::PLAYERSCRIPT)
	, m_iPlayerDir(_other.m_iPlayerDir)
	, m_fSpeed(_other.m_fSpeed)
	, m_vCapeColor(_other.m_vCapeColor)
	, m_ELBtnSkill(_other.m_ELBtnSkill)
	, m_ERBtnSkill(_other.m_ERBtnSkill)
	, m_EQSkill(_other.m_EQSkill)
	, m_EESkill(_other.m_EESkill)
	, m_ERSkill(_other.m_ERSkill)
	, m_EAttackBtn(PLAYER_ATTACKBUTTON::NONE)
	, m_fLBtnCoolTime(_other.m_fLBtnCoolTime)
	, m_fRBtnCoolTime(_other.m_fRBtnCoolTime)
	, m_fECoolTime(_other.m_fECoolTime)
	, m_fQCoolTime(_other.m_fQCoolTime)
	, m_fRCoolTime(_other.m_fRCoolTime)
	, m_fLBtnCurCoolTime(_other.m_fLBtnCurCoolTime)
	, m_fRBtnCurCoolTime(_other.m_fRBtnCurCoolTime)
	, m_fECurCoolTime(_other.m_fECurCoolTime)
	, m_fQCurCoolTime(_other.m_fQCurCoolTime)
	, m_fRCurCoolTime(_other.m_fRCurCoolTime)
	, m_Stat(_other.m_Stat)
	, m_pTileMap(_other.m_pTileMap)
{
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fSpeed, "Speed");
	AddScriptParam(SCRIPT_PARAM::INT, &m_iPlayerDir, "PlayerDir");
	AddScriptParam(SCRIPT_PARAM::VEC4, &m_vCapeColor, "CapeColor");
}

CPlayerScript::~CPlayerScript()
{
	
}

void CPlayerScript::begin()
{
	MeshRender()->GetDynamicMaterial();
	UINT i = (UINT)SCRIPT_TYPE::PLAYERIDLESCRIPT;
	ChangeState((UINT)SCRIPT_TYPE::PLAYERIDLESCRIPT);

	
	//AStar용도, Normal Stage에서만 사용됨
	m_pTileMap = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"TileMap");


}

void CPlayerScript::tick()
{
	m_Stat.CurMP += DT * 20;
	if (m_Stat.CurMP > m_Stat.MaxMP) {
		m_Stat.CurMP = m_Stat.MaxMP; 
		m_bUltReady = true;
	}
	else {
		m_bUltReady = false;
	}

	if (m_Stat.CurHP < 1) {
		ChangeState((UINT)SCRIPT_TYPE::PLAYERDEADSCRIPT, false);
	}

	if (KEY_TAP(KEY::M)) {
		m_Stat.CurHP = 20.f;
	}

	if (KEY_TAP(KEY::N)) {
		m_Stat.CurHP = 100.f;
	}

	GetAngle();
	MeshRender()->GetMaterial()->SetScalarParam(VEC4_1, &m_vCapeColor);

	m_fLBtnCurCoolTime -= DT;
	m_fRBtnCurCoolTime -= DT;
	m_fECurCoolTime -= DT;
	m_fQCurCoolTime -= DT;
	m_fRCurCoolTime -= DT;
	if (m_fLBtnCurCoolTime <= 0.f) m_fLBtnCurCoolTime = 0.f;
	if (m_fRBtnCurCoolTime <= 0.f) m_fRBtnCurCoolTime = 0.f;
	if (m_fECurCoolTime <= 0.f) m_fECurCoolTime = 0.f;
	if (m_fQCurCoolTime <= 0.f) m_fQCurCoolTime = 0.f;
	if (m_fRCurCoolTime <= 0.f) m_fRCurCoolTime = 0.f;

	NormalAttackCoolTimeCheck();

	
	if (KEY_TAP(KEY::TAB)) {
		CGameObject* SkillSlot = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"SkillSlot");
		CPlayerSkillSlotScript* SkillSlotScript = SkillSlot->GetScript<CPlayerSkillSlotScript>();
		if (SkillSlotScript->GetUIActive() == true) {
			SkillSlotScript->Deactivate();
		}
		else {
			SkillSlotScript->Activate();
		}
	}
	
}



void CPlayerScript::SaveToLevelFile(FILE* _File)
{
}

void CPlayerScript::LoadFromLevelFile(FILE* _File)
{
	//Animator에 로딩 한번만 하면 Animator의 LoadFromLevelFile에서 현재 Animation을 다 기억하고 한번에 로딩시킴

	Animator2D()->LoadAnim(L"animation\\player\\Player_Backhand_Down.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_Backhand_Left.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_Backhand_Right.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_Backhand_Up.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_Dash_Down.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_Dash_Left.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_Dash_Right.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_Dash_Stop_Left.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_Dash_Stop_Right.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_Dash_Up.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_Dead.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_Fall_Down.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_Fall_Left.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_Fall_Right.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_Fall_Up.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_Forehand_Down.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_Forehand_Left.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_Forehand_Right.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_Forehand_Up.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_Forehand_Down_Ready.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_Forehand_Left_Ready.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_Forehand_Right_Ready.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_Forehand_Up_Ready.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_GroundSlam_Down.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_GroundSlam_Up.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_Hit_Down.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_Hit_Left.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_Hit_Right.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_Hit_Up.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_Idle_Down.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_Idle_Left.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_Idle_Right.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_Idle_Up.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_PBAoE_Down.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_PBAoE_Left.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_PBAoE_Right.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_PBAoE_Up.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_Slide_Down.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_Slide_Left.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_Slide_Right.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_Slide_Up.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_Walk_Down.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_Walk_Left.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_Walk_Right.anim");
	Animator2D()->LoadAnim(L"animation\\player\\Player_Walk_Up.anim");
	Animator2D()->SetCurAnim(Animator2D()->FindAnim(L"Player_Idle_Down"));
}

void CPlayerScript::BeginOverlap(CCollider2D* _Other)
{
	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();


	if (Curlevel->GetLayer(_Other->GetOwner()->GetLayerIndex())->GetName() == L"PitWall" ||
		Curlevel->GetLayer(_Other->GetOwner()->GetLayerIndex())->GetName() == L"Wall") {
		// Calculate the direction from the wall to the player
		Matrix MatColliderPos = Collider2D()->GetColliderPosMat();
		Vec3 ColliderPos = Transform()->GetRelativePos() + Collider2D()->GetOffsetPos();
		Matrix MatWallColliderPos = _Other->GetColliderPosMat();
		Vec3 WallColliderPos = _Other->Transform()->GetRelativePos() + _Other->GetOffsetPos();

		Vec3 direction = WallColliderPos - ColliderPos;
		direction.Normalize();
		// Calculate the magnitude of the force based on the collider sizes and player speed
		Matrix MatColliderScale = Collider2D()->GetColliderScaleMat();
		Vec3 ColliderScale = Vec3(MatColliderScale._11, MatColliderScale._22, MatColliderScale._33);
		Matrix MatWallColliderScale = _Other->GetColliderScaleMat();
		Vec3 WallColliderScale = Vec3(MatWallColliderScale._11, MatWallColliderScale._22, MatWallColliderScale._33);

		float x;
		float y;
		float xratio = 0.f;
		float yratio = 0.f;
		
		// wall이 오른쪽에 있는 경우
		if (ColliderPos.x < WallColliderPos.x) {
			x = WallColliderPos.x - WallColliderScale.x / 2.0f - ColliderScale.x;
			xratio = (WallColliderPos.x - ColliderPos.x) / (WallColliderScale.x / 2.0f + ColliderScale.x / 2.0f);
		}
		//wall이 왼쪽에 있는 경우
		else {
			x = WallColliderPos.x + WallColliderScale.x / 2.0f + ColliderScale.x;
			xratio = (ColliderPos.x - WallColliderPos.x) / (WallColliderScale.x / 2.0f + ColliderScale.x / 2.0f);
		}

		//wall이 위쪽에 있는 경우
		if (ColliderPos.y < WallColliderPos.y) {
			y = WallColliderPos.y - WallColliderScale.y / 2.0f - ColliderScale.y;
			yratio = (WallColliderPos.y - ColliderPos.y) / (WallColliderScale.y / 2.0f + ColliderScale.y / 2.0f);
		}
		//wall이 아래쪽에 있는 경우
		else {
			y = WallColliderPos.y + WallColliderScale.y / 2.0f + ColliderScale.y;
			yratio = (ColliderPos.y - WallColliderPos.y) / (WallColliderScale.y / 2.0f + ColliderScale.y / 2.0f);
		}
		//x가 더 크다 -> 왼쪽이나 오른쪽으로 밀면됨
		if (xratio > yratio) {
			Transform()->SetRelativePos(Vec3(x - Collider2D()->GetOffsetPos().x,
											Transform()->GetRelativePos().y,
											Transform()->GetRelativePos().z));
		}
		else {
			Transform()->SetRelativePos(Vec3(Transform()->GetRelativePos().x,
											y - Collider2D()->GetOffsetPos().y,
											Transform()->GetRelativePos().z));
		}
		
		
		
	}
}

void CPlayerScript::OnOverlap(CCollider2D* _Other)
{
	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();


	if (Curlevel->GetLayer(_Other->GetOwner()->GetLayerIndex())->GetName() == L"Wall" ||
		Curlevel->GetLayer(_Other->GetOwner()->GetLayerIndex())->GetName() == L"PitWall") {
		// Calculate the direction from the wall to the player
		Matrix MatColliderPos = Collider2D()->GetColliderPosMat();
		Vec3 ColliderPos = Transform()->GetRelativePos() + Collider2D()->GetOffsetPos();
		Matrix MatWallColliderPos = _Other->GetColliderPosMat();
		Vec3 WallColliderPos = _Other->Transform()->GetRelativePos() + _Other->GetOffsetPos();

		Vec3 direction = WallColliderPos - ColliderPos;
		direction.Normalize();
		// Calculate the magnitude of the force based on the collider sizes and player speed
		Matrix MatColliderScale = Collider2D()->GetColliderScaleMat();
		Vec3 ColliderScale = Vec3(MatColliderScale._11, MatColliderScale._22, MatColliderScale._33);
		Matrix MatWallColliderScale = _Other->GetColliderScaleMat();
		Vec3 WallColliderScale = Vec3(MatWallColliderScale._11, MatWallColliderScale._22, MatWallColliderScale._33);

		float x;
		float y;
		float xratio = 0.f;
		float yratio = 0.f;

		// wall이 오른쪽에 있는 경우
		if (ColliderPos.x < WallColliderPos.x) {
			x = WallColliderPos.x - WallColliderScale.x / 2.0f - ColliderScale.x;
			xratio = (WallColliderPos.x - ColliderPos.x) / (WallColliderScale.x / 2.0f + ColliderScale.x / 2.0f);
		}
		//wall이 왼쪽에 있는 경우
		else {
			x = WallColliderPos.x + WallColliderScale.x / 2.0f + ColliderScale.x;
			xratio = (ColliderPos.x - WallColliderPos.x) / (WallColliderScale.x / 2.0f + ColliderScale.x / 2.0f);
		}

		//wall이 위쪽에 있는 경우
		if (ColliderPos.y < WallColliderPos.y) {
			y = WallColliderPos.y - WallColliderScale.y / 2.0f - ColliderScale.y;
			yratio = (WallColliderPos.y - ColliderPos.y) / (WallColliderScale.y / 2.0f + ColliderScale.y / 2.0f);
		}
		//wall이 아래쪽에 있는 경우
		else {
			y = WallColliderPos.y + WallColliderScale.y / 2.0f + ColliderScale.y;
			yratio = (ColliderPos.y - WallColliderPos.y) / (WallColliderScale.y / 2.0f + ColliderScale.y / 2.0f);
		}
		//x가 더 크다 -> 왼쪽이나 오른쪽으로 밀면됨
		if (xratio > yratio) {
			Transform()->SetRelativePos(Vec3(x - Collider2D()->GetOffsetPos().x,
				Transform()->GetRelativePos().y,
				Transform()->GetRelativePos().z));
		}
		else {
			Transform()->SetRelativePos(Vec3(Transform()->GetRelativePos().x,
				y - Collider2D()->GetOffsetPos().y,
				Transform()->GetRelativePos().z));
		}



	}
	
}

void CPlayerScript::EndOverlap(CCollider2D* _Other)
{
	
}

const PLAYER_SKILL& CPlayerScript::GetSkillPerAttackBtn()
{
	if (m_EAttackBtn == PLAYER_ATTACKBUTTON::NONE) {
		assert(nullptr);
	}
	if (m_EAttackBtn == PLAYER_ATTACKBUTTON::LBTN){
		return m_ELBtnSkill;
	}
	else if(m_EAttackBtn == PLAYER_ATTACKBUTTON::RBTN) {
		return m_ERBtnSkill;
	}
	else if (m_EAttackBtn == PLAYER_ATTACKBUTTON::E) {
		return m_EESkill;
	}
	else if (m_EAttackBtn == PLAYER_ATTACKBUTTON::Q) {
		return m_EQSkill;
	}
	else if (m_EAttackBtn == PLAYER_ATTACKBUTTON::R) {
		return m_ERSkill;
	}

}

//성공1 실패 2
int CPlayerScript::ChangePlayerSkill(PLAYER_ATTACKBUTTON _Originbtn, PLAYER_SKILL _OriginSkill, float _OriginCoolTime, PLAYER_ATTACKBUTTON _Destbtn, PLAYER_SKILL _DestSkill, float _DestCoolTime)
{
	if (CheckOtherSkillSlot() == 2) return 2;
	PLAYER_ATTACKBUTTON tmpBtn = _Originbtn;
	PLAYER_SKILL tmpSkill = _OriginSkill;
	float tmpCoolTime = _OriginCoolTime;

	switch (_Originbtn)
	{
	case PLAYER_ATTACKBUTTON::LBTN: {
		m_ELBtnSkill = _DestSkill;
		m_fLBtnCoolTime = _DestCoolTime;
		m_fLBtnCurCoolTime = 0.f;
	}
		break;
	case PLAYER_ATTACKBUTTON::RBTN:
	{
		m_ERBtnSkill = _DestSkill;
		m_fRBtnCoolTime = _DestCoolTime;
		m_fRBtnCurCoolTime = 0.f;
	}
		break;
	case PLAYER_ATTACKBUTTON::Q:
	{
		m_EQSkill = _DestSkill;
		m_fQCoolTime = _DestCoolTime;
		m_fQCurCoolTime = 0.f;
	}
		break;
	case PLAYER_ATTACKBUTTON::E: {
		m_EESkill = _DestSkill;
		m_fECoolTime = _DestCoolTime;
		m_fECurCoolTime = 0.f;
	}
		break;
	case PLAYER_ATTACKBUTTON::R: {
		m_ERSkill = _DestSkill;
		m_fRCoolTime = _DestCoolTime;
		m_fRCurCoolTime = 0.f;
	}
		break;
	case PLAYER_ATTACKBUTTON::NONE: {
		assert(nullptr);
	}
		break;
	case PLAYER_ATTACKBUTTON::END:
		break;
	default:
		break;
	}

	switch (_Destbtn)
	{
	case PLAYER_ATTACKBUTTON::LBTN: {
		m_ELBtnSkill = tmpSkill;
		m_fLBtnCoolTime = tmpCoolTime;
		m_fLBtnCurCoolTime = 0.f;
	}
	 break;
	case PLAYER_ATTACKBUTTON::RBTN:
	{
		m_ERBtnSkill = tmpSkill;
		m_fRBtnCoolTime = tmpCoolTime;
		m_fRBtnCurCoolTime = 0.f;
	}
	break;
	case PLAYER_ATTACKBUTTON::Q:
	{
		m_EQSkill = tmpSkill;
		m_fQCoolTime = tmpCoolTime;
		m_fQCurCoolTime = 0.f;
	}
	break;
	case PLAYER_ATTACKBUTTON::E: {
		m_EESkill = tmpSkill;
		m_fECoolTime = tmpCoolTime;
		m_fECurCoolTime = 0.f;
	}
	break;
	case PLAYER_ATTACKBUTTON::R: {
		m_ERSkill = tmpSkill;
		m_fRCoolTime = tmpCoolTime;
		m_fRCurCoolTime = 0.f;
	}
	break;
	case PLAYER_ATTACKBUTTON::NONE: {
		assert(nullptr);
	}
	break;
	case PLAYER_ATTACKBUTTON::END:
		break;
	default:
		break;
	}

	return 1;
}



//성공1 실패 2
int CPlayerScript::CheckOtherSkillSlot()
{
	if (m_fLBtnCurCoolTime == 0.f && m_fRBtnCurCoolTime == 0.f && m_fQCurCoolTime == 0.f && m_fECurCoolTime == 0.f && m_fRCurCoolTime == 0.f) {
		return 1;
	}
	else {
		return 2;
	}
}

void CPlayerScript::SetSkill(PLAYER_ATTACKBUTTON _btn, PLAYER_SKILL _skill, float _CoolTime)
{
	switch (_btn)
	{
	case PLAYER_ATTACKBUTTON::LBTN: {
		m_ELBtnSkill = _skill;
		m_fLBtnCoolTime = _CoolTime;
		m_fLBtnCurCoolTime = 0.f;
	}
		break;
	case PLAYER_ATTACKBUTTON::RBTN: {
		m_ERBtnSkill = _skill;
		m_fRBtnCoolTime = _CoolTime;
		m_fRBtnCurCoolTime = 0.f;
	}
		break;
	case PLAYER_ATTACKBUTTON::Q: {
		m_EQSkill = _skill;
		m_fQCoolTime = _CoolTime;
		m_fQCurCoolTime = 0.f;
	}
		break;
	case PLAYER_ATTACKBUTTON::E: {
		m_EESkill = _skill;
		m_fECoolTime = _CoolTime;
		m_fECurCoolTime = 0.f;
	}
		break;
	case PLAYER_ATTACKBUTTON::R: {
		m_ERSkill = _skill;
		m_fRCoolTime = _CoolTime;
		m_fRCurCoolTime = 0.f;
	}
		break;
	case PLAYER_ATTACKBUTTON::NONE: {
		assert(nullptr);
	}
		break;
	case PLAYER_ATTACKBUTTON::END:
		break;
	default:
		break;
	}
}

void CPlayerScript::SetPlayerInfo()
{
	CPlayerInfo::GetInst()->SetStat(m_Stat);

	CPlayerInfo::GetInst()->SetLBtnSkill(m_ELBtnSkill);
	CPlayerInfo::GetInst()->SetRBtnSkill(m_ERBtnSkill);
	CPlayerInfo::GetInst()->SetQSkill(m_EQSkill);
	CPlayerInfo::GetInst()->SetESkill(m_EESkill);
	CPlayerInfo::GetInst()->SetRSkill(m_ERSkill);

	CPlayerInfo::GetInst()->SetLBtnCoolTime(m_fLBtnCoolTime);
	CPlayerInfo::GetInst()->SetRBtnCoolTime(m_fRBtnCoolTime);
	CPlayerInfo::GetInst()->SetQCoolTime(m_fQCoolTime);
	CPlayerInfo::GetInst()->SetECoolTime(m_fECoolTime);
	CPlayerInfo::GetInst()->SetRCoolTime(m_fRCoolTime);

	CPlayerInfo::GetInst()->SetCapeColor(m_vCapeColor);
}

const PLAYER_SKILL& CPlayerScript::GetSkillPerBtn(int BtnNum)
{
	if (BtnNum == 0) {
		return m_ELBtnSkill;
	}
	else if (BtnNum == 1) {
		return m_ERBtnSkill;
	}
	else if (BtnNum == 2) {
		return m_EQSkill;
	}
	else if (BtnNum == 3) {
		return m_EESkill;
	}
	else if (BtnNum == 4) {
		return m_ERSkill;
	}
	else {
		assert(nullptr);
	}
}

const float& CPlayerScript::GetCoolTimePerSkill(int BtnNum)
{
	if (BtnNum == 0) {
		return m_fLBtnCoolTime;
	}
	else if (BtnNum == 1) {
		return m_fRBtnCoolTime;
	}
	else if (BtnNum == 2) {
		return m_fQCoolTime;
	}
	else if (BtnNum == 3) {
		return m_fECoolTime;
	}
	else if (BtnNum == 4) {
		return m_fRCoolTime;
	}
	else {
		assert(nullptr);
	}
}

const float& CPlayerScript::GetCurCoolTimePerBtn(PLAYER_ATTACKBUTTON _btn)
{
	switch (_btn)
	{
	case PLAYER_ATTACKBUTTON::LBTN:
		return m_fLBtnCurCoolTime;
		break;
	case PLAYER_ATTACKBUTTON::RBTN:
		return m_fRBtnCurCoolTime;
		break;
	case PLAYER_ATTACKBUTTON::Q:
		return m_fQCurCoolTime;
		break;
	case PLAYER_ATTACKBUTTON::E:
		return m_fECurCoolTime;
		break;
	case PLAYER_ATTACKBUTTON::R:
		return m_fRCurCoolTime;
		break;
	case PLAYER_ATTACKBUTTON::NONE:
		assert(nullptr);
		break;
	default:
		break;
	}
}

void CPlayerScript::SetCoolTimePerBtn(PLAYER_ATTACKBUTTON _btn, float _CoolTime)
{
	switch (_btn)
	{
	case PLAYER_ATTACKBUTTON::LBTN:
		m_fLBtnCoolTime = _CoolTime;
		break;
	case PLAYER_ATTACKBUTTON::RBTN:
		m_fRBtnCoolTime = _CoolTime;
		break;
	case PLAYER_ATTACKBUTTON::Q:
		m_fQCoolTime = _CoolTime;
		break;
	case PLAYER_ATTACKBUTTON::E:
		m_fECoolTime = _CoolTime;
		break;
	case PLAYER_ATTACKBUTTON::R:
		m_fRCoolTime = _CoolTime;
		break;
	case PLAYER_ATTACKBUTTON::NONE:
		assert(nullptr);
		break;
	default:
		break;
	}
}

void CPlayerScript::SetCurCoolTimetoMax(PLAYER_ATTACKBUTTON _btn)
{
	switch (_btn)
	{
	case PLAYER_ATTACKBUTTON::LBTN:
		m_fLBtnCurCoolTime = m_fLBtnCoolTime;
		break;
	case PLAYER_ATTACKBUTTON::RBTN:
		m_fRBtnCurCoolTime = m_fRBtnCoolTime;
		break;
	case PLAYER_ATTACKBUTTON::Q:
		m_fQCurCoolTime = m_fQCoolTime;
		break;
	case PLAYER_ATTACKBUTTON::E:
		m_fECurCoolTime = m_fECoolTime;
		break;
	case PLAYER_ATTACKBUTTON::R:
		m_fRCurCoolTime = m_fRCoolTime;
		break;
	case PLAYER_ATTACKBUTTON::NONE:
		assert(nullptr);
		break;
	default:
		break;
	}
}

bool CPlayerScript::IsPlayerOnGround()
{
	Vec3 Pos = Transform()->GetRelativePos();
	Vec3 Scale = Transform()->GetRelativeScale();
	// 플레이어의 실제 위치는 발바닥
	Pos = Vec3(Pos.x, Pos.y - 50.f, Pos.z);
	vector<tTile> tiles = m_pTileMap->TileMap()->GetTile();
	Vec2 TileSize = Vec2(m_pTileMap->Transform()->GetRelativeScale().x / m_pTileMap->TileMap()->GetTileCountX(),
						m_pTileMap->Transform()->GetRelativeScale().y / m_pTileMap->TileMap()->GetTileCountY());
	Vec2 DestTilePos = Vec2(Pos.x + m_pTileMap->Transform()->GetRelativeScale().x / 2,
							Pos.y + m_pTileMap->Transform()->GetRelativeScale().y / 2);

	int iDestPosX = (int)DestTilePos.x / TileSize.x;
	int iDestPosY = 80 - (int)DestTilePos.y / TileSize.y;

	int tmp = iDestPosY * m_pTileMap->TileMap()->GetTileCountX() + iDestPosX;
	if (tiles[iDestPosY * m_pTileMap->TileMap()->GetTileCountX() + iDestPosX].Type == 1) return true;
	else return false;
}

void CPlayerScript::NormalAttackCoolTimeCheck()
{
	if (m_ELBtnSkill == PLAYER_SKILL::NORMALATTACK)
	{
		if (m_fLBtnCoolTime > 0.f && m_fLBtnCurCoolTime <= 0.f)
			m_fLBtnCoolTime = 0.f;
	}
	if (m_ERBtnSkill == PLAYER_SKILL::NORMALATTACK)
	{
		if (m_fRBtnCoolTime > 0.f && m_fRBtnCurCoolTime <= 0.f)
			m_fRBtnCoolTime = 0.f;
	}
	if (m_EQSkill == PLAYER_SKILL::NORMALATTACK)
	{
		if (m_fQCoolTime > 0.f && m_fQCurCoolTime <= 0.f)
			m_fQCoolTime = 0.f;
	}
	if (m_EESkill == PLAYER_SKILL::NORMALATTACK)
	{
		if (m_fECoolTime > 0.f && m_fECurCoolTime <= 0.f)
			m_fECoolTime = 0.f;
	}
	if (m_ERSkill == PLAYER_SKILL::NORMALATTACK)
	{
		if (m_fRCoolTime > 0.f && m_fRCurCoolTime <= 0.f)
			m_fRCoolTime = 0.f;
	}
}

void CPlayerScript::Shoot()
{
	/*
	// 미사일 오브젝트 생성
	CGameObject* pMissile = new CGameObject;

	pMissile->AddComponent(new CTransform);
	pMissile->AddComponent(new CMeshRender);
	pMissile->AddComponent(new CMissileScript);

	pMissile->Transform()->SetRelativePos(Transform()->GetRelativePos() + Vec3(0.f, 0.5f, 0.f) * Transform()->GetRelativeScale());
	pMissile->Transform()->SetRelativeScale(Vec3(50.f, 50.f, 50.f));

	pMissile->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pMissile->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std2DMtrl"));

	CMissileScript* pMissileScript = pMissile->GetScript<CMissileScript>();
	if (nullptr != pMissileScript)
		pMissileScript->SetSpeed(500.f);

	// 레벨에 추가
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	pCurLevel->AddGameObject(pMissile, L"PlayerProjectile", false);
	*/

	// 미사일 프리팹 참조
	Ptr<CPrefab> pMissilePrefab = CResMgr::GetInst()->FindRes<CPrefab>(L"prefab\\Missile.prefab");
	Vec3 vMissilePos = Transform()->GetRelativePos() + Vec3(0.f, 0.5f, 0.f) * Transform()->GetRelativeScale();
	CGameObject* pCloneMissile = pMissilePrefab->Instantiate();

	// 레벨에 추가
	SpawnGameObject(pCloneMissile, vMissilePos, L"PlayerProjectile");
}



void CPlayerScript::GetAngle()
{
	//GetMousePointer------------//
	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
	CGameObject* mouse = Curlevel->FindParentObjectByName(L"MousePointer");
	CPlayerScript* PlayerMainScript = GetOwner()->GetScript<CPlayerScript>();
	CMousePointerScript* MouseScript = mouse->GetScript<CMousePointerScript>();
	Vec4 Mousepos = MouseScript->GetMousePos();
	Vec3 OwnerPos = GetOwner()->Transform()->GetRelativePos();
	// calculate the slope of the line from A to B
	double slope = (Mousepos.y - OwnerPos.y) / (Mousepos.x - OwnerPos.x);
	// calculate the angle between the x-axis and the line in radians
	double angle = atan(slope);
	// convert radians to degrees
	angle = angle * 180.0 / XM_PI;
	//// if the slope is negative, add 180 degrees to get the acute angle
	if (slope < 0) {
		angle += 180.0;
	}
	// if the slope is positive and y2 < y1, add 360 degrees
	if (Mousepos.y < OwnerPos.y) {
		angle += 180.0;
	}
	m_fAngle = angle;
}


