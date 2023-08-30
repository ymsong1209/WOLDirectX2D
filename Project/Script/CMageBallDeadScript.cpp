#include "pch.h"
#include "CMageBallDeadScript.h"
#include "CMageBallScript.h"
#include "CMonsterSpawnPointScript.h"

CMageBallDeadScript::CMageBallDeadScript()
	:CScript((UINT)SCRIPT_TYPE::MAGEBALLDEADSCRIPT)
{
	SetActive(false);
}

CMageBallDeadScript::~CMageBallDeadScript()
{

}
void CMageBallDeadScript::begin()
{
}

void CMageBallDeadScript::tick()
{
	if (!IsActive()) return;
	DestroyObject(GetOwner());

}

void CMageBallDeadScript::Enter()
{
	CMageBallScript* MageBallMainScript = GetOwner()->GetScript<CMageBallScript>();
	
	//Wave에 자기자신 빼기
	int CurWaveNum = MageBallMainScript->GetBallWaveNum();
	CLayer* WaveLayer = CLevelMgr::GetInst()->GetCurLevel()->FindLayerByName(L"Wave");
	for (size_t i = 0; i < WaveLayer->GetParentObject().size(); ++i) {
		CGameObject* Wave = WaveLayer->GetParentObject()[i];
		CMonsterSpawnPointScript* WaveScript = Wave->GetScript<CMonsterSpawnPointScript>();
		if (WaveScript->GetWaveNum() == CurWaveNum) {
			WaveScript->RemoveMonsterCount();
		}
	}
	Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\Splash.wav");
	pSound->Play(1, 0.2, true);
	
}

void CMageBallDeadScript::Exit()
{
}


