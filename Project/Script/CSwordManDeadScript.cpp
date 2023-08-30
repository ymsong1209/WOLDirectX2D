#include "pch.h"
#include "CSwordManDeadScript.h"
#include <Engine/CAnim2D.h>
#include <Engine/CAnimator2D.h>
#include "CSwordManScript.h"
#include "CMonsterSpawnPointScript.h"


CSwordManDeadScript::CSwordManDeadScript()
	:CScript((UINT)SCRIPT_TYPE::SWORDMANDEADSCRIPT)
{
	SetActive(false);
}


CSwordManDeadScript::~CSwordManDeadScript()
{
}


void CSwordManDeadScript::begin()
{

}

void CSwordManDeadScript::tick()
{
	if (!IsActive()) return;
	if (Animator2D()->GetCurAnim()->IsFinish()) {
		
		DestroyObject(GetOwner());
	}
}

void CSwordManDeadScript::Enter()
{
	CSwordManScript* SwordManScript = GetOwner()->GetScript<CSwordManScript>();
	SwordManScript->SetSwordManDeadState(true);
	if (SwordManScript->GetSwordManDir() & DIR_LEFT) {
		float m_fDegree = 0.f / 180.f * XM_PI;
		Transform()->SetRelativeRot(Vec3(0.f, m_fDegree, 0.f));
		Animator2D()->Play(L"SwordMan_Death_Left", false);
	}
	else {
		float m_fDegree = 180.f / 180.f * XM_PI;
		Transform()->SetRelativeRot(Vec3(0.f, m_fDegree, 0.f));
		Animator2D()->Play(L"SwordMan_Death_Left", false);
	}

	
	//Wave에 자기자신 빼기
	int CurWaveNum = SwordManScript->GetSwordManWaveNum();
	CLayer* WaveLayer = CLevelMgr::GetInst()->GetCurLevel()->FindLayerByName(L"Wave");
	for (size_t i = 0; i < WaveLayer->GetParentObject().size(); ++i) {
		CGameObject* Wave = WaveLayer->GetParentObject()[i];
		CMonsterSpawnPointScript* WaveScript = Wave->GetScript<CMonsterSpawnPointScript>();
		if (WaveScript->GetWaveNum() == CurWaveNum) {
			WaveScript->RemoveMonsterCount();
		}

	}
}

void CSwordManDeadScript::Exit()
{
}

