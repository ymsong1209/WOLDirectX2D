#include "pch.h"
#include "CPlayerDeadScript.h"
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim2D.h>
#include "CPlayerScript.h"
#include <Engine/CTimeMgr.h>
CPlayerDeadScript::CPlayerDeadScript()
	: CScript((UINT)SCRIPT_TYPE::PLAYERDEADSCRIPT)
	, m_fDissolveTime(0.f)
	, m_fDissolveRange(0.05f)
	, m_vDissolveColor(0.0f, 0.0f, 1.0f, 0.f)
	, m_bDissolveActive(false)
{
	SetActive(false);
}
CPlayerDeadScript::CPlayerDeadScript(const CPlayerDeadScript& _other)
	: CScript((UINT)SCRIPT_TYPE::PLAYERDEADSCRIPT)
	, m_fDissolveTime(_other.m_fDissolveTime)
	, m_fDissolveRange(_other.m_fDissolveRange)
	, m_vDissolveColor(_other.m_vDissolveColor)
	, m_bDissolveActive(_other.m_bDissolveActive)
{
}


CPlayerDeadScript::~CPlayerDeadScript()
{
}

void CPlayerDeadScript::begin()
{
}

void CPlayerDeadScript::tick()
{
	if (!IsActive()) return;

	if (KEY_TAP(KEY::F)) {
		ChangeState((UINT)SCRIPT_TYPE::PLAYERIDLESCRIPT, false);
		CGameObject* Player = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"Player");
		CPlayerScript* Script = Player->GetScript<CPlayerScript>();
		PlayerStat stat = Script->GetStat();
		stat.CurHP = 100;
		Script->SetStat(stat);
	}

	if (m_bDissolveActive) {
		m_fDissolveTime += DT * 0.5f;
		if (m_fDissolveTime > 1.f) m_fDissolveTime = 1.f;

		float DissolveThickness = 0.1;



		MeshRender()->GetDynamicMaterial()->SetScalarParam(FLOAT_0, &m_fDissolveTime);
		MeshRender()->GetDynamicMaterial()->SetScalarParam(FLOAT_1, &DissolveThickness);
		MeshRender()->GetDynamicMaterial()->SetScalarParam(VEC4_0, &m_vDissolveColor);

	}


}

void CPlayerDeadScript::Enter()
{
	CPlayerScript* PlayerMainScript = GetOwner()->GetScript<CPlayerScript>();
	Animator2D()->Play(L"Player_Dead", false);
	m_bDissolveActive = true;
	m_fDissolveTime = 0.f;
	int iDissolveUse = 1;
	MeshRender()->GetDynamicMaterial()->SetScalarParam(INT_1, &iDissolveUse);
	m_vDissolveColor = PlayerMainScript->GetCapeColor();
	float Acctime = CTimeMgr::GetInst()->GetAccTime();
	MeshRender()->GetDynamicMaterial()->SetScalarParam(FLOAT_2, &Acctime);

	PlayerMainScript->SetPlayerDeadState(true);
}

void CPlayerDeadScript::Exit()
{
	CPlayerScript* PlayerMainScript = GetOwner()->GetScript<CPlayerScript>();

	Animator2D()->GetCurAnim()->Reset();
	m_bDissolveActive = false;
	m_fDissolveTime = 0.f;

	int iDissolveUse = 0;
	MeshRender()->GetDynamicMaterial()->SetScalarParam(INT_1, &iDissolveUse);
	//MeshRender()->GetMaterial()->SetScalarParam(INT_1, &iDissolveUse);

	PlayerMainScript->SetPlayerDeadState(false);
}


void CPlayerDeadScript::DissolveActive()
{
	//Active ÄÑ±â
	if (!m_bDissolveActive)
	{
		m_bDissolveActive = true;
		m_fDissolveTime = 0.f;
		int iDissolveUse = 1;
		MeshRender()->GetDynamicMaterial()->SetScalarParam(INT_1, &iDissolveUse);

	}
	//Active ²ô±â
	else
	{
		m_bDissolveActive = false;
		m_fDissolveTime = 0.f;

		int iDissolveUse = 0;
		MeshRender()->GetDynamicMaterial()->SetScalarParam(INT_1, &iDissolveUse);
		//MeshRender()->GetMaterial()->SetScalarParam(INT_1, &iDissolveUse);
	}
}