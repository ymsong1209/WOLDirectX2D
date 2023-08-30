#include "pch.h"
#include "CPlayerHurtUIScript.h"
#include "CPlayerScript.h"
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

CPlayerHurtUIScript::CPlayerHurtUIScript()
	:CScript((UINT)SCRIPT_TYPE::PLAYERHURTUISCRIPT)
	,m_fAlphaCoefficient(1.0f)
{
}

CPlayerHurtUIScript::~CPlayerHurtUIScript()
{
}

void CPlayerHurtUIScript::begin()
{
	Ptr<CTexture> Effect = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\CameraHurtEffect.png");
	MeshRender()->GetDynamicMaterial();
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, Effect);
}

void CPlayerHurtUIScript::tick()
{
	CGameObject* Player = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"Player");
	CPlayerScript* PlayerMainScript = Player->GetScript<CPlayerScript>();
	int hp = PlayerMainScript->GetStat().CurHP;
	if (0 < hp && hp < 30) {
		m_fTime += DT;
		if (1.0 <= m_fTime)
		{
			m_fAlphaCoefficient = m_fAlphaCoefficient * -1;
			m_fTime = 0.f;
		}
		m_fAlpha = m_fAlpha + DT * m_fAlphaCoefficient;
		if (m_fAlpha > 1.0f) {
			m_fAlpha = 1.0f;
		}
	}
	else {
		m_fAlpha = 0.f;
		m_fAlphaCoefficient = 1.f;
		m_fTime = 0.f;
	}
	MeshRender()->GetMaterial()->SetScalarParam(FLOAT_0, &m_fAlpha);
}

void CPlayerHurtUIScript::SaveToLevelFile(FILE* _File)
{
}

void CPlayerHurtUIScript::LoadFromLevelFile(FILE* _File)
{
	Ptr<CTexture> Effect = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\CameraHurtEffect.png");
	MeshRender()->GetDynamicMaterial();
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, Effect);
}


