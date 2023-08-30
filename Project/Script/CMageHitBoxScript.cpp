#include "pch.h"
#include "CMageHitBoxScript.h"
#include "CMageHitScript.h"
#include "CMageScript.h"
#include <Engine/CGameObject.h>

CMageHitBoxScript::CMageHitBoxScript()
	:CScript((UINT)SCRIPT_TYPE::MAGEHITBOXSCRIPT)
{
}

CMageHitBoxScript::~CMageHitBoxScript()
{
}

void CMageHitBoxScript::begin()
{
	CLayer* HitBoxLayer = CLevelMgr::GetInst()->GetCurLevel()->FindLayerByName(L"MonsterHitBox");
	GetOwner()->SetLayerIndex(HitBoxLayer->GetLayerIndex());
	Transform()->SetRelativeScale(Vec3(1.f, 1.f, 1.f));
	Transform()->SetRelativePos(Vec3(0.f, 0.f, 0.f));
}

void CMageHitBoxScript::tick()
{
}

void CMageHitBoxScript::AddCollider()
{
	GetOwner()->AddComponent(new CCollider2D);
	Collider2D()->SetAbsolute(true);
	Collider2D()->SetOffsetScale(Vec2(80.f, 150.f));
	Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
}

void CMageHitBoxScript::BeginOverlap(CCollider2D* _Other)
{
	CGameObject* Mage = GetOwner()->GetParent();
	CMageScript* MageMainScript = Mage->GetScript<CMageScript>();

	if (MageMainScript->GetMageDeadState() == true) return;
	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
	if (Curlevel->GetLayer(_Other->GetOwner()->GetLayerIndex())->GetName() == L"PlayerProjectile") {
		CGameObject* SwordMan = GetOwner()->GetParent();
		if (SwordMan->IsDead()) return;

		if (!MageMainScript->IsFall()) {
			MageMainScript->ChangeState((UINT)SCRIPT_TYPE::MAGEHITSCRIPT, true);
		}

	}
}

void CMageHitBoxScript::OnOverlap(CCollider2D* _Other)
{
}

void CMageHitBoxScript::EndOverlap(CCollider2D* _Other)
{
}


