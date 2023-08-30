#include "pch.h"
#include "CPlayerAttackScript.h"
#include "CPlayerScript.h"
#include "CMousePointerScript.h"
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim2D.h>
#include "CBackHandAttackScript.h"
#include "CForeHandAttackScript.h"
#include "CSnowFlakeScript.h"
#include "CDragonBreathScript.h"
#include "CDragonParticleScript.h"
#include "CMeteorScript.h"
#include "CMeteorSpawnCircleScript.h"
#include "CWaterBombScript.h"
#include "CChaosBombScript.h"

CPlayerAttackScript::CPlayerAttackScript()
	: CScript((UINT)SCRIPT_TYPE::PLAYERATTACKSCRIPT)
	, m_ECurAttackBtn(PLAYER_ATTACKBUTTON::NONE)
	, m_ECurSkill(PLAYER_SKILL::NONE)
	, m_IAttackCount(0)
	, m_bReturnToAttack(false)
	, m_bIsAnimationFinished(false)
	, m_bIsSkillActivated(true)
	, m_bIsFinalAttack(false)
	, m_bIsCharging(false)
	, m_pWater(nullptr)
	, m_bIsUlt(false)
{
	AddScriptParam(SCRIPT_PARAM::INT, &m_IAttackCount, "AttackCount");
	SetActive(false);
}

CPlayerAttackScript::~CPlayerAttackScript()
{
}

void CPlayerAttackScript::begin()
{
	if (!IsActive()) return;
	
}

void CPlayerAttackScript::tick()
{
	if (!IsActive()) return;
	CPlayerScript* PlayerMainScript = GetOwner()->GetScript<CPlayerScript>();
	
	//AttackState일때 키를 누르면
	//다시 AttackScript로 돌아오는걸 예약
	if (KEY_TAP(KEY::LBTN)) {
		m_ECurAttackBtn = PLAYER_ATTACKBUTTON::LBTN;
		m_bReturnToAttack = true;
	}
	if (KEY_TAP(KEY::RBTN)) {
		m_ECurAttackBtn = PLAYER_ATTACKBUTTON::RBTN;
		m_bReturnToAttack = true;
	}
	if (KEY_TAP(KEY::R)) {
		m_ECurAttackBtn = PLAYER_ATTACKBUTTON::R;
		m_bReturnToAttack = true;
	}
	if (KEY_TAP(KEY::Q)) {
		m_ECurAttackBtn = PLAYER_ATTACKBUTTON::Q;
		m_bReturnToAttack = true;
	}
	if (KEY_TAP(KEY::E)) {
		m_ECurAttackBtn = PLAYER_ATTACKBUTTON::E;
		m_bReturnToAttack = true;
	}

	if (m_bIsCharging) {
		AttackCharging();
	}

	//공격 모션 끝나면 상태 전환
	if (Animator2D()->GetCurAnim()->IsFinish() && !m_bIsCharging) {
		Animator2D()->GetCurAnim()->Reset();
		//다시 공격으로 돌아가는게 예약되어있음
		if (m_bReturnToAttack) {
			m_bIsAnimationFinished = true;
			ChangeToAttack();
		}
		else {
			ChangeState((UINT)SCRIPT_TYPE::PLAYERIDLESCRIPT);
		}
	}
	
}

void CPlayerAttackScript::Enter()
{
	CPlayerScript* PlayerMainScript = GetOwner()->GetScript<CPlayerScript>();
	//현재 누른 버튼이 스킬이 세팅이 안되어있는 경우
	if (PlayerMainScript->GetSkillPerAttackBtn() == PLAYER_SKILL::NONE) {
		m_ECurAttackBtn = PLAYER_ATTACKBUTTON::NONE;
		m_ECurSkill = PLAYER_SKILL::NONE;
		m_IAttackCount = 0;
		m_bIsFinalAttack = false;
		ChangeState((UINT)SCRIPT_TYPE::PLAYERIDLESCRIPT);
		return;
	}

	//이번에 새로 공격을 시작하는 경우
	if (m_ECurAttackBtn == PLAYER_ATTACKBUTTON::NONE && m_ECurSkill == PLAYER_SKILL::NONE) {
		m_ECurAttackBtn = PlayerMainScript->GetAttackBtn();
		m_ECurSkill = PlayerMainScript->GetSkillPerAttackBtn();
		m_bIsFinalAttack = false;
		++m_IAttackCount;
	}
	//두번째로 들어오는 경우
	else {
		//공격키를 누르다가 다른 키를 누를경우 그냥 다시 Idle로 전환
		if ((m_ECurAttackBtn != PlayerMainScript->GetAttackBtn()) &&
			(m_ECurSkill != PlayerMainScript->GetSkillPerAttackBtn())) {
			m_ECurAttackBtn = PLAYER_ATTACKBUTTON::NONE;
			m_ECurSkill = PLAYER_SKILL::NONE;
			m_IAttackCount = 0;
			ChangeState((UINT)SCRIPT_TYPE::PLAYERIDLESCRIPT);
			return;
		}
		//공격키를 두번째로 눌렀고, 동일한 키를 입력했을 경우
		else {
			++m_IAttackCount;
		}
		
	}
	

	switch (m_ECurSkill)
	{
	case PLAYER_SKILL::NORMALATTACK: {
		NormalAttack();
	}
		break;
	case PLAYER_SKILL::SNOWFLAKE: {
		SnowFlakeAttack();
	}
		break;
	case PLAYER_SKILL::DRAGONBREATH: {
		DragonAttack();
	}
		break;
	case PLAYER_SKILL::METEOR: {
		MeteorAttack();
	}
		break;
	case PLAYER_SKILL::WATERBALL: {
		if (PlayerMainScript->GetUltReady()) {
			ChaosBallAttack();
			m_bIsUlt = true;
		}
		else {
			WaterBombAttack();
			m_bIsUlt = false;
		}
		
	}
		break;
	case PLAYER_SKILL::NONE:
		break;
	case PLAYER_SKILL::END:
		break;
	default:
		break;
	}

	PlayerMainScript->SetSpeed(0.f);
	RigidBody()->SetVelocity(Vec2(0.f, 0.f));
}

void CPlayerAttackScript::Exit()
{
	CPlayerScript* PlayerMainScript = GetOwner()->GetScript<CPlayerScript>();
	//다시 공격상태로 들어오는것이 아닐 경우
	//예약은 다시 걸었지만, 애니메이션이 끝나기 전에 상태 전환이 되었을때
	//예약을 다시 걸었고, 애니메이션이 끝났지만, 쿨타임이 안되었을 경우
	if (m_bReturnToAttack == false || m_bIsAnimationFinished == false || m_bIsSkillActivated == false) {
		m_IAttackCount = 0;
		m_ECurAttackBtn = PLAYER_ATTACKBUTTON::NONE;
		m_ECurSkill = PLAYER_SKILL::NONE;
		m_bIsSkillActivated = true;
		m_bIsFinalAttack = false;
		m_bIsCharging = false;

		if (m_pWater) {
			DestroyObject(m_pWater);
		}
		PlayerMainScript->SetAttackBtn(PLAYER_ATTACKBUTTON::NONE);
		Animator2D()->GetCurAnim()->Reset();
	}
	//공격상태로 다시 돌아온다.
	else if(m_bReturnToAttack == true) {
		m_bReturnToAttack = false;
		if (m_bIsFinalAttack) {
			m_IAttackCount = 0;
			m_bIsFinalAttack = false;
		}
	}
	else {
		assert(nullptr);
	}
}

void CPlayerAttackScript::ChangeToAttack()
{
	//GetMousePointer------------//
	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
	CPlayerScript* PlayerMainScript = GetOwner()->GetScript<CPlayerScript>();

	if (m_ECurAttackBtn == PLAYER_ATTACKBUTTON::NONE) {
		wchar_t szStr[256] = {};
		wsprintf(szStr, L"공격이 이중으로 들어왔는데 공격키가 설정안되어있음");
		MessageBox(nullptr, szStr, L"FSM전환 실패.", MB_OK);
		assert(nullptr);
	}

	if (m_ECurAttackBtn == PLAYER_ATTACKBUTTON::LBTN) {
		//쿨타임이 돌았을 경우
		if (PlayerMainScript->GetCurCoolTimePerBtn(PLAYER_ATTACKBUTTON::LBTN) <= 0.f) {
			ChangeDir();
			ChangeState((UINT)SCRIPT_TYPE::PLAYERATTACKSCRIPT, true);
		}
		//다시 Idle로 돌아감
		else {
			m_bIsSkillActivated = false;
			ChangeState((UINT)SCRIPT_TYPE::PLAYERIDLESCRIPT, false);
		}
	}
	else if (m_ECurAttackBtn == PLAYER_ATTACKBUTTON::RBTN) {
		if (PlayerMainScript->GetCurCoolTimePerBtn(PLAYER_ATTACKBUTTON::RBTN) <= 0.f) {
			ChangeDir();
			ChangeState((UINT)SCRIPT_TYPE::PLAYERATTACKSCRIPT, true);
		}
		//다시 Idle로 돌아감
		else {
			m_bIsSkillActivated = false;
			ChangeState((UINT)SCRIPT_TYPE::PLAYERIDLESCRIPT, false);
		}
	}
	else if (m_ECurAttackBtn == PLAYER_ATTACKBUTTON::Q) {
		if (PlayerMainScript->GetCurCoolTimePerBtn(PLAYER_ATTACKBUTTON::Q) <= 0.f) {
			ChangeDir();
			ChangeState((UINT)SCRIPT_TYPE::PLAYERATTACKSCRIPT, true);
		}
		//다시 Idle로 돌아감
		else {
			m_bIsSkillActivated = false;
			ChangeState((UINT)SCRIPT_TYPE::PLAYERIDLESCRIPT, false);
		}
	}
	else if (m_ECurAttackBtn == PLAYER_ATTACKBUTTON::E) {
		if (PlayerMainScript->GetCurCoolTimePerBtn(PLAYER_ATTACKBUTTON::E) <= 0.f) {
			ChangeDir();
			ChangeState((UINT)SCRIPT_TYPE::PLAYERATTACKSCRIPT, true);
		}
		//다시 Idle로 돌아감
		else {
			m_bIsSkillActivated = false;
			ChangeState((UINT)SCRIPT_TYPE::PLAYERIDLESCRIPT, false);
		}
	}
	else if (m_ECurAttackBtn == PLAYER_ATTACKBUTTON::R) {
		if (PlayerMainScript->GetCurCoolTimePerBtn(PLAYER_ATTACKBUTTON::R) <= 0.f) {
			ChangeDir();
			ChangeState((UINT)SCRIPT_TYPE::PLAYERATTACKSCRIPT, true);
		}
		//다시 Idle로 돌아감
		else {
			m_bIsSkillActivated = false;
			ChangeState((UINT)SCRIPT_TYPE::PLAYERIDLESCRIPT, false);
		}
	}
}

void CPlayerAttackScript::ChangeDir()
{
	//GetMousePointer------------//
	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
	CGameObject* mouse = Curlevel->FindParentObjectByName(L"MousePointer");
	CPlayerScript* PlayerMainScript = GetOwner()->GetScript<CPlayerScript>();
	CMousePointerScript* MouseScript = mouse->GetScript<CMousePointerScript>();
	Vec4 Mousepos = MouseScript->GetMousePos();
	Vec3 OwnerPos = GetOwner()->Transform()->GetRelativePos();

	// Calculate the angle between the player and the mouse
	double dx = Mousepos.x - OwnerPos.x;
	double dy = Mousepos.y - OwnerPos.y;
	double angle = atan2(dy, dx) * 180 / XM_PI;

	// Convert the angle to a direction
	if (angle > -45 && angle <= 45) {
		PlayerMainScript->SetPlayerDir(DIR_RIGHT);
	}
	else if (angle > 45 && angle <= 135) {
		PlayerMainScript->SetPlayerDir(DIR_UP);
	}
	else if (angle > 135 || angle <= -135) {
		PlayerMainScript->SetPlayerDir(DIR_LEFT);
	}
	else {
		PlayerMainScript->SetPlayerDir(DIR_DOWN);
	}
}

void CPlayerAttackScript::NormalAttack()
{
	//GetMousePointer------------//
	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
	CGameObject* mouse = Curlevel->FindParentObjectByName(L"MousePointer");
	CPlayerScript* PlayerMainScript = GetOwner()->GetScript<CPlayerScript>();
	CMousePointerScript* MouseScript = mouse->GetScript<CMousePointerScript>();
	Vec4 Mousepos = MouseScript->GetMousePos();
	Vec3 OwnerPos = GetOwner()->Transform()->GetRelativePos();
	
	//첫 공격
	if (m_IAttackCount == 1) {
		if (PlayerMainScript->GetPlayerDir() == DIR_UP) {
			Animator2D()->Play(L"Player_Backhand_Up", false);
		}
		else if (PlayerMainScript->GetPlayerDir() == DIR_RIGHT) {
			Animator2D()->Play(L"Player_Backhand_Right", false);
		}
		else if (PlayerMainScript->GetPlayerDir() == DIR_LEFT) {
			Animator2D()->Play(L"Player_Backhand_Left", false);
		}
		else if (PlayerMainScript->GetPlayerDir() == DIR_DOWN) {
			Animator2D()->Play(L"Player_Backhand_Down", false);
		}
		else {
			wchar_t szStr[256] = {};
			wsprintf(szStr, L"Player Dir가 4방향이 아님");
			MessageBox(nullptr, szStr, L"Player공격 실패.", MB_OK);
			assert(nullptr);
		}

		//BackHandAttack 소환
		CGameObject* BackHandAttack = new CGameObject;
		BackHandAttack->SetName(L"BackHandAttack");
		BackHandAttack->AddComponent(new CTransform);
		BackHandAttack->AddComponent(new CMeshRender);
		BackHandAttack->AddComponent(new CAnimator2D);
		BackHandAttack->AddComponent(new CCollider2D);
		BackHandAttack->AddComponent(new CBackHandAttackScript);
		BackHandAttack->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
		BackHandAttack->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"material\\Std2DLightMtrl.mtrl"));
		BackHandAttack->MeshRender()->GetDynamicMaterial();
				
		// calculate the slope of the line from A to B
		double slope = (Mousepos.y - OwnerPos.y) / (Mousepos.x - OwnerPos.x);
		// calculate the angle between the x-axis and the line in radians
		double angle = atan(slope);
		// convert radians to degrees
		angle = angle * 180.0 / XM_PI;
		// if the slope is negative, add 180 degrees to get the acute angle
		if (slope < 0) {
			angle += 180.0;
		}
		// if the slope is positive and y2 < y1, add 360 degrees
		if (Mousepos.y < OwnerPos.y) {
			angle += 180.0;
		}
		BackHandAttack->Transform()->SetRelativeScale(Vec3(100.f, 150.f, 1.f));
		Vec3 vRotation = (Vec3(0.f, 0.f, angle) / 180.f) * XM_PI;

		//마우스 위치에 따라서 4사분면으로 나눔
		BackHandAttack->Transform()->SetRelativePos(Vec3(OwnerPos.x + 70 * cos(vRotation.z), OwnerPos.y + 70 * sin(vRotation.z), OwnerPos.z));
		BackHandAttack->Transform()->SetRelativeRot(vRotation);
		CBackHandAttackScript* AttackScript = BackHandAttack->GetScript<CBackHandAttackScript>();
		AttackScript->SetInputAngle((float)angle);
		BackHandAttack->Collider2D()->SetAbsolute(true);
		BackHandAttack->Collider2D()->SetOffsetScale(Vec2(100.f, 100.f));
		SpawnGameObject(BackHandAttack, BackHandAttack->Transform()->GetRelativePos(), L"PlayerProjectile");

	}
	else if (m_IAttackCount == 2) {
		if (PlayerMainScript->GetPlayerDir() == DIR_UP) {
			Animator2D()->Play(L"Player_Forehand_Up", false);
		}
		else if (PlayerMainScript->GetPlayerDir() == DIR_RIGHT) {
			Animator2D()->Play(L"Player_Forehand_Right", false);
		}
		else if (PlayerMainScript->GetPlayerDir() == DIR_LEFT) {
			Animator2D()->Play(L"Player_Forehand_Left", false);
		}
		else if (PlayerMainScript->GetPlayerDir() == DIR_DOWN) {
			Animator2D()->Play(L"Player_Forehand_Down", false);
		}
		else {
			wchar_t szStr[256] = {};
			wsprintf(szStr, L"Player Dir가 4방향이 아님");
			MessageBox(nullptr, szStr, L"Player공격 실패.", MB_OK);
			assert(nullptr);
		}

		//FrontHandAttack 소환
		CGameObject* ForeHandAttack = new CGameObject;
		ForeHandAttack->SetName(L"FrontHandAttack");
		ForeHandAttack->AddComponent(new CTransform);
		ForeHandAttack->AddComponent(new CMeshRender);
		ForeHandAttack->AddComponent(new CAnimator2D);
		ForeHandAttack->AddComponent(new CCollider2D);
		ForeHandAttack->AddComponent(new CForeHandAttackScript);
		ForeHandAttack->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
		ForeHandAttack->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"material\\Std2DLightMtrl.mtrl"));
		ForeHandAttack->MeshRender()->GetDynamicMaterial();

		// calculate the slope of the line from A to B
		double slope = (Mousepos.y - OwnerPos.y) / (Mousepos.x - OwnerPos.x);
		// calculate the angle between the x-axis and the line in radians
		double angle = atan(slope);
		// convert radians to degrees
		angle = angle * 180.0 / XM_PI;
		// if the slope is negative, add 180 degrees to get the acute angle
		if (slope < 0) {
			angle += 180.0;
		}
		// if the slope is positive and y2 < y1, add 360 degrees
		if (Mousepos.y < OwnerPos.y) {
			angle += 180.0;
		}
		ForeHandAttack->Transform()->SetRelativeScale(Vec3(100.f, 150.f, 1.f));
		Vec3 vRotation = (Vec3(0.f, 0.f, angle) / 180.f) * XM_PI;

		//마우스 위치에 따라서 4사분면으로 나눔
		ForeHandAttack->Transform()->SetRelativePos(Vec3(OwnerPos.x + 70 * cos(vRotation.z), OwnerPos.y + 70 * sin(vRotation.z), OwnerPos.z));
		ForeHandAttack->Transform()->SetRelativeRot(vRotation);
		CForeHandAttackScript* AttackScript = ForeHandAttack->GetScript<CForeHandAttackScript>();
		AttackScript->SetInputAngle((float)angle);
		ForeHandAttack->Collider2D()->SetAbsolute(true);
		ForeHandAttack->Collider2D()->SetOffsetScale(Vec2(100.f, 100.f));
		SpawnGameObject(ForeHandAttack, ForeHandAttack->Transform()->GetRelativePos(), L"PlayerProjectile");
	}
	else if (m_IAttackCount == 3) {
		if (PlayerMainScript->GetPlayerDir() == DIR_UP) {
			Animator2D()->Play(L"Player_PBAoE_Up", false);
		}
		else if (PlayerMainScript->GetPlayerDir() == DIR_RIGHT) {
			Animator2D()->Play(L"Player_PBAoE_Right", false);
		}
		else if (PlayerMainScript->GetPlayerDir() == DIR_LEFT) {
			Animator2D()->Play(L"Player_PBAoE_Left", false);
		}
		else if (PlayerMainScript->GetPlayerDir() == DIR_DOWN) {
			Animator2D()->Play(L"Player_PBAoE_Down", false);
		}
		else {
			wchar_t szStr[256] = {};
			wsprintf(szStr, L"Player Dir가 4방향이 아님");
			MessageBox(nullptr, szStr, L"Player공격 실패.", MB_OK);
			assert(nullptr);
		}

		//BackHandAttack 소환
		CGameObject* BackHandAttack = new CGameObject;
		BackHandAttack->SetName(L"BackHandAttack");
		BackHandAttack->AddComponent(new CTransform);
		BackHandAttack->AddComponent(new CMeshRender);
		BackHandAttack->AddComponent(new CAnimator2D);
		BackHandAttack->AddComponent(new CCollider2D);
		BackHandAttack->AddComponent(new CBackHandAttackScript);
		BackHandAttack->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
		BackHandAttack->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"material\\Std2DLightMtrl.mtrl"));
		BackHandAttack->MeshRender()->GetDynamicMaterial();

		// calculate the slope of the line from A to B
		double slope = (Mousepos.y - OwnerPos.y) / (Mousepos.x - OwnerPos.x);
		// calculate the angle between the x-axis and the line in radians
		double angle = atan(slope);
		// convert radians to degrees
		angle = angle * 180.0 / XM_PI;
		// if the slope is negative, add 180 degrees to get the acute angle
		if (slope < 0) {
			angle += 180.0;
		}
		// if the slope is positive and y2 < y1, add 360 degrees
		if (Mousepos.y < OwnerPos.y) {
			angle += 180.0;
		}
		BackHandAttack->Transform()->SetRelativeScale(Vec3(100.f, 150.f, 1.f));
		Vec3 vRotation = (Vec3(0.f, 0.f, angle) / 180.f) * XM_PI;

		//마우스 위치에 따라서 4사분면으로 나눔
		BackHandAttack->Transform()->SetRelativePos(Vec3(OwnerPos.x + 70 * cos(vRotation.z), OwnerPos.y + 70 * sin(vRotation.z), OwnerPos.z));
		BackHandAttack->Transform()->SetRelativeRot(vRotation);
		CBackHandAttackScript* AttackScript = BackHandAttack->GetScript<CBackHandAttackScript>();
		AttackScript->SetInputAngle((float)angle);
		BackHandAttack->Collider2D()->SetAbsolute(true);
		BackHandAttack->Collider2D()->SetOffsetScale(Vec2(100.f, 100.f));
		SpawnGameObject(BackHandAttack, BackHandAttack->Transform()->GetRelativePos(), L"PlayerProjectile");


		m_bIsFinalAttack = true;
		PlayerMainScript->SetCoolTimePerBtn(m_ECurAttackBtn, 0.3f);
		PlayerMainScript->SetCurCoolTimetoMax(m_ECurAttackBtn);
	}
	

}

void CPlayerAttackScript::SnowFlakeAttack()
{

	CPlayerScript* PlayerMainScript = GetOwner()->GetScript<CPlayerScript>();
	Ptr<CPrefab> SnowPrefab = CResMgr::GetInst()->FindRes<CPrefab>(L"prefab\\SnowFlake.prefab");
	CGameObject* Snowflake = SnowPrefab->Instantiate();
	CSnowFlakeScript* SnowScript = Snowflake->GetScript<CSnowFlakeScript>();
	SnowScript->SetStartangle(0.f);
	SpawnGameObject(Snowflake, Vec3(0.f, 0.f, 0.f), L"PlayerProjectile");
	
	CGameObject* Snowflake2 = SnowPrefab->Instantiate();
	CSnowFlakeScript* SnowScript2 = Snowflake2->GetScript<CSnowFlakeScript>();
	SnowScript2->SetStartangle(120.f);
	SpawnGameObject(Snowflake2, Vec3(0.f, 0.f, 0.f), L"PlayerProjectile");

	CGameObject* Snowflake3 = SnowPrefab->Instantiate();
	CSnowFlakeScript* SnowScript3 = Snowflake3->GetScript<CSnowFlakeScript>();
	SnowScript3->SetStartangle(240.f);
	SpawnGameObject(Snowflake3, Vec3(0.f, 0.f, 0.f), L"PlayerProjectile");
	PlayerMainScript->SetCurCoolTimetoMax(m_ECurAttackBtn);

	if (PlayerMainScript->GetPlayerDir() == DIR_UP) {
		Animator2D()->Play(L"Player_PBAoE_Up", false);
	}
	else if (PlayerMainScript->GetPlayerDir() == DIR_RIGHT) {
		Animator2D()->Play(L"Player_PBAoE_Right", false);
	}
	else if (PlayerMainScript->GetPlayerDir() == DIR_LEFT) {
		Animator2D()->Play(L"Player_PBAoE_Left", false);
	}
	else if (PlayerMainScript->GetPlayerDir() == DIR_DOWN) {
		Animator2D()->Play(L"Player_PBAoE_Down", false);
	}
	else {
		wchar_t szStr[256] = {};
		wsprintf(szStr, L"Player Dir가 4방향이 아님");
		MessageBox(nullptr, szStr, L"Player공격 실패.", MB_OK);
		assert(nullptr);
	}
}


void CPlayerAttackScript::DragonAttack()
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
	// if the slope is negative, add 180 degrees to get the acute angle
	if (slope < 0) {
		angle += 180.0;
	}
	// if the slope is positive and y2 < y1, add 360 degrees
	if (Mousepos.y < OwnerPos.y) {
		angle += 180.0;
	}

	Ptr<CPrefab> DragonPrefab = CResMgr::GetInst()->FindRes<CPrefab>(L"prefab\\DragonArc.prefab");
	CGameObject* Dragon = DragonPrefab->Instantiate();
	Dragon->AddComponent(new CLight2D);
	Dragon->Light2D()->SetLightDiffuse(Vec3(1.f, 1.f, 1.f));
	Dragon->Light2D()->SetLightType(LIGHT_TYPE::POINT);
	Dragon->Light2D()->SetRadius(100.f);
	CDragonBreathScript* DragonScript = Dragon->GetScript<CDragonBreathScript>();
	Dragon->Transform()->SetRelativeScale(Vec3(100.f, 100.f, 1.f));
	DragonScript->SetInputAngle(angle);
	DragonScript->SetStartPos(OwnerPos);
	SpawnGameObject(Dragon, Transform()->GetRelativePos(), L"PlayerProjectile");

	CGameObject* Dragon2 = DragonPrefab->Instantiate();
	Dragon2->AddComponent(new CLight2D);
	Dragon2->Light2D()->SetLightDiffuse(Vec3(1.f, 1.f, 1.f));
	Dragon2->Light2D()->SetLightType(LIGHT_TYPE::POINT);
	Dragon2->Light2D()->SetRadius(100.f);
	CDragonBreathScript* DragonScript2 = Dragon2->GetScript<CDragonBreathScript>();
	Dragon2->Transform()->SetRelativeScale(Vec3(100.f, 100.f, 1.f));
	DragonScript2->SetInputAngle(angle);
	DragonScript2->SetStartPos(OwnerPos);
	DragonScript2->SetWaitTime(0.2f);
	vector<CGameObject*>::const_iterator iter = Dragon->GetChild().begin();
	CGameObject* DragonParticle2 = (*iter);
	CDragonParticleScript* DragonParticleScript2 = DragonParticle2->GetScript<CDragonParticleScript>();
	DragonParticleScript2->SetWaittime(0.2f);
	SpawnGameObject(Dragon2, Transform()->GetRelativePos(), L"PlayerProjectile");

	CGameObject* Dragon3 = DragonPrefab->Instantiate();

	CDragonBreathScript* DragonScript3 = Dragon3->GetScript<CDragonBreathScript>();
	Dragon3->AddComponent(new CLight2D);
	Dragon3->Light2D()->SetLightDiffuse(Vec3(1.f, 1.f, 1.f));
	Dragon3->Light2D()->SetLightType(LIGHT_TYPE::POINT);
	Dragon3->Light2D()->SetRadius(100.f);
	Dragon3->Transform()->SetRelativeScale(Vec3(100.f, 100.f, 1.f));
	DragonScript3->SetInputAngle(angle);
	DragonScript3->SetStartPos(OwnerPos);
	DragonScript3->SetWaitTime(0.4f);
	vector<CGameObject*>::const_iterator iter2 = Dragon->GetChild().begin();
	CGameObject* DragonParticle3 = (*iter2);
	CDragonParticleScript* DragonParticleScript3 = DragonParticle3->GetScript<CDragonParticleScript>();
	DragonParticleScript3->SetWaittime(0.4f);
	SpawnGameObject(Dragon3, Transform()->GetRelativePos(), L"PlayerProjectile");

	CGameObject* Dragon4 = DragonPrefab->Instantiate();
	Dragon4->AddComponent(new CLight2D);
	Dragon4->Light2D()->SetLightDiffuse(Vec3(1.f, 1.f, 1.f));
	Dragon4->Light2D()->SetLightType(LIGHT_TYPE::POINT);
	Dragon4->Light2D()->SetRadius(100.f);
	CDragonBreathScript* DragonScript4 = Dragon4->GetScript<CDragonBreathScript>();
	Dragon4->Transform()->SetRelativeScale(Vec3(100.f, 100.f, 1.f));
	DragonScript4->SetInputAngle(angle);
	DragonScript4->SetStartPos(OwnerPos);
	DragonScript4->SetWaitTime(0.6f);
	vector<CGameObject*>::const_iterator iter3 = Dragon4->GetChild().begin();
	CGameObject* DragonParticle4 = (*iter3);
	CDragonParticleScript* DragonParticleScript4 = DragonParticle4->GetScript<CDragonParticleScript>();
	DragonParticleScript4->SetWaittime(0.6f);
	SpawnGameObject(Dragon4, Transform()->GetRelativePos(), L"PlayerProjectile");

	if (PlayerMainScript->GetPlayerDir() == DIR_UP) {
		Animator2D()->Play(L"Player_Backhand_Up", false);
	}
	else if (PlayerMainScript->GetPlayerDir() == DIR_RIGHT) {
		Animator2D()->Play(L"Player_Backhand_Right", false);
	}
	else if (PlayerMainScript->GetPlayerDir() == DIR_LEFT) {
		Animator2D()->Play(L"Player_Backhand_Left", false);
	}
	else if (PlayerMainScript->GetPlayerDir() == DIR_DOWN) {
		Animator2D()->Play(L"Player_Backhand_Down", false);
	}
	else {
		wchar_t szStr[256] = {};
		wsprintf(szStr, L"Player Dir가 4방향이 아님");
		MessageBox(nullptr, szStr, L"Player공격 실패.", MB_OK);
		assert(nullptr);
	}

	PlayerMainScript->SetCurCoolTimetoMax(m_ECurAttackBtn);

}

void CPlayerAttackScript::MeteorAttack()
{
	//GetMousePointer------------//
	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
	CGameObject* mouse = Curlevel->FindParentObjectByName(L"MousePointer");
	CPlayerScript* PlayerMainScript = GetOwner()->GetScript<CPlayerScript>();
	CMousePointerScript* MouseScript = mouse->GetScript<CMousePointerScript>();
	Vec4 Mousepos = MouseScript->GetMousePos();
	Vec3 OwnerPos = GetOwner()->Transform()->GetRelativePos();

	

	CGameObject* Circle = new CGameObject;
	Circle->SetName(L"MeteorSpawnCircle");
	Circle->AddComponent(new CTransform);
	Circle->AddComponent(new CMeshRender);
	Circle->AddComponent(new CAnimator2D);
	Vec3 CirclePos = Vec3(Transform()->GetRelativePos().x, Transform()->GetRelativePos().y, 300.f);
	Circle->Transform()->SetRelativePos(CirclePos);
	Circle->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	Circle->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"material\\Std2DLightMtrl.mtrl"));
	Circle->MeshRender()->GetDynamicMaterial();
	Circle->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 300.f));
	Circle->AddComponent(new CMeteorSpawnCircleScript);
	SpawnGameObject(Circle, Vec3(Mousepos.x, Mousepos.y, 300.f), L"Default");

	CGameObject* Meteor = new CGameObject;
	Meteor->SetName(L"Meteor");
	Meteor->AddComponent(Transform()->Clone());
	Meteor->AddComponent(new CMeshRender);
	Meteor->AddComponent(new CAnimator2D);
	Meteor->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	Meteor->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"material\\Std2DLightMtrl.mtrl"));
	Meteor->MeshRender()->GetDynamicMaterial();
	Meteor->Transform()->SetRelativeScale(Vec3(332.f, 800.f, 1.f));

	Meteor->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 38.f / 180.f * XM_PI));
	Meteor->AddComponent(new CMeteorScript);
	CMeteorScript* MeteorScript = Meteor->GetScript<CMeteorScript>();
	MeteorScript->SetLandPos(Mousepos);
	MeteorScript->SetSpawnCircle(Circle);
	SpawnGameObject(Meteor, Mousepos, L"Default");

	if (PlayerMainScript->GetPlayerDir() == DIR_UP) {
		Animator2D()->Play(L"Player_Backhand_Up", false);
	}
	else if (PlayerMainScript->GetPlayerDir() == DIR_RIGHT) {
		Animator2D()->Play(L"Player_Backhand_Right", false);
	}
	else if (PlayerMainScript->GetPlayerDir() == DIR_LEFT) {
		Animator2D()->Play(L"Player_Backhand_Left", false);
	}
	else if (PlayerMainScript->GetPlayerDir() == DIR_DOWN) {
		Animator2D()->Play(L"Player_Backhand_Down", false);
	}
	else {
		wchar_t szStr[256] = {};
		wsprintf(szStr, L"Player Dir가 4방향이 아님");
		MessageBox(nullptr, szStr, L"Player공격 실패.", MB_OK);
		assert(nullptr);
	}

	PlayerMainScript->SetCurCoolTimetoMax(m_ECurAttackBtn);
}

void CPlayerAttackScript::WaterBombAttack()
{	
	
	Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\FlameChargeUp.wav");
	pSound->Play(1, 0.2, true);

	//GetMousePointer------------//
	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
	CGameObject* mouse = Curlevel->FindParentObjectByName(L"MousePointer");
	CPlayerScript* PlayerMainScript = GetOwner()->GetScript<CPlayerScript>();
	CMousePointerScript* MouseScript = mouse->GetScript<CMousePointerScript>();
	Vec4 Mousepos = MouseScript->GetMousePos();
	Vec3 OwnerPos = GetOwner()->Transform()->GetRelativePos();
	if (m_bIsCharging == false) {
		m_pWater = new CGameObject;
		m_pWater->SetName(L"WaterBomb");
		m_bIsCharging = true;
		
		m_pWater->AddComponent(new CTransform);
		m_pWater->AddComponent(new CMeshRender);
		m_pWater->AddComponent(new CAnimator2D);
		m_pWater->AddComponent(new CWaterBombScript);
		m_pWater->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
		m_pWater->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"material\\Std2DLightMtrl.mtrl"));
		m_pWater->MeshRender()->GetDynamicMaterial();
		Vec2 offset = Vec2(Mousepos.x - OwnerPos.x, Mousepos.y - OwnerPos.y);
		offset.Normalize();
		m_pWater->Transform()->SetRelativePos(Vec3(OwnerPos.x - offset.x * 50.f, OwnerPos.y - offset.y * 50.f, 300.f));
		SpawnGameObject(m_pWater, m_pWater->Transform()->GetRelativePos(), L"PlayerProjectile");
	}
	else {
		Vec2 offset = Vec2(Mousepos.x - OwnerPos.x, Mousepos.y - OwnerPos.y);
		offset.Normalize();
		m_pWater->Transform()->SetRelativePos(Vec3(OwnerPos.x - offset.x * 50.f, OwnerPos.y - offset.y * 50.f, 300.f));
		KEY btnkey;
		switch (m_ECurAttackBtn)
		{
		case PLAYER_ATTACKBUTTON::LBTN:
			btnkey = KEY::LBTN;
			break;
		case PLAYER_ATTACKBUTTON::RBTN:
			btnkey = KEY::RBTN;
			break;
		case PLAYER_ATTACKBUTTON::Q:
			btnkey = KEY::Q;
			break;
		case PLAYER_ATTACKBUTTON::E:
			btnkey = KEY::E;
			break;
		case PLAYER_ATTACKBUTTON::R:
			btnkey = KEY::R;
			break;
		case PLAYER_ATTACKBUTTON::NONE:
			assert(nullptr);
			break;
		default:
			break;
		}
		if (KEY_RELEASE(btnkey) || KEY_NONE(btnkey)) {
			CWaterBombScript* BombScript = m_pWater->GetScript<CWaterBombScript>();
			BombScript->ShootBomb(Vec3(offset.x, offset.y, 1.f));
			m_pWater = nullptr;
			m_bIsCharging = false;
		}
	}

	if (PlayerMainScript->GetPlayerDir() == DIR_UP) {
		Animator2D()->Play(L"Player_PBAoE_Up", false);
	}
	else if (PlayerMainScript->GetPlayerDir() == DIR_RIGHT) {
		Animator2D()->Play(L"Player_PBAoE_Right", false);
	}
	else if (PlayerMainScript->GetPlayerDir() == DIR_LEFT) {
		Animator2D()->Play(L"Player_PBAoE_Left", false);
	}
	else if (PlayerMainScript->GetPlayerDir() == DIR_DOWN) {
		Animator2D()->Play(L"Player_PBAoE_Down", false);
	}

	PlayerMainScript->SetCurCoolTimetoMax(m_ECurAttackBtn);
}

void CPlayerAttackScript::ChaosBallAttack()
{
	Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\FlameChargeUp.wav");
	pSound->Play(1, 0.2, true);

	//GetMousePointer------------//
	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
	CGameObject* mouse = Curlevel->FindParentObjectByName(L"MousePointer");
	CPlayerScript* PlayerMainScript = GetOwner()->GetScript<CPlayerScript>();
	CMousePointerScript* MouseScript = mouse->GetScript<CMousePointerScript>();
	Vec4 Mousepos = MouseScript->GetMousePos();
	Vec3 OwnerPos = GetOwner()->Transform()->GetRelativePos();
	if (m_bIsCharging == false) {
		m_pWater = new CGameObject;
		m_pWater->SetName(L"ChaosBomb");
		m_bIsCharging = true;

		m_pWater->AddComponent(new CTransform);
		m_pWater->AddComponent(new CMeshRender);
		m_pWater->AddComponent(new CAnimator2D);
		m_pWater->AddComponent(new CChaosBombScript);
		m_pWater->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
		m_pWater->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"material\\Std2DLightMtrl.mtrl"));
		m_pWater->MeshRender()->GetDynamicMaterial();
		Vec2 offset = Vec2(Mousepos.x - OwnerPos.x, Mousepos.y - OwnerPos.y);
		offset.Normalize();
		m_pWater->Transform()->SetRelativePos(Vec3(OwnerPos.x - offset.x * 50.f, OwnerPos.y - offset.y * 50.f, 300.f));
		SpawnGameObject(m_pWater, m_pWater->Transform()->GetRelativePos(), L"PlayerProjectile");
	}
	/*else {
		Vec2 offset = Vec2(Mousepos.x - OwnerPos.x, Mousepos.y - OwnerPos.y);
		offset.Normalize();
		m_pWater->Transform()->SetRelativePos(Vec3(OwnerPos.x - offset.x * 50.f, OwnerPos.y - offset.y * 50.f, 300.f));
		KEY btnkey;
		switch (m_ECurAttackBtn)
		{
		case PLAYER_ATTACKBUTTON::LBTN:
			btnkey = KEY::LBTN;
			break;
		case PLAYER_ATTACKBUTTON::RBTN:
			btnkey = KEY::RBTN;
			break;
		case PLAYER_ATTACKBUTTON::Q:
			btnkey = KEY::Q;
			break;
		case PLAYER_ATTACKBUTTON::E:
			btnkey = KEY::E;
			break;
		case PLAYER_ATTACKBUTTON::R:
			btnkey = KEY::R;
			break;
		case PLAYER_ATTACKBUTTON::NONE:
			assert(nullptr);
			break;
		default:
			break;
		}
		if (KEY_RELEASE(btnkey) || KEY_NONE(btnkey)) {
			CChaosBombScript* BombScript = m_pWater->GetScript<CChaosBombScript>();
			BombScript->ShootBomb(Vec3(offset.x, offset.y, 1.f));
			m_pWater = nullptr;
			m_bIsCharging = false;

			PlayerStat stat = PlayerMainScript->GetStat();
			stat.CurMP = 0.f;
			PlayerMainScript->SetStat(stat);
		}
	}*/

	if (PlayerMainScript->GetPlayerDir() == DIR_UP) {
		Animator2D()->Play(L"Player_PBAoE_Up", false);
	}
	else if (PlayerMainScript->GetPlayerDir() == DIR_RIGHT) {
		Animator2D()->Play(L"Player_PBAoE_Right", false);
	}
	else if (PlayerMainScript->GetPlayerDir() == DIR_LEFT) {
		Animator2D()->Play(L"Player_PBAoE_Left", false);
	}
	else if (PlayerMainScript->GetPlayerDir() == DIR_DOWN) {
		Animator2D()->Play(L"Player_PBAoE_Down", false);
	}

	PlayerMainScript->SetCurCoolTimetoMax(m_ECurAttackBtn);
}

void CPlayerAttackScript::AttackCharging()
{

	//GetMousePointer------------//
	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
	CGameObject* mouse = Curlevel->FindParentObjectByName(L"MousePointer");
	CPlayerScript* PlayerMainScript = GetOwner()->GetScript<CPlayerScript>();
	CMousePointerScript* MouseScript = mouse->GetScript<CMousePointerScript>();
	Vec4 Mousepos = MouseScript->GetMousePos();
	Vec3 OwnerPos = GetOwner()->Transform()->GetRelativePos();
	Vec2 offset = Vec2(Mousepos.x - OwnerPos.x, Mousepos.y - OwnerPos.y);
	offset.Normalize();
	m_pWater->Transform()->SetRelativePos(Vec3(OwnerPos.x - offset.x * 50.f, OwnerPos.y - offset.y * 50.f, 300.f));

	if (PlayerMainScript->GetPlayerDir() == DIR_UP) {
		Animator2D()->Play(L"Player_Forehand_Up_Ready", true);
	}
	else if (PlayerMainScript->GetPlayerDir() == DIR_RIGHT) {
		Animator2D()->Play(L"Player_Forehand_Right_Ready", true);
	}
	else if (PlayerMainScript->GetPlayerDir() == DIR_LEFT) {
		Animator2D()->Play(L"Player_Forehand_Left_Ready", true);
	}
	else if (PlayerMainScript->GetPlayerDir() == DIR_DOWN) {
		Animator2D()->Play(L"Player_Forehand_Down_Ready", true);
	}

	ChangeDir();

	KEY btnkey;
	switch (m_ECurAttackBtn)
	{
	case PLAYER_ATTACKBUTTON::LBTN:
		btnkey = KEY::LBTN;
		break;
	case PLAYER_ATTACKBUTTON::RBTN:
		btnkey = KEY::RBTN;
		break;
	case PLAYER_ATTACKBUTTON::Q:
		btnkey = KEY::Q;
		break;
	case PLAYER_ATTACKBUTTON::E:
		btnkey = KEY::E;
		break;
	case PLAYER_ATTACKBUTTON::R:
		btnkey = KEY::R;
		break;
	case PLAYER_ATTACKBUTTON::NONE:
		assert(nullptr);
		break;
	default:
		break;
	}
	if (KEY_RELEASE(btnkey) || KEY_NONE(btnkey)) {
		if (m_bIsUlt) {
			CChaosBombScript* BombScript = m_pWater->GetScript<CChaosBombScript>();
			BombScript->ShootBomb(Vec3(offset.x, offset.y, 1.f));
			PlayerStat stat = PlayerMainScript->GetStat();
			stat.CurMP = 0.f;
			PlayerMainScript->SetStat(stat);
		
		}
		else {
			CWaterBombScript* BombScript = m_pWater->GetScript<CWaterBombScript>();
			BombScript->ShootBomb(Vec3(offset.x, offset.y, 1.f));
		}
	
		m_pWater = nullptr;
		m_bIsCharging = false;
		if (PlayerMainScript->GetPlayerDir() == DIR_UP) {
			Animator2D()->Play(L"Player_Forehand_Up", false);
		}
		else if (PlayerMainScript->GetPlayerDir() == DIR_RIGHT) {
			Animator2D()->Play(L"Player_Forehand_Right", false);
		}
		else if (PlayerMainScript->GetPlayerDir() == DIR_LEFT) {
			Animator2D()->Play(L"Player_Forehand_Left", false);
		}
		else if (PlayerMainScript->GetPlayerDir() == DIR_DOWN) {
			Animator2D()->Play(L"Player_Forehand_Down", false);
		}
	}

}
