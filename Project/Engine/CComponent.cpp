#include "pch.h"
#include "CComponent.h"

CComponent::CComponent(COMPONENT_TYPE _Type)
	: m_pOwner(nullptr)
	, m_Type(_Type)
	, m_bActive(true)
{
}

CComponent::CComponent(const CComponent& _Other)
	: CEntity(_Other)
	, m_pOwner(nullptr)
	, m_Type(_Other.m_Type)
	, m_bActive(_Other.m_bActive)
{
	// GameObject의 AddComponent 쪽에서 m_pOwner를 지정해준다.
	// 하지만, 정확하게 하기 위해 복사생성자 따로 만듬._Component->m_pOwner = this;
}

CComponent::~CComponent()
{
}
