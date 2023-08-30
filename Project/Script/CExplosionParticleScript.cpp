#include "pch.h"
#include "CExplosionParticleScript.h"

#include <Engine/CResMgr.h>
#include <Engine/CParticleSystem.h>

#include <Engine/CKeyMgr.h>
#include <Engine/CTexture.h>
#include <Engine/CTimeMgr.h>




CExplosionParticleScript::CExplosionParticleScript()
	: CScript((UINT)SCRIPT_TYPE::EXPLOSIONPARTICLESCRIPT)
	, m_btime(false)

{
}

CExplosionParticleScript::~CExplosionParticleScript()
{
}

void CExplosionParticleScript::tick()
{
	if (m_btime) {
		m_ftime += DT;
		if (m_ftime > 1.f) {
			m_btime = false;
			m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::PARTICLE_SPAWN] = false;
			m_ftime = 0.f;
		}
	}
	
	if (KEY_TAP(KEY::E)) {
		m_btime = true;
		Ptr<CTexture> tex = CResMgr::GetInst()->Load<CTexture>(L"texture\\particle\\filledsquare.png", L"texture\\particle\\filledsquare.png");
		ParticleSystem()->SetParticleTexture(tex);

		m_ModuleData.iMaxParticleCount = 1000;

		m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::PARTICLE_SPAWN] = true;
		m_ModuleData.SpawnRate = 100;

		m_ModuleData.vSpawnColor = Vec3(4.f / 250.f, 40.f / 255.f, 250.f / 255.f);

		m_ModuleData.vSpawnScaleMin = Vec3(10.f, 10.f, 1.f);
		m_ModuleData.vSpawnScaleMax = Vec3(20.f, 20.f, 1.f);

		m_ModuleData.SpawnShapeType = 0;
		m_ModuleData.vBoxShapeScale = Vec3(20.f, 20.f, 200.f);
		m_ModuleData.Space = 0; // ½Ã¹Ä·¹ÀÌ¼Ç ÁÂÇ¥°è

		m_ModuleData.MinLifeTime = 1.f;
		m_ModuleData.MaxLifeTime = 3.f;

		m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::SCALE_CHANGE] = false;
		m_ModuleData.StartScale = 2.0f;
		m_ModuleData.EndScale = 1.0f;

		m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::COLOR_CHANGE] = true;
		m_ModuleData.vStartColor = Vec4(1.0f, 0.f, 0.f,1.f);
		m_ModuleData.vEndColor = Vec4(248.f/255.f, 86.f/255.f, 86.f/255.f,1.f);


		m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::ADD_VELOCITY] = true;
		m_ModuleData.AddVelocityType = 0; // From Center
		m_ModuleData.Speed = 100.f;
		m_ModuleData.vVelocityDir = Vec4(-0.3f, -0.9f, 0.f, 0.f);
		m_ModuleData.OffsetAngle = 50.f;

		m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::DRAG] = true;
		m_ModuleData.StartDrag = 100.f;
		m_ModuleData.EndDrag = 0.f;

		m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::NOISE_FORCE] = false;
		m_ModuleData.fNoiseTerm = 0.3f;
		m_ModuleData.fNoiseForce = 50.f;

		m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::RENDER] = true;
		m_ModuleData.VelocityAlignment = false;
		m_ModuleData.VelocityScale = false;
		m_ModuleData.vMaxVelocityScale = Vec3(10.f, 1.f, 1.f);
		m_ModuleData.vMaxSpeed = 50.f;
		m_ModuleData.bRotate = false;
		m_ModuleData.fRotateSpeed = 1.f;
		m_ModuleData.fRotationAngle = 2.f;

		
		//ParticleSystem()->GetModuleData() = m_ModuleData;
	}
	ParticleSystem()->SetModuleData(m_ModuleData);
}


void CExplosionParticleScript::begin()
{

}

