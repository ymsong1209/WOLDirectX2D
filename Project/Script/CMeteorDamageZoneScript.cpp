#include "pch.h"
#include "CMeteorDamageZoneScript.h"
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>


CMeteorDamageZoneScript::CMeteorDamageZoneScript()
	:CScript((UINT)SCRIPT_TYPE::METEORDAMAGEZONESCRIPT)
	, m_fForce(50.f)
{
}

CMeteorDamageZoneScript::~CMeteorDamageZoneScript()
{
}


void CMeteorDamageZoneScript::begin()
{
}

void CMeteorDamageZoneScript::tick()
{
}

void CMeteorDamageZoneScript::BeginOverlap(CCollider2D* _Other)
{
	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
	if (Curlevel->GetLayer(_Other->GetOwner()->GetLayerIndex())->GetName() == L"Monster") {
		CGameObject* Monster = _Other->GetOwner();
		//몬스터 밀어내기
		Monster->RigidBody()->SetVelocity(Vec2(0.f, 0.f));
		Vec3 MonsterPos = Monster->Transform()->GetRelativePos();
		Vec3 CenterPos = Transform()->GetRelativePos();
		Vec3 Direction = Vec3(MonsterPos.x - CenterPos.x, MonsterPos.y - CenterPos.y, 1.f);
		Direction = Direction.Normalize();
		float x = Direction.x * m_fForce;
		float y = Direction.y * m_fForce;
		Monster->RigidBody()->AddVelocity(Vec2(Direction.x * m_fForce, Direction.y * m_fForce));
	}
}

void CMeteorDamageZoneScript::OnOverlap(CCollider2D* _Other)
{
}

void CMeteorDamageZoneScript::EndOverlap(CCollider2D* _Other)
{
}

