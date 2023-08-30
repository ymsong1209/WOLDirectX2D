#include "pch.h"
#include "CFireParticleScript.h"


#include <Engine/CResMgr.h>
#include <Engine/CParticleSystem.h>

#include <Engine/CKeyMgr.h>
#include <Engine/CTexture.h>
#include <Engine/CTimeMgr.h>
#include <Engine/CAnimator2D.h>



CFireParticleScript::CFireParticleScript()
	: CScript((UINT)SCRIPT_TYPE::FIREPARTICLESCRIPT)
{
}

CFireParticleScript::~CFireParticleScript()
{
}

void CFireParticleScript::tick()
{
	if (KEY_TAP(KEY::E)) {
		//Ptr<CTexture> tex = CResMgr::GetInst()->Load<CTexture>(L"Particle_0", L"texture\\particle\\AlphaCircle.png");
		Ptr<CTexture> tex = CResMgr::GetInst()->Load<CTexture>(L"texture\\particle\\FireParticles.png", L"texture\\particle\\FireParticles.png");
		
		ParticleSystem()->SetParticleTexture(tex);

		m_ModuleData.iMaxParticleCount = 1000;

		m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::PARTICLE_SPAWN] = true;
		m_ModuleData.SpawnRate = 20;

		m_ModuleData.vSpawnColor = Vec3(0.4f, 1.f, 0.4f);

		m_ModuleData.vSpawnScaleMin = Vec3(15.f, 15.f, 1.f);
		m_ModuleData.vSpawnScaleMax = Vec3(50.f, 50.f, 1.f);

		m_ModuleData.SpawnShapeType = 0;
		m_ModuleData.vBoxShapeScale = Vec3(20.f, 20.f, 200.f);
		m_ModuleData.Space = 0; // ½Ã¹Ä·¹ÀÌ¼Ç ÁÂÇ¥°è

		m_ModuleData.MinLifeTime = 1.f;
		m_ModuleData.MaxLifeTime = 3.f;

		m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::SCALE_CHANGE] = true;
		m_ModuleData.StartScale = 2.0f;
		m_ModuleData.EndScale = 1.0f;

		m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::COLOR_CHANGE] = true;
		m_ModuleData.vStartColor = Vec4(1.0f, 1.f, 0.f,1.f);
		m_ModuleData.vEndColor = Vec4(1.f, 0.f, 0.f,1.f);


		m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::ADD_VELOCITY] = true;
		m_ModuleData.AddVelocityType = 2; // From Center
		m_ModuleData.Speed = 100.f;
		m_ModuleData.vVelocityDir = Vec4(0.f, -1.f, 0.f, 0.f);
		m_ModuleData.OffsetAngle = 100.f;

		m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::DRAG] = true;
		m_ModuleData.StartDrag = 100.f;
		m_ModuleData.EndDrag = 0.f;

		m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::NOISE_FORCE] = false;
		m_ModuleData.fNoiseTerm = 0.3f;
		m_ModuleData.fNoiseForce = 50.f;

		m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::RENDER] = true;
		m_ModuleData.VelocityAlignment = false;
		m_ModuleData.VelocityScale = false;
		m_ModuleData.vMaxVelocityScale = Vec3(20.f, 1.f, 1.f);
		m_ModuleData.vMaxSpeed = 50.f;
		m_ModuleData.bRotate = false;
		m_ModuleData.fRotateSpeed = 10.f;
		m_ModuleData.fRotationAngle = 30.f;

		m_ModuleData.AnimationUse = 1;
		m_ModuleData.AnimationLoop = 0;
		m_ModuleData.iAnimXCount = 6;
		m_ModuleData.iAnimYCount = 4;
		m_ModuleData.fAnimFrmTime = 1.f;
		ParticleSystem()->SetModuleData(m_ModuleData);
	}
	
}


void CFireParticleScript::begin()
{
	
}


