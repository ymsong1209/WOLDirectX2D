#include "pch.h"
#include "CSwordManAttackScript.h"
#include "CSwordManScript.h"
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim2D.h>
#include "CSwordManAttackTraceScript.h"

CSwordManAttackScript::CSwordManAttackScript()
	:CScript((UINT)SCRIPT_TYPE::SWORDMANATTACKSCRIPT)
	,m_bAttackFinished(false)
{
	SetActive(false);
}

CSwordManAttackScript::~CSwordManAttackScript()
{
}


void CSwordManAttackScript::begin()
{
}

void CSwordManAttackScript::tick()
{
	if (!IsActive()) return;
	CSwordManScript* SwordManMainScript = GetOwner()->GetScript<CSwordManScript>();
	if (m_bAttackFinished == false) {
		if (Animator2D()->GetCurAnim()->IsFinish()) {
			Animator2D()->GetCurAnim()->Reset();
			if (SwordManMainScript->GetSwordManDir() == DIR_RIGHT) {
				float m_fDegree = 180.f / 180.f * XM_PI;
				Transform()->SetRelativeRot(Vec3(0.f, m_fDegree, 0.f));
				Animator2D()->Play(L"SwordMan_Attack_Left", false);
			}
			else if (SwordManMainScript->GetSwordManDir() == DIR_LEFT) {
				float m_fDegree = 0.f / 180.f * XM_PI;
				Transform()->SetRelativeRot(Vec3(0.f, m_fDegree, 0.f));
				Animator2D()->Play(L"SwordMan_Attack_Left", false);
			}
			

			//SwordManAttack 소환
			CGameObject* SwordManAttack = new CGameObject;
			SwordManAttack->SetName(L"SwordManAttack");
			SwordManAttack->AddComponent(new CTransform);
			SwordManAttack->AddComponent(new CMeshRender);
			SwordManAttack->AddComponent(new CAnimator2D);
			SwordManAttack->AddComponent(new CCollider2D);
			SwordManAttack->AddComponent(new CSwordManAttackTraceScript);
			SwordManAttack->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
			SwordManAttack->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"material\\Std2DLightMtrl.mtrl"));
			SwordManAttack->MeshRender()->GetDynamicMaterial();


			Vec3 PlayerPos = SwordManMainScript->GetPlayerPos();
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
			SwordManAttack->Transform()->SetRelativeScale(Vec3(100.f, 150.f, 1.f));
			Vec3 vRotation = (Vec3(0.f, 0.f, angle) / 180.f) * XM_PI;

			//마우스 위치에 따라서 4사분면으로 나눔
			SwordManAttack->Transform()->SetRelativePos(Vec3(OwnerPos.x + 120 * cos(vRotation.z), OwnerPos.y + 120 * sin(vRotation.z), OwnerPos.z));
			SwordManAttack->Transform()->SetRelativeRot(vRotation);
			CSwordManAttackTraceScript* AttackScript = SwordManAttack->GetScript<CSwordManAttackTraceScript>();
			AttackScript->SetInputAngle((float)angle);
			SwordManAttack->Collider2D()->SetAbsolute(true);
			SwordManAttack->Collider2D()->SetOffsetScale(Vec2(100.f, 100.f));
			SpawnGameObject(SwordManAttack, SwordManAttack->Transform()->GetRelativePos(), L"MonsterProjectile");
			m_bAttackFinished = true;
		}
	}
	else {
		if (Animator2D()->GetCurAnim()->IsFinish()) {
			Animator2D()->GetCurAnim()->Reset();
			ChangeState((UINT)SCRIPT_TYPE::SWORDMANIDLESCRIPT, false);
		}
	}
	CGameObject* Player = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"Player");
}

void CSwordManAttackScript::Enter()
{
	m_bAttackFinished = false;
	CSwordManScript* SwordManMainScript = GetOwner()->GetScript<CSwordManScript>();
	if (SwordManMainScript->GetSwordManDir() == DIR_RIGHT) {
		float m_fDegree = 180.f / 180.f * XM_PI;
		Transform()->SetRelativeRot(Vec3(0.f, m_fDegree, 0.f));
		Animator2D()->Play(L"SwordMan_AttackReady_Left", false);
	}
	else if (SwordManMainScript->GetSwordManDir() == DIR_LEFT) {
		float m_fDegree = 0.f / 180.f * XM_PI;
		Transform()->SetRelativeRot(Vec3(0.f, m_fDegree, 0.f));
		Animator2D()->Play(L"SwordMan_AttackReady_Left", false);
	}
}

void CSwordManAttackScript::Exit()
{
	Animator2D()->GetCurAnim()->Reset();
}

