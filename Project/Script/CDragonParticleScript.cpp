#include "pch.h"
#include "CDragonParticleScript.h"


CDragonParticleScript::CDragonParticleScript()
	:CScript((UINT)SCRIPT_TYPE::DRAGONPARTICLESCRIPT)
	, m_fWaitTime(0.f)
{
}

CDragonParticleScript::~CDragonParticleScript()
{
}

void CDragonParticleScript::begin()
{
}

void CDragonParticleScript::tick()
{
	m_fWaitTime -= DT;
	tParticleModule Module = ParticleSystem()->GetModuleData();
	if (m_fWaitTime > 0.f) {
		Module.SpawnRate = 0;
		ParticleSystem()->SetModuleData(Module);
		return;
	}
	else {
		Module.SpawnRate = 4;
		ParticleSystem()->SetModuleData(Module);
	}
	Vec3 ParentRot = GetOwner()->GetParent()->Transform()->GetRelativeRot();
	m_fAngle = ParentRot.z;

	
	Module.fRotationAngle = m_fAngle;
	ParticleSystem()->SetModuleData(Module);
}

