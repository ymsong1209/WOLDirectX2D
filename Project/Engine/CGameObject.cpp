#include "pch.h"
#include "CGameObject.h"

#include "CComponent.h"
#include "CMeshRender.h"
#include "CScript.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLayer.h"

CGameObject::CGameObject()
	: m_arrCom{}
	, m_RenderCom(nullptr)
	, m_Parent(nullptr)
	, m_iLayerIdx(-1)//layer�� �������� ����
	, m_bDead(false)
	, m_LifeTime(0.f)
	, m_CurLifeTime(0.f)
	, m_bLifeSpan(false)
{
}

//���������
CGameObject::CGameObject(const CGameObject& _Other)
	: CEntity(_Other)//�θ��Ǻ�������� ȣ�� ���ϸ� �Ϲ� ������ ȣ��
	, m_arrCom{}
	, m_RenderCom(nullptr)
	, m_Parent(nullptr)
	, m_iLayerIdx(-1)
	, m_bDead(false)
	, m_LifeTime(_Other.m_LifeTime)
	, m_CurLifeTime(_Other.m_CurLifeTime)
	, m_bLifeSpan(_Other.m_bLifeSpan)
{
	// Component ����
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (_Other.m_arrCom[i] && i != (UINT)COMPONENT_TYPE::FSMCOM)
		{
			AddComponent(_Other.m_arrCom[i]->Clone());
		}
	}

	// Script ����
	for (size_t i = 0; i < _Other.m_vecScript.size(); ++i)
	{
		AddComponent(_Other.m_vecScript[i]->Clone());
	}

	// FSM�� Script�� ������ ����, �� CurScript�� �ٽ� ã�Ƽ� �־����.
	if (_Other.m_arrCom[(UINT)COMPONENT_TYPE::FSMCOM]) {
		AddComponent(_Other.m_arrCom[(UINT)COMPONENT_TYPE::FSMCOM]->Clone());
	}

	// �ڽ� ������Ʈ ����
	for (size_t i = 0; i < _Other.m_vecChild.size(); ++i)
	{
		AddChild(_Other.m_vecChild[i]->Clone());
	}
}



CGameObject::~CGameObject()
{
	/*for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr != m_arrCom[i])
			delete m_arrCom[i];
	}*/

	Safe_Del_Array(m_arrCom);
	Safe_Del_Vec(m_vecScript);
	Safe_Del_Vec(m_vecChild);
}

void CGameObject::begin()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr != m_arrCom[i])
			m_arrCom[i]->begin();
	}

	for (size_t i = 0; i < m_vecScript.size(); ++i)
	{
		m_vecScript[i]->begin();
	}

	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->begin();
	}
}

void CGameObject::tick()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr != m_arrCom[i])
			m_arrCom[i]->tick();
	}

	for (size_t i = 0; i < m_vecScript.size(); ++i)
	{
		m_vecScript[i]->tick();
	}

	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->tick();
	}
}

void CGameObject::finaltick()
{
	if (m_bLifeSpan)
	{
		m_CurLifeTime += DT;
		if (m_LifeTime < m_CurLifeTime)
		{
			DestroyObject(this);
		}
	}


	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::SCRIPT; ++i)
	{
		if (nullptr != m_arrCom[i])
			m_arrCom[i]->finaltick();
	}


	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->finaltick();
	}


	// �Ҽ� ���̾ ���µ� finaltick �� ȣ��Ǿ���.
	assert(-1 != m_iLayerIdx);

	// ���̾� ���
	CLayer* pCurLayer = CLevelMgr::GetInst()->GetCurLevel()->GetLayer(m_iLayerIdx);
	pCurLayer->RegisterObject(this);

}

void CGameObject::render()
{
	if (nullptr != m_RenderCom)
		m_RenderCom->render();
}

void CGameObject::AddComponent(CComponent* _Component)
{
	_Component->m_pOwner = this;

	// ������Ʈ�� ��ũ��Ʈ�� ���
	if (COMPONENT_TYPE::SCRIPT == _Component->GetType())
	{
		m_vecScript.push_back((CScript*)_Component);
	}

	// ��ũ��Ʈ�� ������ �Ϲ� ������Ʈ�� ���
	else
	{
		// �̹� �����ϰ� �ִ� ������Ʈ�� ���
		assert(!m_arrCom[(UINT)_Component->GetType()]);

		m_arrCom[(UINT)_Component->GetType()] = _Component;

		// RenderComponent Ȯ��
		if (COMPONENT_TYPE::MESHRENDER <= _Component->GetType()
			&& _Component->GetType() <= COMPONENT_TYPE::DECAL)
		{
			assert(!m_RenderCom);
			m_RenderCom = (CRenderComponent*)_Component;
		}
	}
}

void CGameObject::AddChild(CGameObject* _Object)
{

	if (_Object->m_Parent)
	{
		// ���� �θ� ������ ���� ���� �� ����
		_Object->DisconnectFromParent();
	}

	else
	{
		// ���� �θ� ������, �Ҽ� ���̾�� �ֻ����θ� ��Ͽ��� ���ŵ� �� ����
		_Object->ChangeToChildType();
	}

	// �θ� �ڽ� ����
	_Object->m_Parent = this;
	m_vecChild.push_back(_Object);
}

bool CGameObject::IsAncestor(CGameObject* _Target)
{
	CGameObject* pParent = m_Parent;
	while (pParent)
	{
		if (pParent == _Target)
		{
			return true;
		}
		//�ֻ��� �θ�� m_parent�� nullptr�̹Ƿ� while�� Ż��
		pParent = pParent->m_Parent;
	}

	return false;
}



void CGameObject::DisconnectFromParent()
{
	if (!m_Parent)
		return;

	vector<CGameObject*>::iterator iter = m_Parent->m_vecChild.begin();
	for (; iter != m_Parent->m_vecChild.end(); ++iter)
	{
		if (this == *iter)
		{
			//�θ� �ڽ��� ����
			m_Parent->m_vecChild.erase(iter);
			//�ڽ��� �θ� nullptr�� �о�ִ´�.
			m_Parent = nullptr;
			return;
		}
	}

	assert(nullptr);
}
void CGameObject::ChangeToChildType()
{
	assert(-1 <= m_iLayerIdx && m_iLayerIdx < MAX_LAYER);

	if (-1 != m_iLayerIdx)
	{
		CLayer* pLayer = CLevelMgr::GetInst()->GetCurLevel()->GetLayer(m_iLayerIdx);
		pLayer->RemoveFromParentList(this);
	}
}

void CGameObject::AddParentList()
{
	CLayer* pLayer = CLevelMgr::GetInst()->GetCurLevel()->GetLayer(m_iLayerIdx);
	pLayer->AddParentList(this);
}

void CGameObject::SetLayerIndex(int _layeridx)
{
	assert(-1 <= _layeridx && _layeridx < MAX_LAYER);
	if (_layeridx == m_iLayerIdx) return;

	
	if (m_iLayerIdx == -1) {
		m_iLayerIdx = _layeridx;
		return;
	}

	//�θ��� ���
	if (!m_Parent) {
		//Prefab Object
		
		
		//�Ҽӵ� layer�� ParentObjlist���� �ڱ��ڽ� ����
		CLayer* pLayer = CLevelMgr::GetInst()->GetCurLevel()->GetLayer(m_iLayerIdx);
		pLayer->RemoveFromParentList(this);
		m_iLayerIdx = _layeridx;
		pLayer = CLevelMgr::GetInst()->GetCurLevel()->GetLayer(m_iLayerIdx);
		pLayer->AddParentList(this);
	}
	//�θ� �ƴ� ���, index�� �ٲٸ� �ȴ�.
	else {
		m_iLayerIdx = _layeridx;
	}


}
