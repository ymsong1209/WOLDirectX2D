#include "pch.h"
#include "CPortalParticleScript.h"

CPortalParticleScript::CPortalParticleScript()
	:CScript((UINT)SCRIPT_TYPE::PORTALPARTICLESCRIPT)
	,m_bPortalActivated(false)
{
}

CPortalParticleScript::~CPortalParticleScript()
{
}


void CPortalParticleScript::tick()
{
	if (m_bPortalActivated) {
		tParticleModule ModuleData = ParticleSystem()->GetModuleData();
		ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::PARTICLE_SPAWN] = false;
		ParticleSystem()->SetModuleData(ModuleData);
	}
}

void CPortalParticleScript::begin()
{
	m_bPortalActivated = false;
	tParticleModule ModuleData = ParticleSystem()->GetModuleData();
	ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::PARTICLE_SPAWN] = false;
	ParticleSystem()->SetModuleData(ModuleData);
}

void CPortalParticleScript::BeginOverlap(CCollider2D* _Other)
{
	if (m_bPortalActivated) return;
	tParticleModule ModuleData = ParticleSystem()->GetModuleData();
	ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::PARTICLE_SPAWN] = true;
	ParticleSystem()->SetModuleData(ModuleData);

	Ptr<CSound> sound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\PortalShine.wav");
	sound->Play(1, 0.2, false);
}

void CPortalParticleScript::OnOverlap(CCollider2D* _Other)
{
	if (m_bPortalActivated) return;
	tParticleModule ModuleData = ParticleSystem()->GetModuleData();
	ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::PARTICLE_SPAWN] = true;
	ParticleSystem()->SetModuleData(ModuleData);
}

void CPortalParticleScript::EndOverlap(CCollider2D* _Other)
{
	if (m_bPortalActivated) return;
	tParticleModule ModuleData = ParticleSystem()->GetModuleData();
	ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::PARTICLE_SPAWN] = false;
	ParticleSystem()->SetModuleData(ModuleData);
}

void CPortalParticleScript::SaveToLevelFile(FILE* _File)
{
}

void CPortalParticleScript::LoadFromLevelFile(FILE* _FILE)
{
}

void CPortalParticleScript::Activate()
{
	m_bPortalActivated = true;
	tParticleModule ModuleData = ParticleSystem()->GetModuleData();
	ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::PARTICLE_SPAWN] = false;
	ParticleSystem()->SetModuleData(ModuleData);
}


