#include "pch.h"
#include "CForeHandAttackScript.h"
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim2D.h>

CForeHandAttackScript::CForeHandAttackScript()
	: CScript((UINT)SCRIPT_TYPE::FOREHANDATTACKSCRIPT)
	, m_fForce(50.f)
{
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fInputangle, "InputAngle");
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fForce, "Force");
}


CForeHandAttackScript::~CForeHandAttackScript()
{
}

void CForeHandAttackScript::begin()
{
	Animator2D()->LoadAnim(L"animation\\particle\\normalbackhand.anim");
	Animator2D()->Play(L"normalbackhand", false);
	float degree = m_fInputangle / 180.f * XM_PI;
	m_vDirection = Vec3(cos(degree), sin(degree), 1.f);
	Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\WindSlashBasic.wav");
	pSound->Play(1, 0.15f, true);
}

void CForeHandAttackScript::tick()
{
	if (Animator2D()->GetCurAnim()->IsFinish()) {
		Animator2D()->GetCurAnim()->Reset();
		DestroyObject(GetOwner());
	}
}

void CForeHandAttackScript::BeginOverlap(CCollider2D* _Other)
{
	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
	if (Curlevel->GetLayer(_Other->GetOwner()->GetLayerIndex())->GetName() == L"MonsterHitBox") {
		CGameObject* Monster = _Other->GetOwner()->GetParent();
		//몬스터 밀어내기
		//Monster->RigidBody()->SetVelocity(Vec2(0.f, 0.f));
		float x = m_vDirection.x * m_fForce;
		float y = m_vDirection.y * m_fForce;
		Monster->RigidBody()->AddVelocity(Vec2(m_vDirection.x * m_fForce, m_vDirection.y * m_fForce));
	}
}

void CForeHandAttackScript::OnOverlap(CCollider2D* _Other)
{
}

void CForeHandAttackScript::EndOverlap(CCollider2D* _Other)
{
}