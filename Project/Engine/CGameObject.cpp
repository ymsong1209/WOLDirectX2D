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
	, m_iLayerIdx(-1)//layer에 배정받지 않음
	, m_bDead(false)
	, m_LifeTime(0.f)
	, m_CurLifeTime(0.f)
	, m_bLifeSpan(false)
{
}

//복사생성자
CGameObject::CGameObject(const CGameObject& _Other)
	: CEntity(_Other)//부모의복사생성자 호출 안하면 일반 생성자 호출
	, m_arrCom{}
	, m_RenderCom(nullptr)
	, m_Parent(nullptr)
	, m_iLayerIdx(-1)
	, m_bDead(false)
	, m_LifeTime(_Other.m_LifeTime)
	, m_CurLifeTime(_Other.m_CurLifeTime)
	, m_bLifeSpan(_Other.m_bLifeSpan)
{
	// Component 복사
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (_Other.m_arrCom[i] && i != (UINT)COMPONENT_TYPE::FSMCOM)
		{
			AddComponent(_Other.m_arrCom[i]->Clone());
		}
	}

	// Script 복사
	for (size_t i = 0; i < _Other.m_vecScript.size(); ++i)
	{
		AddComponent(_Other.m_vecScript[i]->Clone());
	}

	// FSM은 Script를 복사한 이후, 그 CurScript를 다시 찾아서 넣어야함.
	if (_Other.m_arrCom[(UINT)COMPONENT_TYPE::FSMCOM]) {
		AddComponent(_Other.m_arrCom[(UINT)COMPONENT_TYPE::FSMCOM]->Clone());
	}

	// 자식 오브젝트 복사
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


	// 소속 레이어가 없는데 finaltick 이 호출되었다.
	assert(-1 != m_iLayerIdx);

	// 레이어 등록
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

	// 컴포넌트가 스크립트인 경우
	if (COMPONENT_TYPE::SCRIPT == _Component->GetType())
	{
		m_vecScript.push_back((CScript*)_Component);
	}

	// 스크립트를 제외한 일반 컴포넌트인 경우
	else
	{
		// 이미 보유하고 있는 컴포넌트인 경우
		assert(!m_arrCom[(UINT)_Component->GetType()]);

		m_arrCom[(UINT)_Component->GetType()] = _Component;

		// RenderComponent 확인
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
		// 기존 부모가 있으면 연결 해제 후 연결
		_Object->DisconnectFromParent();
	}

	else
	{
		// 기존 부모가 없으면, 소속 레이어에서 최상위부모 목록에서 제거된 후 연결
		_Object->ChangeToChildType();
	}

	// 부모 자식 연결
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
		//최상위 부모는 m_parent가 nullptr이므로 while문 탈출
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
			//부모가 자식을 끊기
			m_Parent->m_vecChild.erase(iter);
			//자식은 부모에 nullptr를 밀어넣는다.
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

	//부모일 경우
	if (!m_Parent) {
		//Prefab Object
		
		
		//소속된 layer의 ParentObjlist에서 자기자신 제거
		CLayer* pLayer = CLevelMgr::GetInst()->GetCurLevel()->GetLayer(m_iLayerIdx);
		pLayer->RemoveFromParentList(this);
		m_iLayerIdx = _layeridx;
		pLayer = CLevelMgr::GetInst()->GetCurLevel()->GetLayer(m_iLayerIdx);
		pLayer->AddParentList(this);
	}
	//부모가 아닐 경우, index만 바꾸면 된다.
	else {
		m_iLayerIdx = _layeridx;
	}


}
