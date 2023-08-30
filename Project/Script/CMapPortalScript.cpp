#include "pch.h"
#include "CMapPortalScript.h"
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim2D.h>
#include "CScriptLevelSaveLoad.h"
#include <Engine/CEventMgr.h>
#include "CPortalParticleScript.h"
#include "CPortalSummonEffectScript.h"

CMapPortalScript::CMapPortalScript()
	:CScript((UINT)SCRIPT_TYPE::MAPPORTALSCRIPT)
	, m_iPortalNum(0)
	, m_bPortalActivated(false)
{
	AddScriptParam(SCRIPT_PARAM::INT, &m_iPortalNum, "PortalNum");
}

CMapPortalScript::~CMapPortalScript()
{
}

void CMapPortalScript::tick()
{
}

void CMapPortalScript::begin()
{
	MeshRender()->GetDynamicMaterial();
	Ptr<CTexture> PortalTex = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\particles\\Teleport.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, PortalTex);
}

void CMapPortalScript::BeginOverlap(CCollider2D* _Other)
{
	if (m_iPortalNum == 0) assert(nullptr);
	if (m_bPortalActivated) return;
	if (KEY_TAP(KEY::ENTER)) {
		if (m_iPortalNum == 1) {
			CGameObject* SummonEffect = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"PortalSummonEffect");
			CPortalSummonEffectScript* Script = SummonEffect->GetScript<CPortalSummonEffectScript>();
			Script->SetPortalNum(1);
			Script->Activate();
		}
		else if(m_iPortalNum == 2) {
			CGameObject* SummonEffect = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"PortalSummonEffect");
			CPortalSummonEffectScript* Script = SummonEffect->GetScript<CPortalSummonEffectScript>();
			Script->SetPortalNum(2);
			Script->Activate();
		}
		else if (m_iPortalNum == 3) {
			CGameObject* SummonEffect = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"PortalSummonEffect");
			CPortalSummonEffectScript* Script = SummonEffect->GetScript<CPortalSummonEffectScript>();
			Script->SetPortalNum(3);
			Script->Activate();
		}
		else if (m_iPortalNum == 4) {
			CGameObject* SummonEffect = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"PortalSummonEffect");
			CPortalSummonEffectScript* Script = SummonEffect->GetScript<CPortalSummonEffectScript>();
			Script->SetPortalNum(4);
			Script->Activate();
		}
		else {
			assert(nullptr);
		}

		CGameObject* Player = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"Player");
		Vec3 PlayerPos = Player->Transform()->GetRelativePos();
		Player->Transform()->SetRelativePos(Vec3(PlayerPos.x, PlayerPos.y, 1500.f));

		CGameObject* PortalParticle = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"PortalParticle");
		CPortalParticleScript* ParticleScript = PortalParticle->GetScript<CPortalParticleScript>();
		ParticleScript->Activate();

		m_bPortalActivated = true;
	}
}

void CMapPortalScript::OnOverlap(CCollider2D* _Other)
{
	if (m_iPortalNum == 0) assert(nullptr);
	if (m_bPortalActivated) return;
	if (KEY_TAP(KEY::ENTER)) {
		if (m_iPortalNum == 1) {
			CGameObject* SummonEffect = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"PortalSummonEffect");
			CPortalSummonEffectScript* Script = SummonEffect->GetScript<CPortalSummonEffectScript>();
			Script->SetPortalNum(1);
			Script->Activate();
		}
		else if (m_iPortalNum == 2) {
			CGameObject* SummonEffect = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"PortalSummonEffect");
			CPortalSummonEffectScript* Script = SummonEffect->GetScript<CPortalSummonEffectScript>();
			Script->SetPortalNum(2);
			Script->Activate();
		}
		else if (m_iPortalNum == 3) {
			CGameObject* SummonEffect = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"PortalSummonEffect");
			CPortalSummonEffectScript* Script = SummonEffect->GetScript<CPortalSummonEffectScript>();
			Script->SetPortalNum(3);
			Script->Activate();
		}
		else if (m_iPortalNum == 4) {
			CGameObject* SummonEffect = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"PortalSummonEffect");
			CPortalSummonEffectScript* Script = SummonEffect->GetScript<CPortalSummonEffectScript>();
			Script->SetPortalNum(4);
			Script->Activate();
		}
		else {
			assert(nullptr);
		}

		CGameObject* Player = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"Player");
		Vec3 PlayerPos = Player->Transform()->GetRelativePos();
		Player->Transform()->SetRelativePos(Vec3(PlayerPos.x, PlayerPos.y, 1500.f));

		CGameObject* PortalParticle = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"PortalParticle");
		CPortalParticleScript* ParticleScript = PortalParticle->GetScript<CPortalParticleScript>();
		ParticleScript->Activate();

		m_bPortalActivated = true;

		Ptr<CSound> Sound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\FallRecover.wav");
		Sound->Play(1, 0.2, false);
	}
}

void CMapPortalScript::EndOverlap(CCollider2D* _Other)
{
}

void CMapPortalScript::SaveToLevelFile(FILE* _File)
{
	fwrite(&m_iPortalNum, sizeof(int), 1, _File);
}

void CMapPortalScript::LoadFromLevelFile(FILE* _FILE)
{
	fread(&m_iPortalNum, sizeof(int), 1, _FILE);
	MeshRender()->GetDynamicMaterial();
	Ptr<CTexture> PortalTex = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\particles\\Teleport.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, PortalTex);
}


