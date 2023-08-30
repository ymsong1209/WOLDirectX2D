#include "pch.h"
#include "CPlayerHitBoxScript.h"
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include "CPlayerScript.h"

CPlayerHitBoxScript::CPlayerHitBoxScript()
	: CScript((UINT)SCRIPT_TYPE::PLAYERHITBOXSCRIPT)
	, m_pPlayer(nullptr)
{

}

CPlayerHitBoxScript::CPlayerHitBoxScript(const CPlayerHitBoxScript& _other)
	: CScript((UINT)SCRIPT_TYPE::PLAYERHITBOXSCRIPT)
{
}

CPlayerHitBoxScript::~CPlayerHitBoxScript()
{
}


void CPlayerHitBoxScript::begin()
{
	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
	m_pPlayer = Curlevel->FindParentObjectByName(L"Player");
	assert(m_pPlayer);
}

void CPlayerHitBoxScript::tick()
{
	Vec3 PlayerPos = m_pPlayer->Transform()->GetRelativePos();
	Transform()->SetRelativePos(PlayerPos);
}

void CPlayerHitBoxScript::BeginOverlap(CCollider2D* _Other)
{
}

void CPlayerHitBoxScript::OnOverlap(CCollider2D* _Other)
{
  
}

void CPlayerHitBoxScript::EndOverlap(CCollider2D* _Other)
{
}


