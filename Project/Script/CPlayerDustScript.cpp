#include "pch.h"
#include "CPlayerDustScript.h"
#include <Engine/CParticleSystem.h>

CPlayerDustScript::CPlayerDustScript()
	:CScript((UINT)SCRIPT_TYPE::PLAYERDUSTSCRIPT)
{
}

CPlayerDustScript::~CPlayerDustScript()
{
}


void CPlayerDustScript::begin()
{
}

void CPlayerDustScript::tick()
{
}

void CPlayerDustScript::ActivateDust()
{
	tParticleModule Dustmodule = ParticleSystem()->GetModuleData();
	Dustmodule.ModuleCheck[(UINT)PARTICLE_MODULE::PARTICLE_SPAWN] = true;
	ParticleSystem()->SetModuleData(Dustmodule);
}

void CPlayerDustScript::DeActivateDust()
{
	tParticleModule Dustmodule = ParticleSystem()->GetModuleData();
	Dustmodule.ModuleCheck[(UINT)PARTICLE_MODULE::PARTICLE_SPAWN] = false;
	ParticleSystem()->SetModuleData(Dustmodule);
}


