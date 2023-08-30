#include "pch.h"
#include "CSnowFlakeScript.h"
#include <Engine/CResMgr.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include "CPlayerAfterImageScript.h"

CSnowFlakeScript::CSnowFlakeScript()
	: CScript((UINT)SCRIPT_TYPE::SNOWFLAKESCRIPT)
	, m_fStartAngle(0.f)
	, m_fDegree(0.f)
	, m_fRotation(0.f)
	, m_vDirection(0.f,0.f,0.f)
	, m_fForce(50.f)
{
}

CSnowFlakeScript::~CSnowFlakeScript()
{
}

void CSnowFlakeScript::begin()
{
	Ptr<CTexture> SnowTex = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\particles\\Snowflake_Chakram.png");
	SetLifeSpan(5.f);
	MeshRender()->GetDynamicMaterial();
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, SnowTex);
	m_fDegree = m_fStartAngle / 180.f * XM_PI;
	/*Collider2D()->SetAbsolute(true);
	Collider2D()->SetOffsetScale(Vec2(100.f, 100.f));*/
	Collider2D()->SetAbsolute(false);
	Collider2D()->SetOffsetScale(Vec2(1.f, 1.f));
	Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\IceForm2.wav");
	pSound->Play(1, 0.15f, true);
}

void CSnowFlakeScript::tick()
{
	Vec3 CurScale = Transform()->GetRelativeScale();
	CurScale.x += DT * 100;
	CurScale.y += DT * 100;
	
	if (CurScale.x < 200.f) {
		Transform()->SetRelativeScale(CurScale.x, CurScale.y, 1.f);
	}

	CGameObject* player = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"Player");
	Vec3 PlayerPos = player->Transform()->GetRelativePos();
	m_fDegree += DT * 3;
	Transform()->SetRelativePos(Vec3(PlayerPos.x + 150 * cos(m_fDegree), PlayerPos.y + 150 * sin(m_fDegree), PlayerPos.z));
	m_fRotation += DT * 7;
	Transform()->SetRelativeRot(Vec3(0.f, 0.f, m_fRotation));


	Vec3 CurPos = Transform()->GetRelativePos();
	m_vDirection = Vec3(CurPos.x - PlayerPos.x, CurPos.y - PlayerPos.y, 1.f);
	m_vDirection = m_vDirection.Normalize();

	
	
}

void CSnowFlakeScript::BeginOverlap(CCollider2D* _Other)
{
	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
	if (Curlevel->GetLayer(_Other->GetOwner()->GetLayerIndex())->GetName() == L"Monster") {
		CGameObject* Monster = _Other->GetOwner();
		//몬스터 밀어내기
		Monster->RigidBody()->SetVelocity(Vec2(0.f, 0.f));
		float x = m_vDirection.x * m_fForce;
		float y = m_vDirection.y * m_fForce;
		Monster->RigidBody()->AddVelocity(Vec2(m_vDirection.x * m_fForce, m_vDirection.y * m_fForce));
	}
}

void CSnowFlakeScript::OnOverlap(CCollider2D* _Other)
{
}

void CSnowFlakeScript::EndOverlap(CCollider2D* _Other)
{
}

