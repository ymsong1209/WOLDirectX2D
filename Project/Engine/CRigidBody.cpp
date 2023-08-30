#include "pch.h"
#include "CRigidBody.h"
#include "CTimeMgr.h"
#include "CTransform.h"

CRigidBody::CRigidBody()
	: CComponent(COMPONENT_TYPE::RIGIDBODY)
	, m_vForce{}
	, m_vVelocity{}
	, m_fMass(1.f)
	, m_fFriction(100.f)
	, m_fFrictionScale(1.f)
	, m_fVelocityLimit(10000.f)
	, m_fGravityLimit(10000.f)
	, m_fGravityAccel(0.f)
	, m_bGravityUse(false)
	, m_bGround(false)
{

}
CRigidBody::CRigidBody(const CRigidBody& _other)
	: CComponent(_other)
	, m_vForce(_other.m_vForce)
	, m_vVelocity(_other.m_vVelocity)
	, m_fMass(_other.m_fMass)
	, m_fFriction(_other.m_fFriction)
	, m_fFrictionScale(_other.m_fFrictionScale)
	, m_fVelocityLimit(_other.m_fVelocityLimit)
	, m_fGravityLimit(_other.m_fGravityLimit)
	, m_fGravityAccel(_other.m_fGravityAccel)
	, m_bGravityUse(_other.m_bGravityUse)
	, m_bGround(false)
{
}

CRigidBody::~CRigidBody()
{
}


void CRigidBody::tick()
{
}

void CRigidBody::finaltick()
{
	// F = M x A
	// ���ӵ� ���ϱ�(A)
	Vec2 vAccel = m_vForce / m_fMass;

	// ���ӵ��� �̿��ؼ� �ӵ��� ������Ŵ
	m_vVelocity += Vec2(vAccel.x * DT, vAccel.y * DT);

	// �߷��� ����ϴ� ����, ���� �־�� ������ ����
	// �߷��� ���� ������ ������ �ٷ� ����
	if (m_bGravityUse && m_bGround || !m_bGravityUse) {

		// ���� ���ӵ�
		Vec2 vFriction = -m_vVelocity;
		if (!(vFriction.x == 0.f && vFriction.y == 0.f))
		{
			
			vFriction.Normalize();
			vFriction *= (m_fFriction * m_fFrictionScale * m_fMass * DT);
		}


		// �ӵ� ���ҷ�(�����¿� ����) �� ���� �ӵ��� �Ѿ� �� ���, ���� ���η� �����.
		if (m_vVelocity.Length() < vFriction.Length())
		{
			m_vVelocity = Vec2(0.f, 0.f);
		}
		else {
			// ���� �ӵ� �ݴ�������� ������ ���� �ӵ� ����
			m_vVelocity += vFriction;
		}
	}

	// �߷� ���� + ���� ���� ==> �߷�
	if (m_bGravityUse && !m_bGround)
	{
		Vec2 vGravityAccel = Vec2(0.f, m_fGravityAccel);
		m_vVelocity += Vec2(vGravityAccel.x * DT, vGravityAccel.y * DT);
	}

	// �ӵ� ���� ����(��, ��)
	// �߷��� ����ϴ� ���, �¿� �̵��� �߷¹���(�Ʒ�) �� �ӵ������� ���� �����Ѵ�.
	if (m_bGravityUse)
	{
		if (m_fVelocityLimit < fabsf(m_vVelocity.x))
		{
			m_vVelocity.x = (m_vVelocity.x / fabsf(m_vVelocity.x)) * m_fVelocityLimit;
		}

		if (m_fGravityLimit < fabsf(m_vVelocity.y))
		{
			m_vVelocity.y = (m_vVelocity.y / fabsf(m_vVelocity.y)) * m_fGravityLimit;
		}
	}

	// �߷��� ������� ������, ��� �������ε� �ӵ� ������ �Ǵ�.
	else
	{
		if (m_fVelocityLimit < m_vVelocity.Length())
		{
			// ���� �ӵ��� �Ѱ��� ���
			m_vVelocity.Normalize();
			m_vVelocity *= m_fVelocityLimit;
		}
	}


	// ������Ʈ�� ��ġ
	
	Vec3 vPos = Transform()->GetRelativePos();

	// �ӵ�(�ӷ� + ����) �� �°� ��ü�� �̵���Ŵ
	vPos.x += m_vVelocity.x * DT;
	vPos.y += m_vVelocity.y * DT;

	Transform()->SetRelativePos(vPos);

	m_vForce = Vec2(0.f, 0.f);
}

void CRigidBody::SetGround(bool _bGround)
{
	m_bGround = _bGround;

	if (m_bGround)
	{
		m_vVelocity.y = 0.f;
	}
}


void CRigidBody::SaveToLevelFile(FILE* _File)
{
	fwrite(&m_vForce, sizeof(Vec2), 1, _File);
	fwrite(&m_vVelocity, sizeof(Vec2), 1, _File);
	fwrite(&m_fMass, sizeof(float), 1, _File);

	fwrite(&m_fFriction, sizeof(float), 1, _File);
	fwrite(&m_fFrictionScale, sizeof(float), 1, _File);

	fwrite(&m_fVelocityLimit, sizeof(float), 1, _File);
	fwrite(&m_fGravityLimit, sizeof(float), 1, _File);

	fwrite(&m_fGravityAccel, sizeof(float), 1, _File);
	fwrite(&m_bGravityUse, sizeof(bool), 1, _File);
	fwrite(&m_bGround, sizeof(bool), 1, _File);
}

void CRigidBody::LoadFromLevelFile(FILE* _File)
{
	fread(&m_vForce, sizeof(Vec2), 1, _File);
	fread(&m_vVelocity, sizeof(Vec2), 1, _File);
	fread(&m_fMass, sizeof(float), 1, _File);

	fread(&m_fFriction, sizeof(float), 1, _File);
	fread(&m_fFrictionScale, sizeof(float), 1, _File);

	fread(&m_fVelocityLimit, sizeof(float), 1, _File);
	fread(&m_fGravityLimit, sizeof(float), 1, _File);

	fread(&m_fGravityAccel, sizeof(float), 1, _File);
	fread(&m_bGravityUse, sizeof(bool), 1, _File);
	fread(&m_bGround, sizeof(bool), 1, _File);
	
}