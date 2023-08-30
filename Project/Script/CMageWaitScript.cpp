#include "pch.h"
#include "CMageWaitScript.h"
#include "CMageScript.h"
#include "CMonsterSpawnPointScript.h"

CMageWaitScript::CMageWaitScript()
	:CScript((UINT)SCRIPT_TYPE::MAGEWAITSCRIPT)
{
	SetActive(false);
}

CMageWaitScript::~CMageWaitScript()
{
}


void CMageWaitScript::begin()
{
}

void CMageWaitScript::tick()
{
	if (!IsActive()) return;
}

void CMageWaitScript::Enter()
{

	CMageScript* MageMainScript = GetOwner()->GetScript<CMageScript>();
	//MeshRender�� �ֺ� �ؽ��� �о�ֱ�
	Ptr<CTexture> pTex = nullptr;
	MeshRender()->GetDynamicMaterial()->SetTexParam(TEX_0, pTex);

	CLayer* MonsterLayer = CLevelMgr::GetInst()->GetCurLevel()->FindLayerByName(L"Monster");
	GetOwner()->SetLayerIndex(MonsterLayer->GetLayerIndex());

	//Wave�� �ڱ��ڽ� �ֱ�
	int CurWaveNum = MageMainScript->GetMageWaveNum();
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

void CMageWaitScript::Exit()
{
}

void CMageWaitScript::SaveToLevelFile(FILE* _File)
{
}

void CMageWaitScript::LoadFromLevelFile(FILE* _FILE)
{
	//Level�� Stop�����̿��� SwordMan�� Position�� ���� ����
	MeshRender()->GetDynamicMaterial();
	Ptr<CTexture> WizardPortrait = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\Enemy\\png\\WIZARD_PORTRAIT.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, WizardPortrait);
}

