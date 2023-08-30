#include "pch.h"
#include "CRainParticleScript.h"
#include <Engine/CResMgr.h>
#include <Engine/CParticleSystem.h>

#include <Engine/CKeyMgr.h>
#include <Engine/CTexture.h>
#include <Engine/CTimeMgr.h>




CRainParticleScript::CRainParticleScript()
  :CScript((UINT)SCRIPT_TYPE::RAINPARTICLESCRIPT)
{
}

CRainParticleScript::~CRainParticleScript()
{
}

void CRainParticleScript::tick()
{
	if (KEY_TAP(KEY::E)) {
		Ptr<CTexture> tex = CResMgr::GetInst()->Load<CTexture>(L"texture\\particle\\HardRain.png", L"texture\\particle\\HardRain.png");
		ParticleSystem()->SetParticleTexture(tex);

		m_ModuleData.iMaxParticleCount = 1000;

		m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::PARTICLE_SPAWN] = true;
		m_ModuleData.SpawnRate = 50;

		m_ModuleData.vSpawnColor = Vec4(4.f / 250.f, 40.f / 255.f, 250.f / 255.f,1.f);

		m_ModuleData.vSpawnScaleMin = Vec3(15.f, 15.f, 1.f);
		m_ModuleData.vSpawnScaleMax = Vec3(50.f, 50.f, 1.f);

		m_ModuleData.SpawnShapeType = 0;
		m_ModuleData.vBoxShapeScale = Vec3(3000.f, 3000.f, 200.f);
		m_ModuleData.Space = 0; // ½Ã¹Ä·¹ÀÌ¼Ç ÁÂÇ¥°è

		m_ModuleData.MinLifeTime = 1.f;
		m_ModuleData.MaxLifeTime = 3.f;

		m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::SCALE_CHANGE] = false;
		m_ModuleData.StartScale = 2.0f;
		m_ModuleData.EndScale = 1.0f;

		m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::COLOR_CHANGE] = false;
		m_ModuleData.vStartColor = Vec4(1.0f, 1.f, 0.f,1.f);
		m_ModuleData.vEndColor = Vec4(1.f, 0.f, 0.f,1.f);


		m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::ADD_VELOCITY] = true;
		m_ModuleData.AddVelocityType = 2; // From Center
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
		m_ModuleData.VelocityAlignment = true;
		m_ModuleData.VelocityScale = true;
		m_ModuleData.vMaxVelocityScale = Vec3(10.f, 1.f, 1.f);
		m_ModuleData.vMaxSpeed = 50.f;
		m_ModuleData.bRotate = false;
		m_ModuleData.fRotateSpeed = 10.f;
		m_ModuleData.fRotationAngle = 30.f;

		ParticleSystem()->SetModuleData(m_ModuleData);
		//ParticleSystem()->GetModuleData() = m_ModuleData;
	}

}


void CRainParticleScript::begin()
{

}

