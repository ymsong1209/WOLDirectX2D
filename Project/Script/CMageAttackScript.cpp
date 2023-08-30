#include "pch.h"
#include "CMageAttackScript.h"
#include "CMageScript.h"
#include "CMageBallScript.h"
#include "CMonsterSpawnPointScript.h"
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim2D.h>

CMageAttackScript::CMageAttackScript()
	:CScript((UINT)SCRIPT_TYPE::MAGEATTACKSCRIPT)
	,m_fAttackCoolTime(0.f)
{
	SetActive(false);
}

CMageAttackScript::~CMageAttackScript()
{
}


void CMageAttackScript::begin()
{
}

void CMageAttackScript::tick()
{
	if (!IsActive()) return;
	m_fAttackCoolTime += DT;
	if (m_fAttackCoolTime > 2.0f) {
		CMageScript* MageMainScript = GetOwner()->GetScript<CMageScript>();

		Ptr<CPrefab> WizardBallPrefab = CResMgr::GetInst()->FindRes<CPrefab>(L"prefab\\MageBall.prefab");
		CGameObject* WizardBall = WizardBallPrefab->Instantiate();
		Vec3 CurPos = Transform()->GetRelativePos();
		SpawnGameObject(WizardBall, Vec3(CurPos.x + 100.f, CurPos.y + 100.f, CurPos.z), L"Monster");

		CGameObject* WizardBall2 = WizardBallPrefab->Instantiate();
		CurPos = Transform()->GetRelativePos();
		SpawnGameObject(WizardBall2, Vec3(CurPos.x - 100.f, CurPos.y + 100.f, CurPos.z), L"Monster");
		

		//Wave에 자기자신 넣기
		int CurWaveNum = MageMainScript->GetMageWaveNum();
		CMageBallScript* BallScript1 = WizardBall->GetScript<CMageBallScript>();
		BallScript1->SetBallWaveNum(CurWaveNum);
		CMageBallScript* BallScript2 = WizardBall2->GetScript<CMageBallScript>();
		BallScript2->SetBallWaveNum(CurWaveNum);

		CLayer* WaveLayer = CLevelMgr::GetInst()->GetCurLevel()->FindLayerByName(L"Wave");
		for (size_t i = 0; i < WaveLayer->GetParentObject().size(); ++i) {
			CGameObject* Wave = WaveLayer->GetParentObject()[i];
			CMonsterSpawnPointScript* WaveScript = Wave->GetScript<CMonsterSpawnPointScript>();
			if (WaveScript->GetWaveNum() == CurWaveNum) {
				WaveScript->AddMonster(WizardBall);
				WaveScript->AddMonster(WizardBall2);
			}
		}

		ChangeState((UINT)SCRIPT_TYPE::MAGEIDLESCRIPT, false);
	}
}

void CMageAttackScript::Enter()
{
	m_fAttackCoolTime = 0.f;
	CMageScript* MageMainScript = GetOwner()->GetScript<CMageScript>();
	if (MageMainScript->GetMageDir() & DIR_LEFT) {
		float m_fDegree = 0.f / 180.f * XM_PI;
		Transform()->SetRelativeRot(Vec3(0.f, m_fDegree, 0.f));
		Animator2D()->Play(L"Wizard_Attack_Left", true);
	}
	else {
		float m_fDegree = 180.f / 180.f * XM_PI;
		Transform()->SetRelativeRot(Vec3(0.f, m_fDegree, 0.f));
		Animator2D()->Play(L"Wizard_Attack_Left", true);
	}
	Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\flippage.mp3");
	m_pSound = pSound.Get();
	m_pSound->Play(0, 0.4, true);

}

void CMageAttackScript::Exit()
{
	m_fAttackCoolTime = 0.f;
	m_pSound->Stop();
}


