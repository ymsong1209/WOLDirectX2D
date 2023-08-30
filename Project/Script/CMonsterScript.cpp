#include "pch.h"
#include "CMonsterScript.h"
#include <Engine/CResMgr.h>
#include <Engine/CTexture.h>
#include <Engine/CAstarMgr.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

CMonsterScript::CMonsterScript()
	: CScript((UINT)SCRIPT_TYPE::MONSTERSCRIPT)
	, m_bTrace(false)
{
}

CMonsterScript::~CMonsterScript()
{
}

void CMonsterScript::begin()
{
	MeshRender()->GetDynamicMaterial();
	CLevel* CurLevel = CLevelMgr::GetInst()->GetCurLevel();
	m_pPlayer = CurLevel->FindParentObjectByName(L"Player");
}

void CMonsterScript::tick()
{
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\Character.png"));

	if (KEY_TAP(KEY::N)) {
		m_bTrace = !m_bTrace;
	}

	if (m_bTrace) {
		m_fTime += DT;
		Vec3 CurPos = Transform()->GetRelativePos();
		Vec3 FindPos = m_pPlayer->Transform()->GetRelativePos();
		if (m_fTime > 0.1f) {
			Vec2 pos = CAstarMgr::GetInst()->SetFind(CurPos, FindPos);

			if (pos == Vec2(0.f, 0.f)) return;
			else {
				
				Transform()->SetRelativePos(Vec3(pos.x, pos.y, CurPos.z));
			}
			m_fTime = 0.f;
		}
		
	}
}

void CMonsterScript::BeginOverlap(CCollider2D* _Other)
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

void CMonsterScript::OnOverlap(CCollider2D* _Other)
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

void CMonsterScript::EndOverlap(CCollider2D* _Other)
{
}
