#include "pch.h"
#include "CGhoulDeadScript.h"
#include <Engine/CAnim2D.h>
#include <Engine/CAnimator2D.h>
#include "CGhoulScript.h"
#include "CMonsterSpawnPointScript.h"


CGhoulDeadScript::CGhoulDeadScript()
	:CScript((UINT)SCRIPT_TYPE::GHOULDEADSCRIPT)
{
	SetActive(false);
}


CGhoulDeadScript::~CGhoulDeadScript()
{
}


void CGhoulDeadScript::begin()
{

}

void CGhoulDeadScript::tick()
{
	if (!IsActive()) return;
	if (Animator2D()->GetCurAnim()->IsFinish()) {

		DestroyObject(GetOwner());
	}
}

void CGhoulDeadScript::Enter()
{
	CGhoulScript* GhoulMainScript = GetOwner()->GetScript<CGhoulScript>();
	GhoulMainScript->SetGhoulDeadState(true);
	if (GhoulMainScript->GetGhoulDir() & DIR_LEFT) {
		float m_fDegree = 180.f / 180.f * XM_PI;
		Transform()->SetRelativeRot(Vec3(0.f, m_fDegree, 0.f));
		Animator2D()->Play(L"GhoulDead_Right", false);
	}
	else {
		float m_fDegree = 0.f / 180.f * XM_PI;
		Transform()->SetRelativeRot(Vec3(0.f, m_fDegree, 0.f));
		Animator2D()->Play(L"GhoulDead_Right", false);
	}


	//Wave에 자기자신 빼기
	int CurWaveNum = GhoulMainScript->GetGhoulWaveNum();
	CLayer* WaveLayer = CLevelMgr::GetInst()->GetCurLevel()->FindLayerByName(L"Wave");
	for (size_t i = 0; i < WaveLayer->GetParentObject().size(); ++i) {
		CGameObject* Wave = WaveLayer->GetParentObject()[i];
		CMonsterSpawnPointScript* WaveScript = Wave->GetScript<CMonsterSpawnPointScript>();
		if (WaveScript->GetWaveNum() == CurWaveNum) {
			WaveScript->RemoveMonsterCount();
		}

	}

	srand(time(NULL));
	if (rand() % 5 == 0) {
		Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\EnemyDead0.wav");
		pSound->Play(1, 0.2f, true);
	}
	else if (rand() % 5 == 1) {
		Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\EnemyDead1.wav");
		pSound->Play(1, 0.2f, true);
	}
	else if (rand() % 5 == 2) {
		Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\EnemyDead2.wav");
		pSound->Play(1, 0.2f, true);
	}
	else if (rand() % 5 == 3) {
		Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\EnemyDead3.wav");
		pSound->Play(1, 0.2f, true);
	}
	else {
		Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\EnemyDead4.wav");
		pSound->Play(1, 0.2f, true);
	}
}

void CGhoulDeadScript::Exit()
{
}

