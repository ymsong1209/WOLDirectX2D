#include "pch.h"
#include "CMageDeadScript.h"
#include "CMageScript.h"
#include "CMonsterSpawnPointScript.h"
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim2D.h>

CMageDeadScript::CMageDeadScript()
	:CScript((UINT)SCRIPT_TYPE::MAGEDEADSCRIPT)
{
	SetActive(false);
}

CMageDeadScript::~CMageDeadScript()
{
}

void CMageDeadScript::begin()
{
}

void CMageDeadScript::tick()
{
	if (!IsActive()) return;
	if (Animator2D()->GetCurAnim()->IsFinish()) {
		DestroyObject(GetOwner());
	}
}

void CMageDeadScript::Enter()
{
	CMageScript* MageMainScript = GetOwner()->GetScript<CMageScript>();
	MageMainScript->SetMageDeadState(true);
	if (MageMainScript->GetMageDir() & DIR_LEFT) {
		float m_fDegree = 0.f / 180.f * XM_PI;
		Transform()->SetRelativeRot(Vec3(0.f, m_fDegree, 0.f));
		Animator2D()->Play(L"Wizard_Death.Left", false);
	}
	else {
		float m_fDegree = 180.f / 180.f * XM_PI;
		Transform()->SetRelativeRot(Vec3(0.f, m_fDegree, 0.f));
		Animator2D()->Play(L"Wizard_Death.Left", false);
	}


	//Wave에 자기자신 빼기
	int CurWaveNum = MageMainScript->GetMageWaveNum();
	CLayer* WaveLayer = CLevelMgr::GetInst()->GetCurLevel()->FindLayerByName(L"Wave");
	for (size_t i = 0; i < WaveLayer->GetParentObject().size(); ++i) {
		CGameObject* Wave = WaveLayer->GetParentObject()[i];
		CMonsterSpawnPointScript* WaveScript = Wave->GetScript<CMonsterSpawnPointScript>();
		if (WaveScript->GetWaveNum() == CurWaveNum) {
			WaveScript->RemoveMonsterCount();
		}
	}
}

void CMageDeadScript::Exit()
{
}


