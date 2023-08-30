#include "pch.h"
#include "CBossHitBoxScript.h"
#include "CBossScript.h"
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

CBossHitBoxScript::CBossHitBoxScript()
	:CScript((UINT)SCRIPT_TYPE::BOSSHITBOXSCRIPT)
{
}

CBossHitBoxScript::~CBossHitBoxScript()
{
}


void CBossHitBoxScript::begin()
{
	CLayer* HitBoxLayer = CLevelMgr::GetInst()->GetCurLevel()->FindLayerByName(L"MonsterHitBox");
	GetOwner()->SetLayerIndex(HitBoxLayer->GetLayerIndex());
	Transform()->SetRelativeScale(Vec3(1.f, 1.f, 1.f));
	Transform()->SetRelativePos(Vec3(0.f, 0.f, 0.f));
}

void CBossHitBoxScript::tick()
{

}

void CBossHitBoxScript::BeginOverlap(CCollider2D* _Other)
{
	CGameObject* Boss = GetOwner()->GetParent();
	CBossScript* BossMainScript = Boss->GetScript<CBossScript>();
	int hp = BossMainScript->GetBossHp();
	BossMainScript->SetBossHp(--hp);
	if (BossMainScript->GetBossDeadState() == true) return;
	if (BossMainScript->GetCanChangeToHit() == false) {
		return;
	}
	

	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
	if (Curlevel->GetLayer(_Other->GetOwner()->GetLayerIndex())->GetName() == L"PlayerProjectile") {
		CGameObject* Boss = GetOwner()->GetParent();
		if (Boss->IsDead()) return;
		
		BossMainScript->ChangeState((UINT)SCRIPT_TYPE::BOSSHITSCRIPT, true);
	}
}

