#include "pch.h"
#include "CSnowParticleScript.h"

#include <Engine/CResMgr.h>
#include <Engine/CParticleSystem.h>

#include <Engine/CKeyMgr.h>
#include <Engine/CTexture.h>
#include <Engine/CTimeMgr.h>



CSnowParticleScript::CSnowParticleScript()
	: CScript((UINT)SCRIPT_TYPE::SNOWPARTICLESCRIPT)
{
}

CSnowParticleScript::~CSnowParticleScript()
{
}

void CSnowParticleScript::tick()
{
	if (KEY_TAP(KEY::E)) {
		Ptr<CTexture> tex = CResMgr::GetInst()->Load<CTexture>(L"texture\\particle\\Snow50px.png", L"texture\\particle\\Snow50px.png");
		ParticleSystem()->SetParticleTexture(tex);

		m_ModuleData.iMaxParticleCount = 1000;

		m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::PARTICLE_SPAWN] = true;
		m_ModuleData.SpawnRate = 20;

		m_ModuleData.vSpawnColor = Vec4(1.f,1.f,1.f,1.f);

		m_ModuleData.vSpawnScaleMin = Vec3(15.f, 15.f, 1.f);
		m_ModuleData.vSpawnScaleMax = Vec3(50.f, 50.f, 1.f);

		m_ModuleData.SpawnShapeType = 0;
		m_ModuleData.vBoxShapeScale = Vec3(3000.f, 3000.f, 200.f);
		m_ModuleData.Space = 0; // ½Ã¹Ä·¹ÀÌ¼Ç ÁÂÇ¥°è

		m_ModuleData.MinLifeTime = 3.f;
		m_ModuleData.MaxLifeTime = 7.f;

		m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::SCALE_CHANGE] = false;
		m_ModuleData.StartScale = 2.0f;
		m_ModuleData.EndScale = 1.0f;

		m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::COLOR_CHANGE] = false;
		m_ModuleData.vStartColor = Vec3(1.0f, 1.f, 0.f);
		m_ModuleData.vEndColor = Vec3(1.f, 0.f, 0.f);


		m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::ADD_VELOCITY] = true;
		m_ModuleData.AddVelocityType = 2; // From Center
		m_ModuleData.Speed = 100.f;
		m_ModuleData.vVelocityDir = Vec4(0.f, -1.f, 0.f, 0.f);
		m_ModuleData.OffsetAngle = 0.f;

		m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::DRAG] = true;
		m_ModuleData.StartDrag = 100.f;
		m_ModuleData.EndDrag = 0.f;

		m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::NOISE_FORCE] = true;
		m_ModuleData.fNoiseTerm = 0.3f;
		m_ModuleData.fNoiseForce = 300.f;

		m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::RENDER] = true;
		m_ModuleData.VelocityAlignment = false;
		m_ModuleData.VelocityScale = false;
		m_ModuleData.vMaxVelocityScale = Vec3(10.f, 1.f, 1.f);
		m_ModuleData.vMaxSpeed = 50.f;
		m_ModuleData.bRotate = true;
		m_ModuleData.fRotateSpeed = 1.f;
		m_ModuleData.fRotationAngle = 2.f;

		ParticleSystem()->SetModuleData(m_ModuleData);
		//ParticleSystem()->GetModuleData() = m_ModuleData;
	}

}


void CSnowParticleScript::begin()
{

}