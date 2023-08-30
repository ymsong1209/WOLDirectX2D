#include "pch.h"
#include "CBossAttackScript.h"
#include "CBossScript.h"
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include "CBossDrillScript.h"
#include "CRockFistScript.h"
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim2D.h>
#include <Engine/CCollisionMgr.h>
#include <Engine/CEventMgr.h>
#include "CPlayerCameraScript.h"
#include "CBossLeapAttackScript.h"
#include "CBossLeapAttackHitBoxScript.h"
#include "CTerraScript.h"
#include "CMainLightScript.h"

CBossAttackScript::CBossAttackScript()
	:CScript((UINT)SCRIPT_TYPE::BOSSATTACKSCRIPT)
	,m_iAttackCount(0)
	,m_iAttackType(0)
	,m_pDrill(nullptr)
	,m_iRockPunchCount(0)
	,m_iLeapStage(0)
	,m_bDrillSpawned(false)
	,m_fTime(0.f)
{
	SetActive(false);
	AddScriptParam(SCRIPT_PARAM::INT, &m_iAttackCount, "AttackCount");
	AddScriptParam(SCRIPT_PARAM::INT, &m_iAttackType, "AttackType");
	AddScriptParam(SCRIPT_PARAM::INT, &m_iRockPunchCount, "RockPunchCount");
}

CBossAttackScript::~CBossAttackScript()
{
}

void CBossAttackScript::begin()
{
}

void CBossAttackScript::tick()
{
	if (!IsActive()) return;
	if (m_iAttackCount == -1) return;
	if (m_iAttackCount > 3) {
		m_iAttackCount = -1;
		ChangeState((UINT)SCRIPT_TYPE::BOSSFLEXSCRIPT, false);
		return;
	}

	if (m_iAttackType == (UINT)EType::DRILL) {
		if (abs(RigidBody()->GetVelocity().x) < 1.f && abs(RigidBody()->GetVelocity().y) < 1.f && m_bDrillSpawned) {
			
			ChangeState((UINT)SCRIPT_TYPE::BOSSATTACKSCRIPT,true);
			CBossDrillScript* DrillScript = m_pDrill->GetScript<CBossDrillScript>();
			Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\Drill.wav");
			pSound->Stop();
			DestroyObject(m_pDrill);
			m_bDrillSpawned = false;
			m_pDrill = nullptr;
		}
		return;
	}
	else if (m_iAttackType == (UINT)EType::ROCKPUNCH) {
		if (Animator2D()->GetCurAnim()->IsFinish()) {
			++m_iRockPunchCount;
			Animator2D()->GetCurAnim()->Reset();
			if (m_iRockPunchCount > 2) {
				m_iRockPunchCount = 0;
				ChangeState((UINT)SCRIPT_TYPE::BOSSATTACKSCRIPT, true);
			}
			else {
				RockPunchAttack();
			}
		}
		return;
	}

	else if (m_iAttackType == (UINT)EType::LEAPATTACK) {
		//지금은 LeapWindUp상태
		if (m_iLeapStage == 0 && Animator2D()->GetCurAnim()->IsFinish()) {
			++m_iLeapStage;
			Leap();
		}
		//Leap상태
		else if (m_iLeapStage == 1) {
			if (abs(Transform()->GetRelativePos().x - m_vMiddlePos.x) < 2.0f ) {
				RigidBody()->SetVelocity(Vec2(0.f, 0.f));
				++m_iLeapStage;
				LeapFall();
			}
			else {
				RigidBody()->SetVelocity(Vec2(m_vBossToMiddle.x * 700.f, m_vBossToMiddle.y * 700.f));
			}
		}
		//LeapFall상태
		else if (m_iLeapStage == 2) {
			if (abs(Transform()->GetRelativePos().x - m_vPlayerPos.x) < 2.0f) {
				RigidBody()->SetVelocity(Vec2(0.f, 0.f));
				++m_iLeapStage;
				LeapLand();
			}
			else {
				RigidBody()->SetVelocity(Vec2(m_vMiddleToPlayer.x * 700.f, m_vMiddleToPlayer.y * 700.f));
			}
		}
		//LeapLand상태
		else if (m_iLeapStage == 3) {
			if (Animator2D()->GetCurAnim()->IsFinish()) {
				Animator2D()->GetCurAnim()->Reset();
				ChangeState((UINT)SCRIPT_TYPE::BOSSATTACKSCRIPT, true);
				m_iLeapStage = 0;
			}
		}
	}

	else if (m_iAttackType == (UINT)EType::TOWEROFTERRA) {
		m_fTime += DT;
		if (m_fTime > 3.0f) {
			ChangeState((UINT)SCRIPT_TYPE::BOSSATTACKSCRIPT, true);
			m_fTime = 0.f;
		}
	}

	else if (m_iAttackType == (UINT)EType::SHUTLIGHT) {
		if (Animator2D()->GetCurAnim()->IsFinish()) {
			Animator2D()->GetCurAnim()->Reset();
			ChangeState((UINT)SCRIPT_TYPE::BOSSATTACKSCRIPT, true);
		}
	}
	else {
		assert(nullptr);
	}

}

void CBossAttackScript::Enter()
{
	if (m_iAttackCount > 2) {
		//ChangeState((UINT)SCRIPT_TYPE::BOSSFLEXSCRIPT, false);
		//m_iAttackCount = -1;
		++m_iAttackCount;
		int a = 0;
		return;
	}
	++m_iAttackCount;
	++m_iAttackType;

	if (m_iAttackType == (UINT)EType::DRILL) {
		DrillAttack();
	}
	else if (m_iAttackType == (UINT)EType::ROCKPUNCH) {
		RockPunchAttack();
	}
	else if (m_iAttackType == (UINT)EType::LEAPATTACK) {
		LeapWindUp();
	}
	else if (m_iAttackType == (UINT)EType::TOWEROFTERRA) {
		TowerOfTerraAttack();
	}
	else if (m_iAttackType == (UINT)EType::SHUTLIGHT) {
		ShutLightAttack();
	}
	else {
		m_iAttackType = (UINT)EType::DRILL;
		DrillAttack();
	}
	

}

void CBossAttackScript::Exit()
{
	if (m_bDrillSpawned) {
		Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\Drill.wav");
		pSound->Stop();
		DestroyObject(m_pDrill);
		m_bDrillSpawned = false;
		m_pDrill = nullptr;
	}
}

void CBossAttackScript::DrillAttack()
{
	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
	CGameObject* Player = Curlevel->FindParentObjectByName(L"Player");
	Vec3 CurPos = Transform()->GetRelativePos();
	Vec3 PlayerPos = Player->Transform()->GetRelativePos();

	if (m_pDrill) {
		assert(nullptr);
	}
	m_pDrill = new CGameObject;
	m_pDrill->SetName(L"Drill");
	m_pDrill->AddComponent(new CTransform);
	m_pDrill->AddComponent(new CMeshRender);
	m_pDrill->AddComponent(new CAnimator2D);
	m_pDrill->AddComponent(new CRigidBody);
	m_pDrill->AddComponent(new CCollider2D);
	m_pDrill->AddComponent(new CBossDrillScript);
	m_pDrill->Transform()->SetAbsolute(true);
	m_pDrill->Transform()->SetRelativeScale(Vec3(80.f, 60.f, 1.f));
	m_pDrill->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	m_pDrill->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"material\\Std2DLightMtrl.mtrl"));
	m_pDrill->MeshRender()->GetDynamicMaterial();
	m_pDrill->Collider2D()->SetAbsolute(false);
	m_pDrill->Collider2D()->SetOffsetScale(Vec2(1.f, 1.f));

	//x축으로 더 멀리 있음 ->왼쪽 or오른쪽 봐야함
	if (abs(CurPos.x - PlayerPos.x) > abs(CurPos.y - PlayerPos.y)) {
		if (CurPos.x < PlayerPos.x) {
			Animator2D()->Play(L"Boss_Punch_Right", false);
			m_pDrill->Transform()->SetRelativePos(Vec3(80.f, 0.f, -10.f));
			m_pDrill->Transform()->SetRelativeRot(Vec3(0.f, 0.f, XMConvertToRadians(0.f)));
		}
		else {
			Animator2D()->Play(L"Boss_Punch_Left", false);
			m_pDrill->Transform()->SetRelativePos(Vec3(-80.f, 0.f, -10.f));
			m_pDrill->Transform()->SetRelativeRot(Vec3(0.f, 0.f, XMConvertToRadians(180.f)));
		}
	}
	else {
		if (CurPos.y < PlayerPos.y) {
			Animator2D()->Play(L"Boss_Punch_Up", false);
			m_pDrill->Transform()->SetRelativePos(Vec3(0.f, 100.f, -10.f));
			m_pDrill->Transform()->SetRelativeRot(Vec3(0.f, 0.f, XMConvertToRadians(90.f)));
		}
		else {
			Animator2D()->Play(L"Boss_Punch_Down", false);
			m_pDrill->Transform()->SetRelativePos(Vec3(0.f, -100.f, -10.f));
			m_pDrill->Transform()->SetRelativeRot(Vec3(0.f, 0.f, XMConvertToRadians(270.f)));
		}
	}
	
	SpawnGameObject(m_pDrill, m_pDrill->Transform()->GetRelativePos(), L"MonsterProjectile");
	Vec2 Direction = Vec2(PlayerPos.x - CurPos.x, PlayerPos.y - CurPos.y);
	Direction.Normalize();
	RigidBody()->SetVelocity(Vec2(Direction.x * 700.f, Direction.y * 700.f));
	m_bDrillSpawned = true;
	CBossDrillScript* Script = m_pDrill->GetScript<CBossDrillScript>();
	Script->SetOwner(GetOwner());
	Script->SetDirection(Direction);
	Script->init();
	
	Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\Drill.wav");
	pSound->Play(0, 0.2, true);
	
}

void CBossAttackScript::RockPunchAttack()
{
	CGameObject* RockFist = new CGameObject;
	RockFist->SetName(L"RockFist");
	RockFist->AddComponent(new CTransform);
	RockFist->AddComponent(new CMeshRender);
	RockFist->AddComponent(new CCollider2D);
	RockFist->AddComponent(new CRigidBody);
	RockFist->AddComponent(new CRockFistScript);
	RockFist->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	RockFist->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"material\\Std2DLightMtrl.mtrl"));
	RockFist->MeshRender()->GetDynamicMaterial();
	RockFist->Transform()->SetRelativeScale(Vec3(80.f, 80.f, 1.f));
	RockFist->Collider2D()->SetOffsetScale(Vec2(1.f, 1.f));
	RockFist->Collider2D()->SetAbsolute(false);

	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
	CGameObject* Player = Curlevel->FindParentObjectByName(L"Player");
	Vec3 CurPos = Transform()->GetRelativePos();
	Vec3 PlayerPos = Player->Transform()->GetRelativePos();

	//x축으로 더 멀리 있음 ->왼쪽 or오른쪽 봐야함
	if (abs(CurPos.x - PlayerPos.x) > abs(CurPos.y - PlayerPos.y)) {
		if (CurPos.x < PlayerPos.x) {
			Animator2D()->Play(L"Boss_Swing_Right", false);
		}
		else {
			Animator2D()->Play(L"Boss_Swing_Left", false);
		}
	}
	else {
		if (CurPos.y < PlayerPos.y) {
			Animator2D()->Play(L"Boss_Swing_Up", false);
		}
		else {
			Animator2D()->Play(L"Boss_Swing_Down", false);
		}
	}

	CRockFistScript* Script = RockFist->GetScript<CRockFistScript>();
	Script->SetBossPos(CurPos);
	Script->SetPlayerPos(PlayerPos);

	SpawnGameObject(RockFist, Vec3(CurPos.x, CurPos.y - 80.f, CurPos.z - 20.f), L"MonsterProjectile");

	Ptr<CSound> RockSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\GroundSlam.wav");
	RockSound->Play(1, 0.2, true);
}


void CBossAttackScript::LeapWindUp()
{
	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
	CGameObject* Player = Curlevel->FindParentObjectByName(L"Player");
	Vec3 CurPos = Transform()->GetRelativePos();
	Vec3 PlayerPos = Player->Transform()->GetRelativePos();

	m_vBossPos = CurPos;
	m_vPlayerPos = PlayerPos;
	Animator2D()->Play(L"Boss_LeapWindUp", false);

	Ptr<CSound> WindUp = CResMgr::GetInst()->FindRes<CSound>(L"sound\\AirWindup.wav");
	WindUp->Play(1, 0.2, true);
}

void CBossAttackScript::Leap()
{
	//Boss와 Wall,PitWall 충돌 해제
	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
	UINT CollisionMatrix[MAX_LAYER];
	for (UINT i = 0; i < MAX_LAYER; ++i) {
		CollisionMatrix[i] = CCollisionMgr::GetInst()->GetMatrix()[i];
	}

	for (UINT iRow = 0; iRow < MAX_LAYER; ++iRow)
	{
		for (UINT iCol = iRow; iCol < MAX_LAYER; ++iCol)
		{
			if (CollisionMatrix[iRow] & (1 << iCol)) {
				CLayer* Rowlayer = Curlevel->GetLayer(iRow);
				CLayer* Collayer = Curlevel->GetLayer(iCol);
				string RowName = string(Rowlayer->GetName().begin(), Rowlayer->GetName().end());
				string ColName = string(Collayer->GetName().begin(), Collayer->GetName().end());
				if ((RowName == "Monster" || ColName == "Monster") && (RowName == "Wall" || ColName == "Wall")) {
					CollisionMatrix[iRow] -= (1 << iCol);
					CCollisionMgr::GetInst()->SetMatrix(CollisionMatrix);
				}
				else if ((RowName == "Monster" || ColName == "Monster") && (RowName == "PitWall" || ColName == "PitWall")) {
					CollisionMatrix[iRow] -= (1 << iCol);
					CCollisionMgr::GetInst()->SetMatrix(CollisionMatrix);
				}
			}
		}
	}


	//boss가 플레이어의 왼쪽에 있다.
	if (m_vBossPos.x < m_vPlayerPos.x) {
		m_vMiddlePos = Vec3(m_vBossPos.x + (m_vPlayerPos.x - m_vBossPos.x)/2.f, m_vBossPos.y + 250.f, 1.f);
	}
	else {
		m_vMiddlePos = Vec3(m_vBossPos.x - (m_vBossPos.x - m_vPlayerPos.x)/2.f, m_vBossPos.y + 250.f, 1.f);
	}
	m_vBossToMiddle = Vec2(m_vMiddlePos.x - m_vBossPos.x, m_vMiddlePos.y - m_vBossPos.y);
	m_vBossToMiddle.Normalize();
	RigidBody()->SetVelocity(Vec2(m_vBossToMiddle.x * 700.f, m_vBossToMiddle.y * 700.f));
	Animator2D()->Play(L"Boss_Leap", false);
}

void CBossAttackScript::LeapFall()
{
	m_vMiddleToPlayer = Vec2(m_vPlayerPos.x - m_vMiddlePos.x, m_vPlayerPos.y - m_vMiddlePos.y);
	m_vMiddleToPlayer.Normalize();
	RigidBody()->SetVelocity(Vec2(m_vMiddleToPlayer.x * 700.f, m_vMiddleToPlayer.y * 700.f));
	Animator2D()->Play(L"Boss_LeapFall", false);
}

void CBossAttackScript::LeapLand()
{
	Animator2D()->Play(L"Boss_LeapLand", false);
	CGameObject* MainCam = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"MainCamera");
	CPlayerCameraScript* Script = MainCam->GetScript<CPlayerCameraScript>();
	Script->CameraShake(1.0f, 10.0f, 100.f);
	Vec3 CurPos = Transform()->GetRelativePos();

	CGameObject* FloorCrack = new CGameObject;
	FloorCrack->SetName(L"FloorCrack");
	FloorCrack->AddComponent(new CTransform);
	FloorCrack->AddComponent(new CMeshRender);
	FloorCrack->AddComponent(new CAnimator2D);
	FloorCrack->AddComponent(new CBossLeapAttackScript);
	FloorCrack->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	FloorCrack->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"material\\Std2DLightMtrl.mtrl"));
	FloorCrack->Transform()->SetRelativePos(CurPos);
	FloorCrack->Transform()->SetRelativeScale(250.f, 250.f, 1.f);
	FloorCrack->Animator2D()->SetSamplerState(1);
	SpawnGameObject(FloorCrack, Vec3(CurPos.x, CurPos.y - 120.f , CurPos.z - 20.f), L"Default");

	CGameObject* CrackHitBox = new CGameObject;
	CrackHitBox->SetName(L"CrackHitBox");
	CrackHitBox->AddComponent(new CTransform);
	CrackHitBox->AddComponent(new CCollider2D);
	CrackHitBox->Transform()->SetRelativeScale(Vec3(150.f, 150.f, 1.f));
	CrackHitBox->Transform()->SetRelativePos(CurPos);
	CrackHitBox->Collider2D()->SetOffsetScale(Vec2(1.f, 1.f));
	CrackHitBox->Collider2D()->SetAbsolute(false);
	CrackHitBox->AddComponent(new CBossLeapAttackHitBoxScript);

	SpawnGameObject(CrackHitBox, Vec3(CurPos.x, CurPos.y - 120.f, CurPos.z - 20.f), L"MonsterProjectile");

	CCollisionMgr::GetInst()->LayerCheck(L"Monster", L"Wall");
	CCollisionMgr::GetInst()->LayerCheck(L"Monster", L"PitWall");

	Ptr<CSound> EarthCrumble = CResMgr::GetInst()->FindRes<CSound>(L"sound\\EarthCrumble.wav");
	EarthCrumble->Play(1, 0.2, true);
}

void CBossAttackScript::TowerOfTerraAttack()
{
	Animator2D()->Play(L"Boss_HeavyStomp", false);

	CGameObject* Terra = new CGameObject;
	Terra->SetName(L"Terra");
	Terra->AddComponent(new CTransform);
	Terra->AddComponent(new CTerraScript);
	CTerraScript* Script = Terra->GetScript<CTerraScript>();
	Script->SetBossPos(Transform()->GetRelativePos());
	Script->SetPlayerPos(CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"Player")->Transform()->GetRelativePos());
	SpawnGameObject(Terra, Transform()->GetRelativePos(), L"Default");
}

void CBossAttackScript::ShutLightAttack()
{
	Animator2D()->Play(L"Boss_Clap", false);
	CMainLightScript* Script = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"MainLight")->GetScript<CMainLightScript>();
	Script->SetToDark();
	Ptr<CSound> GaleBoomerang = CResMgr::GetInst()->FindRes<CSound>(L"sound\\GaleBoomerang.wav");
	GaleBoomerang->Play(1, 0.2, true);
}





