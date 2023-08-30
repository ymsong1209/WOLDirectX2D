#include "pch.h"
#include "CPlayerSlideScript.h"
#include "CPlayerScript.h"
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim2D.h>
#include <Engine/CCollisionMgr.h>

CPlayerSlideScript::CPlayerSlideScript()
	: CScript((UINT)SCRIPT_TYPE::PLAYERSLIDESCRIPT)
{
	SetActive(false);
}

CPlayerSlideScript::~CPlayerSlideScript()
{
}


void CPlayerSlideScript::begin()
{
}

void CPlayerSlideScript::tick()
{
	if (!IsActive()) return;
	CPlayerScript* PlayerMainScript = GetOwner()->GetScript<CPlayerScript>();
	int playerdir = PlayerMainScript->GetPlayerDir();
	if (Animator2D()->GetCurAnim()->IsFinish()) {
		
		if (playerdir & DIR_UP) {
			PlayerMainScript->SetPlayerDir(DIR_UP);
			ChangeState((UINT)SCRIPT_TYPE::PLAYERIDLESCRIPT);
		}
		else if (playerdir & DIR_DOWN) {
			PlayerMainScript->SetPlayerDir(DIR_DOWN);
			ChangeState((UINT)SCRIPT_TYPE::PLAYERIDLESCRIPT);
		}
		//여기까지 오면 일단 up,down은 안누르고 있음
		else if (playerdir & DIR_RIGHT) {
			PlayerMainScript->SetPlayerDir(DIR_RIGHT);
			ChangeState((UINT)SCRIPT_TYPE::PLAYERIDLESCRIPT);
		}
		else if (playerdir & DIR_LEFT) {
			PlayerMainScript->SetPlayerDir(DIR_LEFT);
			ChangeState((UINT)SCRIPT_TYPE::PLAYERIDLESCRIPT);
		}
	}
}

void CPlayerSlideScript::Enter()
{
	CPlayerScript* PlayerMainScript = GetOwner()->GetScript<CPlayerScript>();
	RigidBody()->SetVelocity(Vec2(0.f, 0.f));
	//상,하가 좌,우보다 우선시
	int playerdir = PlayerMainScript->GetPlayerDir();
	if (playerdir & DIR_UP) {
		Animator2D()->Play(L"Player_Slide_Up", false);
	}
	else if (playerdir & DIR_DOWN) {
		Animator2D()->Play(L"Player_Slide_Down", false);
	}
	else if (playerdir & DIR_RIGHT) {
		Animator2D()->Play(L"Player_Slide_Right", false);
	}
	else if (playerdir & DIR_LEFT) {
		Animator2D()->Play(L"Player_Slide_Left", false);
	}
	else {
		assert(nullptr);
	}

	//Dash->Slide로 올시 Player,Pitwall충돌 꺼져 있음
	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
	UINT CollisionMatrix[MAX_LAYER];
	for (UINT i = 0; i < MAX_LAYER; ++i) {
		CollisionMatrix[i] = CCollisionMgr::GetInst()->GetMatrix()[i];
	}

	bool Player_Pitwall = false;
	for (UINT iRow = 0; iRow < MAX_LAYER; ++iRow)
	{
		for (UINT iCol = iRow; iCol < MAX_LAYER; ++iCol)
		{
			if (CollisionMatrix[iRow] & (1 << iCol)) {
				CLayer* Rowlayer = Curlevel->GetLayer(iRow);
				string RowName = string(Rowlayer->GetName().begin(), Rowlayer->GetName().end());
				CLayer* Collayer = Curlevel->GetLayer(iCol);
				string ColName = string(Collayer->GetName().begin(), Collayer->GetName().end());
				if ((RowName == "Player" || ColName == "Player") && (RowName == "PitWall" || ColName == "PitWall")) {
					Player_Pitwall = true;
				}
			}
		}
	}
	if (!Player_Pitwall) {
		CCollisionMgr::GetInst()->LayerCheck(L"Player", L"PitWall");
	}
	
}

void CPlayerSlideScript::Exit()
{
	Animator2D()->GetCurAnim()->Reset();
}

