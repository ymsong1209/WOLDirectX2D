#include "pch.h"
#include "CGhoulAttackScript.h"
#include "CGhoulScript.h"
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim2D.h>
#include "CGhoulAttackTraceScript.h"

CGhoulAttackScript::CGhoulAttackScript()
	:CScript((UINT)SCRIPT_TYPE::GHOULATTACKSCRIPT)
	, m_bAttackFinished(false)
{
	SetActive(false);
}

CGhoulAttackScript::~CGhoulAttackScript()
{
}


void CGhoulAttackScript::begin()
{
}

void CGhoulAttackScript::tick()
{
	if (!IsActive()) return;
	CGhoulScript* GhoulMainScript = GetOwner()->GetScript<CGhoulScript>();
	if (m_bAttackFinished == false) {
		if (Animator2D()->GetCurAnim()->IsFinish()) {
			Animator2D()->GetCurAnim()->Reset();
			if (GhoulMainScript->GetGhoulDir() == DIR_RIGHT) {
				float m_fDegree = 180.f / 180.f * XM_PI;
				Transform()->SetRelativeRot(Vec3(0.f, m_fDegree, 0.f));
				Animator2D()->Play(L"GhoulAttack_Left", false);
			}
			else if (GhoulMainScript->GetGhoulDir() == DIR_LEFT) {
				float m_fDegree = 0.f / 180.f * XM_PI;
				Transform()->SetRelativeRot(Vec3(0.f, m_fDegree, 0.f));
				Animator2D()->Play(L"GhoulAttack_Left", false);
			}


			//GhoulAttack 소환
			CGameObject* GhoulAttack = new CGameObject;
			GhoulAttack->SetName(L"SwordManAttack");
			GhoulAttack->AddComponent(new CTransform);
			GhoulAttack->AddComponent(new CMeshRender);
			GhoulAttack->AddComponent(new CAnimator2D);
			GhoulAttack->AddComponent(new CCollider2D);
			GhoulAttack->AddComponent(new CGhoulAttackTraceScript);
			GhoulAttack->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
			GhoulAttack->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"material\\Std2DLightMtrl.mtrl"));
			GhoulAttack->MeshRender()->GetDynamicMaterial();


			Vec3 PlayerPos = GhoulMainScript->GetPlayerPos();
			Vec3 OwnerPos = Transform()->GetRelativePos();
			// calculate the slope of the line from A to B
			double slope = (PlayerPos.y - OwnerPos.y) / (PlayerPos.x - OwnerPos.x);
			// calculate the angle between the x-axis and the line in radians
			double angle = atan(slope);
			// convert radians to degrees
			angle = angle * 180.0 / XM_PI;
			// if the slope is negative, add 180 degrees to get the acute angle
			if (slope < 0) {
				angle += 180.0;
			}
			// if the slope is positive and y2 < y1, add 360 degrees
			if (PlayerPos.y < OwnerPos.y) {
				angle += 180.0;
			}
			GhoulAttack->Transform()->SetRelativeScale(Vec3(100.f, 150.f, 1.f));
			Vec3 vRotation = (Vec3(0.f, 0.f, angle) / 180.f) * XM_PI;

			//마우스 위치에 따라서 4사분면으로 나눔
			GhoulAttack->Transform()->SetRelativePos(Vec3(OwnerPos.x + 80 * cos(vRotation.z), OwnerPos.y + 80 * sin(vRotation.z), OwnerPos.z));
			GhoulAttack->Transform()->SetRelativeRot(vRotation);
			CGhoulAttackTraceScript* AttackScript = GhoulAttack->GetScript<CGhoulAttackTraceScript>();
			AttackScript->SetInputAngle((float)angle);
			GhoulAttack->Collider2D()->SetAbsolute(true);
			GhoulAttack->Collider2D()->SetOffsetScale(Vec2(100.f, 100.f));
			SpawnGameObject(GhoulAttack, GhoulAttack->Transform()->GetRelativePos(), L"MonsterProjectile");
			m_bAttackFinished = true;
		}
	}
	else {
		if (Animator2D()->GetCurAnim()->IsFinish()) {
			Animator2D()->GetCurAnim()->Reset();
			ChangeState((UINT)SCRIPT_TYPE::GHOULIDLESCRIPT, false);
		}
	}
}

void CGhoulAttackScript::Enter()
{
	m_bAttackFinished = false;
	CGhoulScript* GhoulMainScript = GetOwner()->GetScript<CGhoulScript>();
	if (GhoulMainScript->GetGhoulDir() == DIR_RIGHT) {
		float m_fDegree = 180.f / 180.f * XM_PI;
		Transform()->SetRelativeRot(Vec3(0.f, m_fDegree, 0.f));
		Animator2D()->Play(L"GhoulAttackReady_Left", false);
	}
	else if (GhoulMainScript->GetGhoulDir() == DIR_LEFT) {
		float m_fDegree = 0.f / 180.f * XM_PI;
		Transform()->SetRelativeRot(Vec3(0.f, m_fDegree, 0.f));
		Animator2D()->Play(L"GhoulAttackReady_Left", false);
	}
}

void CGhoulAttackScript::Exit()
{
	Animator2D()->GetCurAnim()->Reset();
}

