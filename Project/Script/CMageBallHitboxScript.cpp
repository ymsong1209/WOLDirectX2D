#include "pch.h"
#include "CMageBallHitboxScript.h"
#include "CMageBallScript.h"

CMageBallHitboxScript::CMageBallHitboxScript()
	:CScript((UINT)SCRIPT_TYPE::MAGEBALLHITBOXSCRIPT)
{
}

CMageBallHitboxScript::~CMageBallHitboxScript()
{
}


void CMageBallHitboxScript::begin()
{
	CLayer* HitBoxLayer = CLevelMgr::GetInst()->GetCurLevel()->FindLayerByName(L"MonsterHitBox");
	Transform()->SetRelativePos(Vec3(0.f, 0.f, 0.f));
	GetOwner()->SetLayerIndex(HitBoxLayer->GetLayerIndex());
	
}

void CMageBallHitboxScript::tick()
{
	
}

void CMageBallHitboxScript::AddCollider()
{
	GetOwner()->AddComponent(new CCollider2D);
	Collider2D()->SetAbsolute(true);
	CGameObject* Ball = GetOwner()->GetParent();
	Vec3 BallScale = Ball->Transform()->GetRelativeScale();
	Collider2D()->SetOffsetScale(Vec2(BallScale.x, BallScale.y));
	Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::CIRCLE);
}

void CMageBallHitboxScript::BeginOverlap(CCollider2D* _Other)
{
	CGameObject* Ball = GetOwner()->GetParent();
	CMageBallScript* BallMainScript = Ball->GetScript<CMageBallScript>();

	if (BallMainScript->IsDeadState() == true) return;
	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
	if (Curlevel->GetLayer(_Other->GetOwner()->GetLayerIndex())->GetName() == L"PlayerProjectile" ||
		Curlevel->GetLayer(_Other->GetOwner()->GetLayerIndex())->GetName() == L"Wall") {
		BallMainScript->SetDeadState(true);
		BallMainScript->ChangeState((UINT)SCRIPT_TYPE::MAGEBALLDEADSCRIPT, false);
	}
	
	
}

void CMageBallHitboxScript::OnOverlap(CCollider2D* _Other)
{
	CGameObject* Ball = GetOwner()->GetParent();
	CMageBallScript* BallMainScript = Ball->GetScript<CMageBallScript>();

	if (BallMainScript->IsDeadState() == true) return;
	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
	if (Curlevel->GetLayer(_Other->GetOwner()->GetLayerIndex())->GetName() == L"PlayerProjectile" ||
		Curlevel->GetLayer(_Other->GetOwner()->GetLayerIndex())->GetName() == L"Wall") {
		BallMainScript->SetDeadState(true);
		BallMainScript->ChangeState((UINT)SCRIPT_TYPE::MAGEBALLDEADSCRIPT, false);
	}
}

void CMageBallHitboxScript::EndOverlap(CCollider2D* _Other)
{
}

