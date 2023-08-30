#include "pch.h"
#include "CBGMScript.h"

CBGMScript::CBGMScript()
	:CScript((UINT)SCRIPT_TYPE::BGMSCRIPT)
	,m_bIcePlay(false)
{
}

CBGMScript::~CBGMScript()
{
}

void CBGMScript::begin()
{
	Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\Earth.wav");
	m_pEarth = pSound.Get();

	Ptr<CSound> pSound2 = CResMgr::GetInst()->FindRes<CSound>(L"sound\\Ice.wav");
	m_pIce = pSound2.Get();

	m_pEarth->Play(0, 0.3, true);
}

void CBGMScript::tick()
{
}

void CBGMScript::BeginOverlap(CCollider2D* _Other)
{
	if (m_bIcePlay) return;
	if (_Other->GetOwner()->GetName() == L"PlayerHitBox") {
		m_pEarth->Stop();
		m_pIce->Play(0, 0.3, true);
	}


}



