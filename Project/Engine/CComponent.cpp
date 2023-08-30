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
	// GameObject�� AddComponent �ʿ��� m_pOwner�� �������ش�.
	// ������, ��Ȯ�ϰ� �ϱ� ���� ��������� ���� ����._Component->m_pOwner = this;
}

CComponent::~CComponent()
{
}
