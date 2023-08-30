#include "pch.h"
#include "CGhoulWaitScript.h"
#include "CGhoulScript.h"
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include "CMonsterSpawnPointScript.h"

CGhoulWaitScript::CGhoulWaitScript()
	:CScript((UINT)SCRIPT_TYPE::GHOULWAITSCRIPT)
{
	SetActive(false);
}

CGhoulWaitScript::~CGhoulWaitScript()
{
}


void CGhoulWaitScript::begin()
{
}

void CGhoulWaitScript::tick()
{
	if (!IsActive()) return;
}

void CGhoulWaitScript::Enter()
{

	CGhoulScript* GhoulMainScript = GetOwner()->GetScript<CGhoulScript>();
	//MeshRender�� �ֺ� �ؽ��� �о�ֱ�
	Ptr<CTexture> pTex = nullptr;
	MeshRender()->GetDynamicMaterial()->SetTexParam(TEX_0, pTex);

	CLayer* MonsterLayer = CLevelMgr::GetInst()->GetCurLevel()->FindLayerByName(L"Monster");
	GetOwner()->SetLayerIndex(MonsterLayer->GetLayerIndex());

	//Wave�� �ڱ��ڽ� �ֱ�
	int CurWaveNum = GhoulMainScript->GetGhoulWaveNum();
	CLayer* WaveLayer = CLevelMgr::GetInst()->GetCurLevel()->FindLayerByName(L"Wave");
	for (size_t i = 0; i < WaveLayer->GetParentObject().size(); ++i) {
		CGameObject* Wave = WaveLayer->GetParentObject()[i];
		CMonsterSpawnPointScript* WaveScript = Wave->GetScript<CMonsterSpawnPointScript>();
		if (WaveScript->GetWaveNum() == CurWaveNum) {
			WaveScript->AddMonster(GetOwner());
		}

	}
	//Position Z�� ���߱�
	Vec3 Pos = Transform()->GetRelativePos();
	Transform()->SetAbsolute(true);
	Transform()->SetRelativePos(Vec3(Pos.x, Pos.y, 350.f));
}

void CGhoulWaitScript::Exit()
{
}

void CGhoulWaitScript::SaveToLevelFile(FILE* _File)
{

}

void CGhoulWaitScript::LoadFromLevelFile(FILE* _FILE)
{
	//Level�� Stop�����̿��� Ghoul�� Position�� ���� ����
	MeshRender()->GetDynamicMaterial();
	Ptr<CTexture> SwordManPortrait = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\Enemy\\png\\GHOUL_PORTRAIT.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, SwordManPortrait);
}