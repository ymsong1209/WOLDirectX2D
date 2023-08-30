#include "pch.h"
#include "CPlayerCameraScript.h"
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

#include <Engine/CRenderMgr.h>

CPlayerCameraScript::CPlayerCameraScript()
	: CScript((UINT)SCRIPT_TYPE::PLAYERCAMERASCRIPT)
	, m_vOffset(0.f,0.f)
	, m_fAccTime(0.f)
	, m_fTime(0.f)
	, m_bCameraShake(false)
	, m_fShakeDir(1.f)
	, m_fRange(0.f)
	, m_fShakeSpeed(0.f)
{
}

CPlayerCameraScript::~CPlayerCameraScript()
{
}

void CPlayerCameraScript::begin()
{
	CLevel* CurLevel = CLevelMgr::GetInst()->GetCurLevel();
	m_pPlayer = CurLevel->FindParentObjectByName(L"Player");
}

void CPlayerCameraScript::tick()
{
	if (m_bCameraShake) {

		m_fAccTime += DT;
		if (m_fTime <= m_fAccTime)
		{
			m_bCameraShake = false;
			m_vOffset = Vec2(0.f, 0.f);
		}
		m_vOffset.y += DT * m_fShakeSpeed * m_fShakeDir;
		if (m_fRange < fabsf(m_vOffset.y))
		{
			m_vOffset.y = m_fRange * m_fShakeDir;
			m_fShakeDir *= -1;
		}
	}


	Vec3 PlayerPos = m_pPlayer->Transform()->GetRelativePos();
	Transform()->SetRelativePos(Vec3(PlayerPos.x, PlayerPos.y + m_vOffset.y, 0.f));
}

void CPlayerCameraScript::CameraShake(float _time, float _Range, float ShakeSpeed)
{
	if (!m_bCameraShake) {
		m_fAccTime = 0.f;
		m_fTime = _time;
		m_fRange = _Range;
		m_fShakeSpeed = ShakeSpeed;
		m_bCameraShake = true;
	}
	

}
