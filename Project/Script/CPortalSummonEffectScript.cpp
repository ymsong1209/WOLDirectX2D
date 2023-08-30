#include "pch.h"
#include "CPortalSummonEffectScript.h"
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim2D.h>
#include "CScriptLevelSaveLoad.h"
#include <Engine/CEventMgr.h>
#include "CPlayerScript.h"

CPortalSummonEffectScript::CPortalSummonEffectScript()
	:CScript((UINT)SCRIPT_TYPE::PORTALSUMMONEFFECTSCRIPT)
	,m_bAnimActive(false)
	,m_iPortalNum(0)
{
}

CPortalSummonEffectScript::~CPortalSummonEffectScript()
{
}



void CPortalSummonEffectScript::begin()
{
	MeshRender()->GetDynamicMaterial();
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, nullptr);
	Animator2D()->LoadAnim(L"animation\\particle\\PortalSummon.anim");

}
void CPortalSummonEffectScript::tick()
{
	if (m_bAnimActive) {
		if (m_iPortalNum == 0) assert(nullptr);

		if (Animator2D()->GetCurAnim()->IsFinish()) {
			if (m_iPortalNum == 1) {
				CLevel* pLoadedLevel = CScriptLevelSaveLoad::LoadLevel(L"level\\HomeLevel.lv");

				tEvent evn = {};
				evn.Type = EVENT_TYPE::LEVEL_CHANGE;
				evn.wParam = (DWORD_PTR)pLoadedLevel;

				CEventMgr::GetInst()->AddEvent(evn);
			}
			else if (m_iPortalNum == 2) {
				CLevel* pLoadedLevel = CScriptLevelSaveLoad::LoadLevel(L"level\\NormalLevel.lv");

				tEvent evn = {};
				evn.Type = EVENT_TYPE::LEVEL_CHANGE;
				evn.wParam = (DWORD_PTR)pLoadedLevel;

				CEventMgr::GetInst()->AddEvent(evn);
			}
			else if (m_iPortalNum == 3) {
				CLevel* pLoadedLevel = CScriptLevelSaveLoad::LoadLevel(L"level\\BossLevel.lv");

				tEvent evn = {};
				evn.Type = EVENT_TYPE::LEVEL_CHANGE;
				evn.wParam = (DWORD_PTR)pLoadedLevel;

				CEventMgr::GetInst()->AddEvent(evn);
			}
			else if (m_iPortalNum == 4) {
				CLevel* pLoadedLevel = CScriptLevelSaveLoad::LoadLevel(L"level\\MainMenu.lv");

				tEvent evn = {};
				evn.Type = EVENT_TYPE::LEVEL_CHANGE;
				evn.wParam = (DWORD_PTR)pLoadedLevel;

				CEventMgr::GetInst()->AddEvent(evn);
			}
			else {
				assert(nullptr);
			}
		}

	}
}


void CPortalSummonEffectScript::SaveToLevelFile(FILE* _File)
{
	fwrite(&m_iPortalNum, sizeof(int), 1, _File);
}

void CPortalSummonEffectScript::LoadFromLevelFile(FILE* _FILE)
{
	fread(&m_iPortalNum, sizeof(int), 1, _FILE);
	MeshRender()->GetDynamicMaterial();
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, nullptr);
	Animator2D()->LoadAnim(L"animation\\particle\\PortalSummon.anim");
}

void CPortalSummonEffectScript::Activate()
{
	m_bAnimActive = true;
	Animator2D()->Play(L"PortalSummon",false);
	CGameObject* Player = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"Player");
	CPlayerScript* PlayerScript = Player->GetScript<CPlayerScript>();
	PlayerScript->SetPlayerInfo();
}

