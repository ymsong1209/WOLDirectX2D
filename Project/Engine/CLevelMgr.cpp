#include "pch.h"
#include "CLevelMgr.h"

#include "CLevel.h"
#include "CLayer.h"

#include "CResMgr.h"
#include "CCollisionMgr.h"

#include "CGameObject.h"
#include "components.h"

#include "CDevice.h"
#include "CSetColorShader.h"



CLevelMgr::CLevelMgr()
	: m_pCurLevel(nullptr)
{
}

CLevelMgr::~CLevelMgr()
{
	if (nullptr != m_pCurLevel)
		delete m_pCurLevel;
}


void CLevelMgr::init()
{

	m_pCurLevel = new CLevel;
	m_pCurLevel->ChangeState(LEVEL_STATE::STOP);
	
}

void CLevelMgr::tick()
{
	m_pCurLevel->clear(); //Gameobject�� finaltick���� ��� layer����� ���� pushback�� �ϰ� �ִ�.

	if (LEVEL_STATE::PLAY == m_pCurLevel->GetState())
	{
		m_pCurLevel->tick();
	}

	m_pCurLevel->finaltick();
}

CGameObject* CLevelMgr::FindObjectByName(const wstring& _strName)
{
	return m_pCurLevel->FindObjectByName(_strName);
}

void CLevelMgr::FindObjectByName(const wstring& _strName, vector<CGameObject*>& _vec)
{
	m_pCurLevel->FindObjectByName(_strName, _vec);
}

CGameObject* CLevelMgr::FindParentObjectByName(const wstring& _strName)
{
	return m_pCurLevel->FindParentObjectByName(_strName);
}

void CLevelMgr::FindParentObjectByName(const wstring& _strName, vector<CGameObject*>& _Out)
{
	m_pCurLevel->FindParentObjectByName(_strName, _Out);
}

void CLevelMgr::ChangeLevel(CLevel* _NextLevel)
{
	if (nullptr != m_pCurLevel)
	{
		delete m_pCurLevel;
		m_pCurLevel = nullptr;
	}

	m_pCurLevel = _NextLevel;
}
