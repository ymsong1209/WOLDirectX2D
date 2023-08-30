#include "pch.h"
#include "CMageBallAfterImageScript.h"


CMageBallAfterImageScript::CMageBallAfterImageScript()
	:CScript((UINT)SCRIPT_TYPE::MAGEBALLAFTERIMAGESCRIPT)
{

}

CMageBallAfterImageScript::~CMageBallAfterImageScript()
{
}


void CMageBallAfterImageScript::begin()
{
	m_vOutlineColor = Vec4(0.f, 0.f, 0.f, 0.f);
	m_fLifeTime = GetOwner()->GetLifeSpan();
}

void CMageBallAfterImageScript::tick()
{
	if (!IsActive()) return;
	float Curlife = GetOwner()->GetCurLifeSpan();
	m_fAlphaPerLife = Curlife / m_fLifeTime;
	MeshRender()->GetMaterial()->SetScalarParam(VEC4_0, &m_vOutlineColor);
	MeshRender()->GetMaterial()->SetScalarParam(FLOAT_0, &m_fAlphaPerLife);
}
