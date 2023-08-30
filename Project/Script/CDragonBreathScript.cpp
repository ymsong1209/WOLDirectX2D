#include "pch.h"
#include "CDragonBreathScript.h"
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
CDragonBreathScript::CDragonBreathScript()
	: CScript((UINT)SCRIPT_TYPE::DRAGONBREATHSCRIPT)
	, m_vPrevPos(0.f,0.f,0.f)
	, m_fLife(0.f)
	, m_fOffset(0.f)
	, m_fWaitTime(0.f)
	, m_fForce(50.f)
	, m_bSoundPlayed(false)
{
}

CDragonBreathScript::~CDragonBreathScript()
{
}
void CDragonBreathScript::begin()
{
	Ptr<CTexture> Dragon = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\particles\\DragonArc.png");
	SetLifeSpan(5.f + m_fWaitTime);
	MeshRender()->GetDynamicMaterial();
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, Dragon);
	
	m_fDegree = m_fInputAngle / 180.f * XM_PI;
	m_vDirection = Vec3(cos(m_fDegree), sin(m_fDegree), 1.f);
}

void CDragonBreathScript::tick()
{
	m_fWaitTime -= DT;
	if (m_fWaitTime > 0) {
		Transform()->SetRelativeScale(Vec3(1.0f, 1.0f, 1.0f));
		return;
	}
	else {
		if (!m_bSoundPlayed) {
			Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\FireballCast.wav");
			pSound->Play(1, 0.15f, true);
			m_bSoundPlayed = true;
		}
		Transform()->SetRelativeScale(Vec3(100.0f, 100.0f, 1.0f));
		Collider2D()->SetAbsolute(true);
		Collider2D()->SetOffsetScale(Vec2(100.f, 50.f));
	}
	
	Vec3 CurPos = Transform()->GetRelativePos();
	float tmpy = CurPos.y - m_vPrevPos.y;
	float tmpx = CurPos.x - m_vPrevPos.x;
	float slope = (CurPos.y - m_vPrevPos.y) / (CurPos.x - m_vPrevPos.x);
	float angle = atan(slope);
	//2사분면
	if (90.f < m_fInputAngle && m_fInputAngle < 270.f) {
		angle += XM_PI;
		
	}
	
	m_fLife += DT * 600;
	float ChangedX = cos(m_fDegree) * m_fLife - sin(m_fDegree) * 70 * sin((m_fLife) / 70.f);
	float ChangedY = sin(m_fDegree) * m_fLife + cos(m_fDegree) * 70 * sin((m_fLife) / 70.f);

	m_vPrevPos.x = Transform()->GetRelativePos().x;
	m_vPrevPos.y = Transform()->GetRelativePos().y;
	Transform()->SetRelativePos(Vec3(m_vStartPos.x + ChangedX, m_vStartPos.y + ChangedY, CurPos.z));
	Transform()->SetRelativeRot(Vec3(0.f, 0.f, angle));
	

}

void CDragonBreathScript::BeginOverlap(CCollider2D* _Other)
{
	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();

	if (Curlevel->GetLayer(_Other->GetOwner()->GetLayerIndex())->GetName() == L"Wall") {
		DestroyObject(GetOwner());
		Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\FireballExplode.wav");
		pSound->Play(1, 0.2f, true);
	}
	if (Curlevel->GetLayer(_Other->GetOwner()->GetLayerIndex())->GetName() == L"MonsterHitBox") {
		CGameObject* Monster = _Other->GetOwner()->GetParent();
		//몬스터 밀어내기
		Monster->RigidBody()->SetVelocity(Vec2(0.f, 0.f));
		float x = m_vDirection.x * m_fForce;
		float y = m_vDirection.y * m_fForce;
		Monster->RigidBody()->AddVelocity(Vec2(m_vDirection.x * m_fForce, m_vDirection.y * m_fForce));
		Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\EnemyFireballImpact.wav");
		pSound->Play(1, 0.2f, true);
	}
	
}

void CDragonBreathScript::OnOverlap(CCollider2D* _Other)
{
}

void CDragonBreathScript::EndOverlap(CCollider2D* _Other)
{
}


