#include "pch.h"
#include "CSwordManWaitScript.h"
#include "CSwordManScript.h"
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include "CMonsterSpawnPointScript.h"

CSwordManWaitScript::CSwordManWaitScript()
	:CScript((UINT)SCRIPT_TYPE::SWORDMANWAITSCRIPT)
{
	SetActive(false);
}

CSwordManWaitScript::~CSwordManWaitScript()
{
}


void CSwordManWaitScript::begin()
{
}

void CSwordManWaitScript::tick()
{
	if (!IsActive()) return;
}

void CSwordManWaitScript::Enter()
{
	
	CSwordManScript* SwordManMainScript = GetOwner()->GetScript<CSwordManScript>();
	//MeshRender에 텅빈 텍스쳐 밀어넣기
	Ptr<CTexture> pTex = nullptr;
	MeshRender()->GetDynamicMaterial()->SetTexParam(TEX_0, pTex);

	CLayer* MonsterLayer = CLevelMgr::GetInst()->GetCurLevel()->FindLayerByName(L"Monster");
	GetOwner()->SetLayerIndex(MonsterLayer->GetLayerIndex());

	//Wave에 자기자신 넣기
	int CurWaveNum = SwordManMainScript->GetSwordManWaveNum();
	CLayer* WaveLayer = CLevelMgr::GetInst()->GetCurLevel()->FindLayerByName(L"Wave");
	for (size_t i = 0; i < WaveLayer->GetParentObject().size(); ++i) {
		CGameObject* Wave = WaveLayer->GetParentObject()[i];
		CMonsterSpawnPointScript* WaveScript = Wave->GetScript<CMonsterSpawnPointScript>();
		if (WaveScript->GetWaveNum() == CurWaveNum) {
			WaveScript->AddMonster(GetOwner());
		}

	}
	//Position Z축 맞추기
	Vec3 Pos = Transform()->GetRelativePos();
	Transform()->SetAbsolute(true);
	Transform()->SetRelativePos(Vec3(Pos.x, Pos.y, 350.f));
}

void CSwordManWaitScript::Exit()
{
}

void CSwordManWaitScript::SaveToLevelFile(FILE* _File)
{
	
}

void CSwordManWaitScript::LoadFromLevelFile(FILE* _FILE)
{
	//Level이 Stop상태이여도 SwordMan의 Position을 보고 싶음
	MeshRender()->GetDynamicMaterial();
	Ptr<CTexture> SwordManPortrait = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\Enemy\\png\\SWORDMAN_PORTRAIT.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, SwordManPortrait);
}

