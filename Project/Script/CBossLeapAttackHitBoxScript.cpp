#include "pch.h"
#include "CBossLeapAttackHitBoxScript.h"
#include "CPlayerScript.h"
#include "CPlayerHitScript.h"

CBossLeapAttackHitBoxScript::CBossLeapAttackHitBoxScript()
	:CScript((UINT)SCRIPT_TYPE::BOSSLEAPATTACKHITBOXSCRIPT)
{
}

CBossLeapAttackHitBoxScript::~CBossLeapAttackHitBoxScript()
{
}


void CBossLeapAttackHitBoxScript::begin()
{
}

void CBossLeapAttackHitBoxScript::tick()
{
	if (GetOwner()->IsDead()) return;
	m_fTime += DT;
	if (m_fTime > 0.3f) {
		DestroyObject(GetOwner());
	}
}

void CBossLeapAttackHitBoxScript::BeginOverlap(CCollider2D* _Other)
{
	if (_Other->GetOwner()->GetName() == L"PlayerHitBox") {
		CGameObject* Player = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"Player");
		CPlayerHitScript* Script = Player->GetScript<CPlayerHitScript>();
		CPlayerScript* PlayerMainScript = Player->GetScript<CPlayerScript>();
		if (PlayerMainScript->IsPlayerDeadState() == false) {
			PlayerMainScript->ChangeState((UINT)SCRIPT_TYPE::PLAYERHITSCRIPT, false);
			Script->SetDirection(Vec3(0.f, -1.f, 0.f));
		}
		
	}
}

