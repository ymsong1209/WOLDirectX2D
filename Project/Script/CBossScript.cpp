#include "pch.h"
#include "CBossScript.h"
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim2D.h>
#include "CBossFlexScript.h"
#include "CBossAttackScript.h"

CBossScript::CBossScript()
	:CScript((UINT)SCRIPT_TYPE::BOSSSCRIPT)
	,m_iMaxHP(10)
	,m_iHp(10)
	,m_iDir(DIR_DOWN)
	,m_bIsDeadState(false)
	,m_fHitTime(0.f)
	,m_bCanChangeToHit(false)
{
}

CBossScript::~CBossScript()
{
}


void CBossScript::begin()
{
	MeshRender()->GetDynamicMaterial();
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, nullptr);
}

void CBossScript::tick()
{
	if (m_iHp < 1) {
		m_iHp = 0;
		m_bIsDeadState = true;
		ChangeState((UINT)SCRIPT_TYPE::BOSSDEADSCRIPT, false);
		return;
	}

	if (m_bCanChangeToHit) {
		m_fHitTime += DT;
		if (m_fHitTime > 5.f) {
			m_fHitTime = 0.f;
			m_bCanChangeToHit = false;
			Animator2D()->GetCurAnim()->Reset();
			CBossAttackScript* AttackScript = GetOwner()->GetScript<CBossAttackScript>();
			AttackScript->ResetAttackCount();
			CBossFlexScript* FlexScript = GetOwner()->GetScript<CBossFlexScript>();
			FlexScript->SetFlexTime(0.f);
			Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.f));
			m_bCanChangeToHit = false;
			ChangeState((UINT)SCRIPT_TYPE::BOSSATTACKSCRIPT, false);
		}
	}

}

void CBossScript::BeginOverlap(CCollider2D* _Other)
{
	if (m_bIsDeadState == true) return;
	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
	
	if ((Curlevel->GetLayer(_Other->GetOwner()->GetLayerIndex())->GetName() == L"PitWall"||
			Curlevel->GetLayer(_Other->GetOwner()->GetLayerIndex())->GetName() == L"Wall")) {
		RigidBody()->SetVelocity(Vec2(0.f, 0.f));

		// Calculate the direction from the wall to the player
		Matrix MatColliderPos = Collider2D()->GetColliderPosMat();
		Vec3 ColliderPos = Transform()->GetRelativePos() + Collider2D()->GetOffsetPos();
		Matrix MatWallColliderPos = _Other->GetColliderPosMat();
		Vec3 WallColliderPos = _Other->Transform()->GetRelativePos() + _Other->GetOffsetPos();

		Vec3 direction = WallColliderPos - ColliderPos;
		direction.Normalize();
		// Calculate the magnitude of the force based on the collider sizes and player speed
		Matrix MatColliderScale = Collider2D()->GetColliderScaleMat();
		Vec3 ColliderScale = Vec3(MatColliderScale._11, MatColliderScale._22, MatColliderScale._33);
		Matrix MatWallColliderScale = _Other->GetColliderScaleMat();
		Vec3 WallColliderScale = Vec3(MatWallColliderScale._11, MatWallColliderScale._22, MatWallColliderScale._33);

		float x;
		float y;
		float xratio = 0.f;
		float yratio = 0.f;

		// wall이 오른쪽에 있는 경우
		if (ColliderPos.x < WallColliderPos.x) {
			x = WallColliderPos.x - WallColliderScale.x / 2.0f - ColliderScale.x;
			xratio = (WallColliderPos.x - ColliderPos.x) / (WallColliderScale.x / 2.0f + ColliderScale.x / 2.0f);
		}
		//wall이 왼쪽에 있는 경우
		else {
			x = WallColliderPos.x + WallColliderScale.x / 2.0f + ColliderScale.x;
			xratio = (ColliderPos.x - WallColliderPos.x) / (WallColliderScale.x / 2.0f + ColliderScale.x / 2.0f);
		}

		//wall이 위쪽에 있는 경우
		if (ColliderPos.y < WallColliderPos.y) {
			y = WallColliderPos.y - WallColliderScale.y / 2.0f - ColliderScale.y;
			yratio = (WallColliderPos.y - ColliderPos.y) / (WallColliderScale.y / 2.0f + ColliderScale.y / 2.0f);
		}
		//wall이 아래쪽에 있는 경우
		else {
			y = WallColliderPos.y + WallColliderScale.y / 2.0f + ColliderScale.y;
			yratio = (ColliderPos.y - WallColliderPos.y) / (WallColliderScale.y / 2.0f + ColliderScale.y / 2.0f);
		}
		//x가 더 크다 -> 왼쪽이나 오른쪽으로 밀면됨
		if (xratio > yratio) {
			Transform()->SetRelativePos(Vec3(x - Collider2D()->GetOffsetPos().x,
				Transform()->GetRelativePos().y,
				Transform()->GetRelativePos().z));
		}
		else {
			Transform()->SetRelativePos(Vec3(Transform()->GetRelativePos().x,
				y - Collider2D()->GetOffsetPos().y,
				Transform()->GetRelativePos().z));
		}

	}

	
}

void CBossScript::OnOverlap(CCollider2D* _Other)
{
}

void CBossScript::EndOverlap(CCollider2D* _Other)
{
}

void CBossScript::SaveToLevelFile(FILE* _File)
{
}

void CBossScript::LoadFromLevelFile(FILE* _File)
{
	Animator2D()->LoadAnim(L"animation\\boss\\Boss_Clap.anim");
	Animator2D()->LoadAnim(L"animation\\boss\\Boss_Down.anim");
	Animator2D()->LoadAnim(L"animation\\boss\\Boss_FlexDown.anim");
	Animator2D()->LoadAnim(L"animation\\boss\\Boss_FlexRight.anim");
	Animator2D()->LoadAnim(L"animation\\boss\\Boss_HeavyStomp.anim");
	Animator2D()->LoadAnim(L"animation\\boss\\Boss_HookDown1.anim");
	Animator2D()->LoadAnim(L"animation\\boss\\Boss_HookDown2.anim");
	Animator2D()->LoadAnim(L"animation\\boss\\Boss_HookLeft1.anim");
	Animator2D()->LoadAnim(L"animation\\boss\\Boss_HookLeft2.anim");
	Animator2D()->LoadAnim(L"animation\\boss\\Boss_HookRight1.anim");
	Animator2D()->LoadAnim(L"animation\\boss\\Boss_HookRight2.anim");
	Animator2D()->LoadAnim(L"animation\\boss\\Boss_HookUp.anim");
	Animator2D()->LoadAnim(L"animation\\boss\\Boss_HookUp2.anim");
	Animator2D()->LoadAnim(L"animation\\boss\\Boss_Hurt.anim");
	Animator2D()->LoadAnim(L"animation\\boss\\Boss_Idle.anim");
	Animator2D()->LoadAnim(L"animation\\boss\\Boss_Leap.anim");
	Animator2D()->LoadAnim(L"animation\\boss\\Boss_LeapFall.anim");
	Animator2D()->LoadAnim(L"animation\\boss\\Boss_LeapLand.anim");
	Animator2D()->LoadAnim(L"animation\\boss\\Boss_LeapWindUp.anim");
	Animator2D()->LoadAnim(L"animation\\boss\\Boss_Punch_Down.anim");
	Animator2D()->LoadAnim(L"animation\\boss\\Boss_Punch_Left.anim");
	Animator2D()->LoadAnim(L"animation\\boss\\Boss_Punch_Right.anim");
	Animator2D()->LoadAnim(L"animation\\boss\\Boss_Punch_Up.anim");
	Animator2D()->LoadAnim(L"animation\\boss\\Boss_Run_Left.anim");
	Animator2D()->LoadAnim(L"animation\\boss\\Boss_Run_Right.anim");
	Animator2D()->LoadAnim(L"animation\\boss\\Boss_Swing_Down.anim");
	Animator2D()->LoadAnim(L"animation\\boss\\Boss_Swing_Left.anim");
	Animator2D()->LoadAnim(L"animation\\boss\\Boss_Swing_Right.anim");
	Animator2D()->LoadAnim(L"animation\\boss\\Boss_Swing_Up.anim");
}

