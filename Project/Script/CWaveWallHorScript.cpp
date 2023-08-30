#include "pch.h"
#include "CWaveWallHorScript.h"
#include "CMonsterSpawnPointScript.h"
#include <Engine/CResMgr.h>

CWaveWallHorScript::CWaveWallHorScript()
	:CScript((UINT)SCRIPT_TYPE::WAVEWALLHORSCRIPT)
{
	AddScriptParam(SCRIPT_PARAM::INT, &m_iWaveNum, "WaveNum");
}

CWaveWallHorScript::~CWaveWallHorScript()
{
}

void CWaveWallHorScript::begin()
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
			WaveScript->AddHorWall(GetOwner());
		}

	}
}

void CWaveWallHorScript::tick()
{
}

void CWaveWallHorScript::SaveToLevelFile(FILE* _File)
{
	fwrite(&m_iWaveNum, sizeof(int), 1, _File);
}

void CWaveWallHorScript::LoadFromLevelFile(FILE* _FILE)
{
	fread(&m_iWaveNum, sizeof(int), 1, _FILE);
	Ptr<CTexture> pri = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\Map\\PRISON_HOR.png");
	MeshRender()->GetDynamicMaterial();
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, pri);
}

void CWaveWallHorScript::BlockGate()
{
	Ptr<CTexture> pri = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\Map\\PRISON_HOR.png");
	MeshRender()->GetDynamicMaterial();
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, pri);
	GetOwner()->AddComponent(new CCollider2D);
	Collider2D()->SetAbsolute(false);
	Collider2D()->SetOffsetScale(Vec2(1.f, 1.f));
	Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\DoorClose.wav");
	pSound->Play(1, 0.2f, true);
}

void CWaveWallHorScript::RemoveGate()
{
	Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\DoorOpen.wav");
	pSound->Play(1, 0.2f, true);
	DestroyObject(GetOwner());
	
}



