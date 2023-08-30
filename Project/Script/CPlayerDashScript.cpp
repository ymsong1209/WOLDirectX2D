#include "pch.h"
#include "CPlayerDashScript.h"
#include "CPlayerScript.h"
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>
#include <Engine/CCollisionMgr.h>

#include <Engine/CTimeMgr.h>

CPlayerDashScript::CPlayerDashScript()
	: CScript((UINT)SCRIPT_TYPE::PLAYERDASHSCRIPT)
	, m_fDashTime(0.f)
{
	SetActive(false);
}

CPlayerDashScript::CPlayerDashScript(const CPlayerDashScript& _other)
	: CScript((UINT)SCRIPT_TYPE::PLAYERDASHSCRIPT)
	, m_fDashTime(_other.m_fDashTime)
{
	SetActive(_other.m_bActive);
}


CPlayerDashScript::~CPlayerDashScript()
{
}


void CPlayerDashScript::begin()
{
}

void CPlayerDashScript::tick()
{
	if (!IsActive()) return;
	m_fDashTime += DT;
	if (m_fDashTime > 0.2f) {
		ChangeState((UINT)SCRIPT_TYPE::PLAYERDASHSTOPSCRIPT);
	}

}

void CPlayerDashScript::Enter()
{	
	//Player과 PitWall 충돌 해제
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
				if ((RowName == "Player" || ColName == "Player") && (RowName == "PitWall" || ColName == "PitWall")) {
					CollisionMatrix[iRow] -= (1 << iCol);
					CCollisionMgr::GetInst()->SetMatrix(CollisionMatrix);
				}
			}
		}
	}

	Ptr<CPrefab> DashPrefab = CResMgr::GetInst()->FindRes<CPrefab>(L"prefab\\DashEffect.prefab");
	CGameObject* DashEffect = DashPrefab->Instantiate();

	CPlayerScript* PlayerMainScript = GetOwner()->GetScript<CPlayerScript>();
	//상,하가 좌,우보다 우선임
	if (PlayerMainScript->GetPlayerDir() & DIR_RIGHT) {
		Animator2D()->Play(L"Player_Dash_Right", true);
		RigidBody()->AddVelocity(Vec2(800.f, 0.f));
		
	}
	if (PlayerMainScript->GetPlayerDir() & DIR_LEFT) {
		Animator2D()->Play(L"Player_Dash_Left", true);
		RigidBody()->AddVelocity(Vec2(-800.f, 0.f));
		DashEffect->Transform()->SetRelativeRot(Vec3(0.f, 0.f, XMConvertToRadians(180.f)));
	}
	if (PlayerMainScript->GetPlayerDir() & DIR_DOWN) {
		Animator2D()->Play(L"Player_Dash_Down",true);
		RigidBody()->AddVelocity(Vec2(0.f, -800.f));
		DashEffect->Transform()->SetRelativeRot(Vec3(0.f, 0.f, XMConvertToRadians(270.f)));
	}
	if (PlayerMainScript->GetPlayerDir() & DIR_UP) {
		Animator2D()->Play(L"Player_Dash_Up", true);
		RigidBody()->AddVelocity(Vec2(0.f, 800.f));
		DashEffect->Transform()->SetRelativeRot(Vec3(0.f, 0.f, XMConvertToRadians(90.f)));
	}
	PlayerMainScript->SetDashStartPos(Transform()->GetRelativePos());
	
	SpawnGameObject(DashEffect, Transform()->GetRelativePos(), L"Default");
	Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\StandardDash.wav");
	pSound->Play(1, 0.5f, true);
	
}

void CPlayerDashScript::Exit()
{
	
	m_fDashTime = 0.f;
}


