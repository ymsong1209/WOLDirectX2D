#include "pch.h"
#include "CSwordManHitBoxScript.h"
#include "CSwordManHitScript.h"
#include "CSwordManScript.h"
#include <Engine/CGameObject.h>

CSwordManHitBoxScript::CSwordManHitBoxScript()
	:CScript((UINT)SCRIPT_TYPE::SWORDMANHITBOXSCRIPT)
{
}

CSwordManHitBoxScript::~CSwordManHitBoxScript()
{
}


void CSwordManHitBoxScript::begin()
{
	CLayer* HitBoxLayer = CLevelMgr::GetInst()->GetCurLevel()->FindLayerByName(L"MonsterHitBox");
	GetOwner()->SetLayerIndex(HitBoxLayer->GetLayerIndex());
	Transform()->SetRelativeScale(Vec3(1.f, 1.f, 1.f));
	Transform()->SetRelativePos(Vec3(0.f, 0.f, 0.f));
}

void CSwordManHitBoxScript::tick()
{
	//CGameObject* hitbox = GetOwner();
	//CGameObject* Parent = GetOwner()->GetParent();
	//Vec3 PlayerPos = GetOwner()->GetParent()->Transform()->GetRelativePos();
	//Transform()->SetRelativePos(PlayerPos);
}

void CSwordManHitBoxScript::AddCollider()
{
	GetOwner()->AddComponent(new CCollider2D);
	Collider2D()->SetAbsolute(true);
	Collider2D()->SetOffsetScale(Vec2(80.f, 150.f));
	Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
}

void CSwordManHitBoxScript::BeginOverlap(CCollider2D* _Other)
{
	CGameObject* SwordMan = GetOwner()->GetParent();
	CSwordManScript* SwordManMainScript = SwordMan->GetScript<CSwordManScript>();

	if (SwordManMainScript->GetSwordManDeadState() == true) return;
	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
	if (Curlevel->GetLayer(_Other->GetOwner()->GetLayerIndex())->GetName() == L"PlayerProjectile") {
		CGameObject* SwordMan = GetOwner()->GetParent();
		if (SwordMan->IsDead()) return;
		CSwordManHitScript* SwordManHitScript = SwordMan->GetScript<CSwordManHitScript>();
		CSwordManScript* SwordManMainScript = SwordMan->GetScript<CSwordManScript>();

		if (!SwordManMainScript->IsFall()) {
			SwordManMainScript->ChangeState((UINT)SCRIPT_TYPE::SWORDMANHITSCRIPT, true);
		}
		
	}
}

void CSwordManHitBoxScript::OnOverlap(CCollider2D* _Other)
{

}

void CSwordManHitBoxScript::EndOverlap(CCollider2D* _Other)
{

}



