#include "pch.h"
#include "CWaterBombScript.h"
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim2D.h>
#include <Engine/CCollider2D.h>


CWaterBombScript::CWaterBombScript()
	:CScript((UINT)SCRIPT_TYPE::WATERBOMBSCRIPT)
	, m_fShootSpeed(0.f)
	, m_fForce(50.f)
	, m_fScale(1.f)
	, m_bReady(false)
{
}

CWaterBombScript::~CWaterBombScript()
{
}

void CWaterBombScript::begin()
{
	Animator2D()->LoadAnim(L"animation\\particle\\WaterBall.anim");
	Animator2D()->Play(L"WaterBall", true);
}

void CWaterBombScript::tick()
{
	m_fScale += DT * 60;
	m_fShootSpeed += DT * 1400;
	if (m_fScale > 80.f) m_fScale = 80.f;
	if (m_fShootSpeed > 1500.f) m_fShootSpeed = 1500.f;
	Transform()->SetRelativeScale(Vec3(m_fScale, m_fScale, 1.f));

	if (m_bReady) {
		Vec2 vel = RigidBody()->GetVelocity();
		if (vel.x == 0.f || vel.y == 0.f) {
			DestroyObject(GetOwner());
		}
	}
}

void CWaterBombScript::BeginOverlap(CCollider2D* _Other)
{
	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();

	if (Curlevel->GetLayer(_Other->GetOwner()->GetLayerIndex())->GetName() == L"Wall") {
		DestroyObject(GetOwner());
	}
	if (Curlevel->GetLayer(_Other->GetOwner()->GetLayerIndex())->GetName() == L"MonsterHitBox") {
		CGameObject* Monster = _Other->GetOwner()->GetParent();
		//몬스터 밀어내기
		Monster->RigidBody()->SetVelocity(Vec2(0.f, 0.f));
		Monster->RigidBody()->AddVelocity(Vec2(m_vDirection.x * m_fForce, m_vDirection.y * m_fForce));
	}
}

void CWaterBombScript::OnOverlap(CCollider2D* _Other)
{
}

void CWaterBombScript::EndOverlap(CCollider2D* _Other)
{
}

void CWaterBombScript::ShootBomb(Vec3 _Direction)
{
	m_fScale = 80.f;
	m_vDirection = _Direction;
	GetOwner()->AddComponent(new CCollider2D);
	Collider2D()->SetAbsolute(false);
	Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::CIRCLE);
	Collider2D()->SetOffsetScale(Vec2(1.f, 1.f));

	GetOwner()->AddComponent(new CRigidBody);
	RigidBody()->AddVelocity(Vec2(_Direction.Normalize().x * m_fShootSpeed, _Direction.Normalize().y * m_fShootSpeed));

	m_bReady = true;
}



