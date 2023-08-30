#include "pch.h"
#include "CGhoulScript.h"
#include <Engine/CAnim2D.h>
#include <Engine/CAnimator2D.h>
#include <Engine/CResMgr.h>

CGhoulScript::CGhoulScript()
	:CScript((UINT)SCRIPT_TYPE::GHOULSCRIPT)
	, m_iHp(4)
	, m_bIsHit(false)
	, m_bFall(false)
	, m_bIsDeadState(false)
{
	AddScriptParam(SCRIPT_PARAM::INT, &m_iWaveNum, "WaveNum");
}

CGhoulScript::~CGhoulScript()
{
}

void CGhoulScript::begin()
{
	ChangeState((UINT)SCRIPT_TYPE::GHOULWAITSCRIPT);

}

void CGhoulScript::tick()
{
	if (m_iHp < 1 && m_bIsDeadState == false) {
		ChangeState((UINT)SCRIPT_TYPE::GHOULDEADSCRIPT, false);
	}
}


void CGhoulScript::BeginOverlap(CCollider2D* _Other)
{
	if (m_bIsDeadState == true) return;
	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
	//낙하중일때는 모든 collide 무시
	if (m_bFall == false &&
		((Curlevel->GetLayer(_Other->GetOwner()->GetLayerIndex())->GetName() == L"PitWall" && (m_bIsHit == false)) ||
			Curlevel->GetLayer(_Other->GetOwner()->GetLayerIndex())->GetName() == L"Wall")) {
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

	//낙하판정은 hitstate에서만
	if ((Curlevel->GetLayer(_Other->GetOwner()->GetLayerIndex())->GetName() == L"Pit" && m_bIsHit)) {
		ChangeState((UINT)SCRIPT_TYPE::GHOULFALLSCRIPT, false);
	}
}

void CGhoulScript::OnOverlap(CCollider2D* _Other)
{
	if (m_bIsDeadState == true) return;
	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
	if (m_bFall == false &&
		((Curlevel->GetLayer(_Other->GetOwner()->GetLayerIndex())->GetName() == L"PitWall" && !m_bIsHit) ||
			Curlevel->GetLayer(_Other->GetOwner()->GetLayerIndex())->GetName() == L"Wall")) {
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

	//낙하판정은 hitstate에서만
	if ((Curlevel->GetLayer(_Other->GetOwner()->GetLayerIndex())->GetName() == L"Pit" && m_bIsHit)) {
		ChangeState((UINT)SCRIPT_TYPE::GHOULFALLSCRIPT, false);
	}
}

void CGhoulScript::EndOverlap(CCollider2D* _Other)
{
}

void CGhoulScript::SaveToLevelFile(FILE* _File)
{
	fwrite(&m_iWaveNum, sizeof(int), 1, _File);
}

void CGhoulScript::LoadFromLevelFile(FILE* _File)
{
	fread(&m_iWaveNum, sizeof(int), 1, _File);
}