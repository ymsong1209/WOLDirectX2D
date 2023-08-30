#include "pch.h"
#include "CBossWaveScript.h"
#include "CBossScript.h"
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

CBossWaveScript::CBossWaveScript()
	:CScript((UINT)SCRIPT_TYPE::BOSSWAVESCRIPT)
	,m_bWaveActive(true)
{
}

CBossWaveScript::~CBossWaveScript()
{
}


void CBossWaveScript::begin()
{
}

void CBossWaveScript::tick()
{
}

void CBossWaveScript::BeginOverlap(CCollider2D* _Other)
{
	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
	if (m_bWaveActive == false) return;

	if (_Other->GetOwner()->GetName() == L"Player") {
		Activate();
	}
}

void CBossWaveScript::Activate()
{
	CGameObject* Boss = CLevelMgr::GetInst()->FindParentObjectByName(L"Boss");
	CBossScript* Script = Boss->GetScript<CBossScript>();
	Script->ChangeState((UINT)SCRIPT_TYPE::BOSSENTERSCRIPT, false);

	m_pBossBGM = CResMgr::GetInst()->FindRes<CSound>(L"sound\\Boss.wav");
	m_pBossBGM->Play(0, 0.2, true);
	m_bWaveActive = false;

	CGameObject* WallObject = CResMgr::GetInst()->FindRes<CPrefab>(L"prefab\\WallObject.prefab")->Instantiate();
	WallObject->Transform()->SetRelativePos(Vec3(0.f, -486.f, 1.f));
	WallObject->Transform()->SetRelativeScale(Vec3(474.f, 81.f, 1.f));
	SpawnGameObject(WallObject, WallObject->Transform()->GetRelativePos(), L"Wall");

}

void CBossWaveScript::Deactivate()
{
	m_pBossBGM->Stop();
}


