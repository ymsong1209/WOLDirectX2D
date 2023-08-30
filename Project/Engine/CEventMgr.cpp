#include "pch.h"
#include "CEventMgr.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CGameObject.h"

#include "CResMgr.h"
#include "CRenderMgr.h"
#include "CFSM.h"
#include "CSound.h"

CEventMgr::CEventMgr()
{

}

CEventMgr::~CEventMgr()
{

}

// EventMgr�� Render�� ������ ����ȴ�.
// �� frame���� tick���� object���� �����Ǳ� ������ �̹� �����ӿ��� ���ุ �ص���.
void CEventMgr::tick()
{
	m_LevelChanged = false;
	GC_Clear();


	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		switch (m_vecEvent[i].Type)
		{
			// wParam : GameObject, lParam : Layer Index
		case EVENT_TYPE::CREATE_OBJECT:
		{
			CGameObject* NewObject = (CGameObject*)m_vecEvent[i].wParam;
			int iLayerIdx = (int)m_vecEvent[i].lParam;

			CLevelMgr::GetInst()->GetCurLevel()->AddGameObject(NewObject, iLayerIdx, false);

			if (CLevelMgr::GetInst()->GetCurLevel()->GetState() == LEVEL_STATE::PLAY)
			{
				NewObject->begin();
			}

			m_LevelChanged = true;
		}
		break;
		case EVENT_TYPE::DELETE_OBJECT:
		{
			CGameObject* DeleteObject = (CGameObject*)m_vecEvent[i].wParam;

			//�� �����ӿ� ���������� delete ȣ���� ����� ���
			if (false == DeleteObject->m_bDead)
			{
				DeleteObject->m_bDead = true;
				m_vecGC.push_back(DeleteObject);
			}

			
		}

			break;
		case EVENT_TYPE::ADD_CHILD:
			// wParam : ParentObject, lParam : ChildObject
		{
			CGameObject* pDestObj = (CGameObject*)m_vecEvent[i].wParam;
			CGameObject* pSrcObj = (CGameObject*)m_vecEvent[i].lParam;

			// �θ�� ������ ������Ʈ�� ������, Child ������Ʈ�� �ֻ��� �θ� ������Ʈ�� �ȴ�.
			if (nullptr == pDestObj)
			{
				if (pSrcObj->GetParent())
				{
					// ���� �θ���� ���� ����
					pSrcObj->DisconnectFromParent();
					// �ֻ��� �θ� ������Ʈ��, �Ҽ� ���̾ ���
					pSrcObj->AddParentList();
				}
			}
			else
			{
				pDestObj->AddChild(pSrcObj);
			}

			m_LevelChanged = true;

		}

			break;
		case EVENT_TYPE::DELETE_RESOURCE:
			// wParam : RES_TYPE, lParam : Resource Adress
		{
			RES_TYPE type = (RES_TYPE)m_vecEvent[i].wParam;
			CRes* pRes = (CRes*)m_vecEvent[i].lParam;
			CResMgr::GetInst()->DeleteRes(type, pRes->GetKey());
		}

		break;
		case EVENT_TYPE::LEVEL_CHANGE:
		{
			// wParam : Level Adress
			CLevel* Level = (CLevel*)m_vecEvent[i].wParam;
			CLevel* CurLevel = CLevelMgr::GetInst()->GetCurLevel();
			bool IsPlay = false;
			if (CurLevel != nullptr) {
				if (CurLevel->GetState() == LEVEL_STATE::PLAY) {
					IsPlay = true;
				}
			}
			CLevelMgr::GetInst()->ChangeLevel(Level);
			CRenderMgr::GetInst()->ClearCamera();

			m_LevelChanged = true;

			const map<wstring, Ptr<CRes>> SoundRes = CResMgr::GetInst()->GetResources(RES_TYPE::SOUND);
			for (const auto& kv : SoundRes) {
				Ptr<CRes> Res = kv.second;
				((CSound*)Res.Get())->Stop();
			}

			if (IsPlay) {
				CLevelMgr::GetInst()->GetCurLevel()->ChangeState(LEVEL_STATE::PLAY);
			}
		}
			break;

		case EVENT_TYPE::CHANGE_AI_STATE:
		{
			// wParam : AI Component Address, lParam : UINT scriptType, CustomParam : bool isRepeat
			CComponent* pAI = (CComponent*)m_vecEvent[i].wParam;
			UINT ScriptType = (UINT)m_vecEvent[i].lParam;
			bool Repeat = (bool)m_vecEvent[i].CustomParam;
			((CFSM*)pAI)->ChangeState(ScriptType, Repeat);
		}

		break;
		}

		
	}

	m_vecEvent.clear();
}

void CEventMgr::GC_Clear()
{
	for (size_t i = 0; i < m_vecGC.size(); ++i)
	{
		if (nullptr != m_vecGC[i])
		{
			// �ڽ� Ÿ�� ������Ʈ�� ���
			if (m_vecGC[i]->GetParent())
				m_vecGC[i]->DisconnectFromParent();

			delete m_vecGC[i];

			m_LevelChanged = true;
		}
	}
	m_vecGC.clear();
}