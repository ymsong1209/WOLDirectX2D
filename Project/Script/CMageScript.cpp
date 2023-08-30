#include "pch.h"
#include "CMageScript.h"
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim2D.h>

CMageScript::CMageScript()
	:CScript((UINT)SCRIPT_TYPE::MAGESCRIPT)
	,m_iHp(3)
	,m_iDir(0)
	,m_bIsDeadState(false)
	,m_bFall(false)
	,m_bIsHit(false)
{
	AddScriptParam(SCRIPT_PARAM::INT, &m_iWaveNum, "WaveNum");
}

CMageScript::CMageScript(const CMageScript& _other)
	:CScript((UINT)SCRIPT_TYPE::MAGESCRIPT)
{
}

CMageScript::~CMageScript()
{
}


void CMageScript::begin()
{
	SetMageDir(DIR_LEFT);
	ChangeState((UINT)SCRIPT_TYPE::MAGEWAITSCRIPT, false);
}

void CMageScript::tick()
{
	if (m_iHp < 1 && m_bIsDeadState == false) {
		ChangeState((UINT)SCRIPT_TYPE::MAGEDEADSCRIPT, false);
	}
}

void CMageScript::BeginOverlap(CCollider2D* _Other)
{
	if (m_bIsDeadState == true) return;
	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
	//�������϶��� ��� collide ����
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

		// wall�� �����ʿ� �ִ� ���
		if (ColliderPos.x < WallColliderPos.x) {
			x = WallColliderPos.x - WallColliderScale.x / 2.0f - ColliderScale.x;
			xratio = (WallColliderPos.x - ColliderPos.x) / (WallColliderScale.x / 2.0f + ColliderScale.x / 2.0f);
		}
		//wall�� ���ʿ� �ִ� ���
		else {
			x = WallColliderPos.x + WallColliderScale.x / 2.0f + ColliderScale.x;
			xratio = (ColliderPos.x - WallColliderPos.x) / (WallColliderScale.x / 2.0f + ColliderScale.x / 2.0f);
		}

		//wall�� ���ʿ� �ִ� ���
		if (ColliderPos.y < WallColliderPos.y) {
			y = WallColliderPos.y - WallColliderScale.y / 2.0f - ColliderScale.y;
			yratio = (WallColliderPos.y - ColliderPos.y) / (WallColliderScale.y / 2.0f + ColliderScale.y / 2.0f);
		}
		//wall�� �Ʒ��ʿ� �ִ� ���
		else {
			y = WallColliderPos.y + WallColliderScale.y / 2.0f + ColliderScale.y;
			yratio = (ColliderPos.y - WallColliderPos.y) / (WallColliderScale.y / 2.0f + ColliderScale.y / 2.0f);
		}
		//x�� �� ũ�� -> �����̳� ���������� �и��
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

	//���������� hitstate������
	if ((Curlevel->GetLayer(_Other->GetOwner()->GetLayerIndex())->GetName() == L"Pit" && m_bIsHit)) {
		ChangeState((UINT)SCRIPT_TYPE::SWORDMANFALLSCRIPT, false);
	}
}

void CMageScript::OnOverlap(CCollider2D* _Other)
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

		// wall�� �����ʿ� �ִ� ���
		if (ColliderPos.x < WallColliderPos.x) {
			x = WallColliderPos.x - WallColliderScale.x / 2.0f - ColliderScale.x;
			xratio = (WallColliderPos.x - ColliderPos.x) / (WallColliderScale.x / 2.0f + ColliderScale.x / 2.0f);
		}
		//wall�� ���ʿ� �ִ� ���
		else {
			x = WallColliderPos.x + WallColliderScale.x / 2.0f + ColliderScale.x;
			xratio = (ColliderPos.x - WallColliderPos.x) / (WallColliderScale.x / 2.0f + ColliderScale.x / 2.0f);
		}

		//wall�� ���ʿ� �ִ� ���
		if (ColliderPos.y < WallColliderPos.y) {
			y = WallColliderPos.y - WallColliderScale.y / 2.0f - ColliderScale.y;
			yratio = (WallColliderPos.y - ColliderPos.y) / (WallColliderScale.y / 2.0f + ColliderScale.y / 2.0f);
		}
		//wall�� �Ʒ��ʿ� �ִ� ���
		else {
			y = WallColliderPos.y + WallColliderScale.y / 2.0f + ColliderScale.y;
			yratio = (ColliderPos.y - WallColliderPos.y) / (WallColliderScale.y / 2.0f + ColliderScale.y / 2.0f);
		}
		//x�� �� ũ�� -> �����̳� ���������� �и��
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

void CMageScript::EndOverlap(CCollider2D* _Other)
{
}

void CMageScript::SaveToLevelFile(FILE* _File)
{
	fwrite(&m_iWaveNum, sizeof(int), 1, _File);
}

void CMageScript::LoadFromLevelFile(FILE* _File)
{
	fread(&m_iWaveNum, sizeof(int), 1, _File);
	
}

