#include "pch.h"
#include "CPlayerAfterImageScript.h"


CPlayerAfterImageScript::CPlayerAfterImageScript()
	: CScript((UINT)SCRIPT_TYPE::PLAYERAFTERIMAGESCRIPT)
{
	m_vOutlineColor = Vec4(1.0f, 212.0f / 255.0f, 0.0f, 1.0f);
	m_vCapeColor = Vec4(1.0f, 0.0f, 0.0f, 1.0f);
	AddScriptParam(SCRIPT_PARAM::VEC4, &m_vOutlineColor, "OutlineColor");
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fAlphaPerLife, "AlphaPerLife");
	AddScriptParam(SCRIPT_PARAM::VEC4, &m_vCapeColor, "CapeColor");
}

CPlayerAfterImageScript::CPlayerAfterImageScript(const CPlayerAfterImageScript& _other)
	: CScript((UINT)SCRIPT_TYPE::PLAYERAFTERIMAGESCRIPT)
	, m_vOutlineColor(_other.m_vOutlineColor)
{
	AddScriptParam(SCRIPT_PARAM::VEC4, &m_vOutlineColor, "OutlineColor");
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fAlphaPerLife, "AlphaPerLife");
	AddScriptParam(SCRIPT_PARAM::VEC4, &m_vCapeColor, "CapeColor");
}


CPlayerAfterImageScript::~CPlayerAfterImageScript()
{
}


void CPlayerAfterImageScript::begin()
{
	m_fLifeTime = GetOwner()->GetLifeSpan();
}

void CPlayerAfterImageScript::tick()
{
	if (!IsActive()) return;
	float Curlife = GetOwner()->GetCurLifeSpan();
	m_fAlphaPerLife = Curlife / m_fLifeTime;
	MeshRender()->GetMaterial()->SetScalarParam(VEC4_0, &m_vOutlineColor);
	MeshRender()->GetMaterial()->SetScalarParam(FLOAT_0, &m_fAlphaPerLife);
	MeshRender()->GetMaterial()->SetScalarParam(VEC4_1, &m_vCapeColor);
	
}

void CPlayerAfterImageScript::Enter()
{
}

void CPlayerAfterImageScript::Exit()
{
}

