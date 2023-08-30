#include "pch.h"
#include "CMonsterSpawnPointScript.h"
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include "CSwordManScript.h"
#include "CMageScript.h"
#include "CGhoulScript.h"
#include "CWaveWallHorScript.h"
#include "CWaveWallVerScript.h"



CMonsterSpawnPointScript::CMonsterSpawnPointScript()
	:CScript((UINT)SCRIPT_TYPE::MONSTERSPAWNPOINTSCRIPT)
	, m_bSpawned(false)
{
	AddScriptParam(SCRIPT_PARAM::INT, &m_iWaveNum, "WaveNum");
}

CMonsterSpawnPointScript::~CMonsterSpawnPointScript()
{
}

void CMonsterSpawnPointScript::tick()
{
	
}

void CMonsterSpawnPointScript::begin()
{
	
}

void CMonsterSpawnPointScript::AddMonster(CGameObject* Monster)
{
	++m_iMonsterCount;
	m_vecMonster.push_back(Monster);
}

void CMonsterSpawnPointScript::RemoveMonsterCount()
{
	--m_iMonsterCount;
	if (m_iMonsterCount < 1) {
		for (size_t i = 0; i < m_vecHorWall.size(); ++i) {
			CWaveWallHorScript* WallScript = m_vecHorWall[i]->GetScript<CWaveWallHorScript>();
			WallScript->RemoveGate();
		}
		for (size_t i = 0; i < m_vecVerWall.size(); ++i) {
			CWaveWallVerScript* WallScript = m_vecVerWall[i]->GetScript<CWaveWallVerScript>();
			WallScript->RemoveGate();
		}
		DestroyObject(GetOwner());
	}


}

void CMonsterSpawnPointScript::SpawnMonster()
{
	if (m_bSpawned == false) {
		m_bSpawned = true;
		for (size_t i = 0; i < m_vecMonster.size(); ++i) {
			if (m_vecMonster[i]->GetName() == L"SwordMan") {
				CSwordManScript* SwordManMainScript = m_vecMonster[i]->GetScript<CSwordManScript>();
				SwordManMainScript->ChangeState((UINT)SCRIPT_TYPE::SWORDMANSPAWNSCRIPT, false);
			}
			else if (m_vecMonster[i]->GetName() == L"Mage") {
				CMageScript* MageScript = m_vecMonster[i]->GetScript<CMageScript>();
				MageScript->ChangeState((UINT)SCRIPT_TYPE::MAGESPAWNSCRIPT, false);
			}
			else if (m_vecMonster[i]->GetName() == L"Ghoul") {
				CGhoulScript* GhoulMainScript = m_vecMonster[i]->GetScript<CGhoulScript>();
				GhoulMainScript->ChangeState((UINT)SCRIPT_TYPE::GHOULSPAWNSCRIPT, false);
			}
		}

		for (size_t i = 0; i < m_vecHorWall.size(); ++i) {
			CWaveWallHorScript* WallScript = m_vecHorWall[i]->GetScript<CWaveWallHorScript>();
			WallScript->BlockGate();
		}

		for (size_t i = 0; i < m_vecVerWall.size(); ++i) {
			CWaveWallVerScript* WallScript = m_vecVerWall[i]->GetScript<CWaveWallVerScript>();
			WallScript->BlockGate();
		}
	}
}

void CMonsterSpawnPointScript::SaveToLevelFile(FILE* _File)
{
	fwrite(&m_iWaveNum, sizeof(int), 1, _File);
}

void CMonsterSpawnPointScript::LoadFromLevelFile(FILE* _FILE)
{
	fread(&m_iWaveNum, sizeof(int), 1, _FILE);
}

void CMonsterSpawnPointScript::BeginOverlap(CCollider2D* _Other)
{
	SpawnMonster();
}

void CMonsterSpawnPointScript::OnOverlap(CCollider2D* _Other)
{
}

void CMonsterSpawnPointScript::EndOverlap(CCollider2D* _Other)
{
}


