#include "pch.h"
#include "CGhoulHitBoxScript.h"
#include "CGhoulHitScript.h"
#include "CGhoulScript.h"
#include <Engine/CGameObject.h>

CGhoulHitBoxScript::CGhoulHitBoxScript()
	:CScript((UINT)SCRIPT_TYPE::GHOULHITBOXSCRIPT)
{
}

CGhoulHitBoxScript::~CGhoulHitBoxScript()
{
}


void CGhoulHitBoxScript::begin()
{
	CLayer* HitBoxLayer = CLevelMgr::GetInst()->GetCurLevel()->FindLayerByName(L"MonsterHitBox");
	GetOwner()->SetLayerIndex(HitBoxLayer->GetLayerIndex());
	Transform()->SetRelativeScale(Vec3(1.f, 1.f, 1.f));
	Transform()->SetRelativePos(Vec3(0.f, 0.f, 0.f));
}

void CGhoulHitBoxScript::tick()
{
	//CGameObject* hitbox = GetOwner();
	//CGameObject* Parent = GetOwner()->GetParent();
	//Vec3 PlayerPos = GetOwner()->GetParent()->Transform()->GetRelativePos();
	//Transform()->SetRelativePos(PlayerPos);
}

void CGhoulHitBoxScript::AddCollider()
{
	GetOwner()->AddComponent(new CCollider2D);
	Collider2D()->SetAbsolute(true);
	Collider2D()->SetOffsetPos(Vec2(0.f, -20.f));
	Collider2D()->SetOffsetScale(Vec2(60.f, 130.f));
	Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
}

void CGhoulHitBoxScript::BeginOverlap(CCollider2D* _Other)
{
	CGameObject* Ghoul = GetOwner()->GetParent();
	CGhoulScript* GhoulMainScript = Ghoul->GetScript<CGhoulScript>();

	if (GhoulMainScript->GetGhoulDeadState() == true) return;
	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
	if (Curlevel->GetLayer(_Other->GetOwner()->GetLayerIndex())->GetName() == L"PlayerProjectile") {
		CGameObject* Ghoul = GetOwner()->GetParent();
		if (Ghoul->IsDead()) return;
		CGhoulHitScript* GhoulHitScript = Ghoul->GetScript<CGhoulHitScript>();
		CGhoulScript* GhoulMainScript = Ghoul->GetScript<CGhoulScript>();

		if (!GhoulMainScript->IsFall()) {
			GhoulMainScript->ChangeState((UINT)SCRIPT_TYPE::GHOULHITSCRIPT, true);
		}

	}
}

void CGhoulHitBoxScript::OnOverlap(CCollider2D* _Other)
{

}

void CGhoulHitBoxScript::EndOverlap(CCollider2D* _Other)
{

}


