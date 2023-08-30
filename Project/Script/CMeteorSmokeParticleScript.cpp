#include "pch.h"
#include "CMeteorSmokeParticleScript.h"
CMeteorSmokeParticleScript::CMeteorSmokeParticleScript()
	:CScript((UINT)SCRIPT_TYPE::METEORSMOKEPARTICLESCRIPT)
	, m_fTime(0.f)
{
}

CMeteorSmokeParticleScript::~CMeteorSmokeParticleScript()
{
}

void CMeteorSmokeParticleScript::begin()
{
	SetLifeSpan(5.f);
	Vec3 Pos = Transform()->GetRelativePos();
	Transform()->SetRelativePos(Vec3(Pos.x, Pos.y, 20.f));

}

void CMeteorSmokeParticleScript::tick()
{
	m_fTime += DT;
	if (m_fTime > 1.f) {
		tParticleModule ParticleModule =  ParticleSystem()->GetModuleData();
		ParticleModule.ModuleCheck[(UINT)PARTICLE_MODULE::PARTICLE_SPAWN] = false;
		ParticleSystem()->SetModuleData(ParticleModule);
	}
}
