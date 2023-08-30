#include "pch.h"
#include "CFSM.h"

#include "CScript.h"

CFSM::CFSM()
	: CComponent(COMPONENT_TYPE::FSMCOM)
	, m_pCurScript(nullptr)
{
}

CFSM::CFSM(const CFSM& _other)
	: CComponent(COMPONENT_TYPE::FSMCOM)
{
	if (_other.m_pCurScript != nullptr) {
		CScript* NextScript = FindScript(_other.m_pCurScript->GetScriptType());
		m_pCurScript = NextScript;
	}
	
}

CFSM::~CFSM()
{
}


void CFSM::finaltick()
{
}

CScript* CFSM::FindScript(UINT _ScriptType)
{
	const vector<CScript*>& vecScript = GetOwner()->GetScripts();
	for (UINT i = 0; i < vecScript.size(); ++i) {
		if (vecScript[i]->GetScriptType() == _ScriptType) return vecScript[i];
	}
	return nullptr;
}

void CFSM::ChangeState(UINT _ScriptType, bool _isRepeat)
{
	CScript* pNextState = FindScript(_ScriptType);
	if (pNextState == nullptr)
	{
		wstring str = L"NextState가 없습니다. Script UINT : " + _ScriptType;
		wchar_t szStr[256] = {};
		wsprintf(szStr, str.c_str());
		MessageBox(nullptr, szStr, L"FSM전환 실패.", MB_OK);
	}
	assert(pNextState);
	//같은 script가 연속으로 들어왔는데 고의적으로 들어온게 아닌경우
	if (m_pCurScript == pNextState && _isRepeat == false) return;

	if (nullptr != m_pCurScript) {
		m_pCurScript->Exit();
		m_pCurScript->SetActive(false);
	}
		

	m_pCurScript = pNextState;

	pNextState->Enter();
	pNextState->SetActive(true);
}



void CFSM::SaveToLevelFile(FILE* _File)
{
	/*if (m_pCurScript) {
		int i = 1;
		fwrite(&i, sizeof(int), 1, _File);
		UINT ScriptType = m_pCurScript->GetScriptType();
		fwrite(&ScriptType, sizeof(UINT), 1, _File);
	}
	else {
		int i = 0;
		fwrite(&i, sizeof(int), 1, _File);
	}*/
	
	
}

void CFSM::LoadFromLevelFile(FILE* _File)
{
	/*int CurScript;
	fread(&CurScript, sizeof(int), 1, _File);
	if (CurScript == 1) {
		UINT ScriptType;
		fread(&ScriptType, sizeof(UINT), 1, _File);
		CScript* NextScript = FindScript(ScriptType);
		m_pCurScript = NextScript;
	}*/
	
}
