#include "pch.h"
#include "CWaveWallVerScript.h"
#include "CMonsterSpawnPointScript.h"

CWaveWallVerScript::CWaveWallVerScript()
	:CScript((UINT)SCRIPT_TYPE::WAVEWALLVERSCRIPT)
{
	AddScriptParam(SCRIPT_PARAM::INT, &m_iWaveNum, "WaveNum");
}

CWaveWallVerScript::~CWaveWallVerScript()
{
}

void CWaveWallVerScript::begin()
{
	Ptr<CTexture> tex = nullptr;
	MeshRender()->GetDynamicMaterial();
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, tex);

	//Wave에 자기자신 넣기
	int CurWaveNum = m_iWaveNum;
	CLayer* WaveLayer = CLevelMgr::GetInst()->GetCurLevel()->FindLayerByName(L"Wave");
	for (size_t i = 0; i < WaveLayer->GetParentObject().size(); ++i) {
		CGameObject* Wave = WaveLayer->GetParentObject()[i];
		CMonsterSpawnPointScript* WaveScript = Wave->GetScript<CMonsterSpawnPointScript>();
		if (WaveScript->GetWaveNum() == CurWaveNum) {
			WaveScript->AddVerWall(GetOwner());
		}

	}
}

void CWaveWallVerScript::tick()
{
}

void CWaveWallVerScript::SaveToLevelFile(FILE* _File)
{
	fwrite(&m_iWaveNum, sizeof(int), 1, _File);
}

void CWaveWallVerScript::LoadFromLevelFile(FILE* _FILE)
{
	fread(&m_iWaveNum, sizeof(int), 1, _FILE);
	Ptr<CTexture> pri = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\Map\\PRISON_VER.png");
	MeshRender()->GetDynamicMaterial();
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, pri);
}

void CWaveWallVerScript::BlockGate()
{
	Ptr<CTexture> pri = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\Map\\PRISON_VER.png");
	MeshRender()->GetDynamicMaterial();
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, pri);
	GetOwner()->AddComponent(new CCollider2D);
	Collider2D()->SetAbsolute(false);
	Collider2D()->SetOffsetScale(Vec2(1.f, 1.f));
	Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\DoorClose.wav");
	pSound->Play(1, 0.2f, true);
}

void CWaveWallVerScript::RemoveGate()
{
	Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\DoorOpen.wav");
	pSound->Play(1, 0.2f, true);
	DestroyObject(GetOwner());
}



