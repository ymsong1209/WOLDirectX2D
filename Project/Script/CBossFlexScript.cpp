#include "pch.h"
#include "CBossFlexScript.h"
#include <Engine/CScript.h>
#include "CBossScript.h"
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim2D.h>
#include "CBossAttackScript.h"
CBossFlexScript::CBossFlexScript()
	:CScript((UINT)SCRIPT_TYPE::BOSSFLEXSCRIPT)
	,m_fFlexTime(0.f)
{
	SetActive(false);
}

CBossFlexScript::~CBossFlexScript()
{
}

void CBossFlexScript::begin()
{
}

void CBossFlexScript::tick()
{
	if (!IsActive()) return;
	m_fFlexTime += DT;
	if (m_fFlexTime <0.4f) {
		if (!m_bAnimationPlayed) {
			Animator2D()->Play(L"Boss_FlexDown", false);
		}
	}
	else if (m_fFlexTime < 5.0f) {
		if (!m_bAnimationPlayed) {
			Animator2D()->Play(L"Boss_FlexRight", false);
			m_bAnimationPlayed = true;
		}
		else {
			if (Animator2D()->GetCurAnim()->IsFinish()) {
				Animator2D()->GetCurAnim()->Reset();
				float Rot = XMConvertToDegrees(Transform()->GetRelativeRot().y);
				int a = 0;
				Transform()->SetRelativeRot(Vec3(0.f, XMConvertToRadians(Rot + 180.f), 0.f));
				Animator2D()->Play(L"Boss_FlexRight", false);
				srand(time(NULL));
				if (rand() % 3 == 0) {
					Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\EarthBossFlex0.wav");
					pSound->Play(1, 0.2, true);
				}
				else if (rand() % 3 == 1) {
					Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\EarthBossFlex1.wav");
					pSound->Play(1, 0.2, true);
				}
				else if (rand() % 3 == 2) {
					Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\EarthBossFlex2.wav");
					pSound->Play(1, 0.2, true);
				}
				else {
					Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\EarthBossFlex3.wav");
					pSound->Play(1, 0.2, true);
				}
			}
		}
	}
}

void CBossFlexScript::Enter()
{
	CBossScript* Script = GetOwner()->GetScript<CBossScript>();
	Script->SetCanChangeToHit(true);
	m_bAnimationPlayed = false;
}

void CBossFlexScript::Exit()
{
	m_bAnimationPlayed = false;
	Animator2D()->GetCurAnim()->Reset();
}

