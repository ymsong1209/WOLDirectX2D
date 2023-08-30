#include "pch.h"
#include "CWardrobeArrowScript.h"
#include <Engine/CKeyMgr.h>
#include "CPlayerScript.h"

CWardrobeArrowScript::CWardrobeArrowScript()
	:CScript((UINT)SCRIPT_TYPE::WARDROBEARROWSCRIPT)
	,m_bOpen(false)
	,m_iCapeNum(0)
{
	AddScriptParam(SCRIPT_PARAM::INT, &m_iCapeNum, "CapeNum");
}

CWardrobeArrowScript::~CWardrobeArrowScript()
{
}


void CWardrobeArrowScript::tick()
{
	if (m_bOpen) {
		if (m_iCapeNum == 0) {
			Transform()->SetRelativePos(Vec3(0.f, 209.f, 1.f));
		}
		else if (m_iCapeNum == 1) {
			Transform()->SetRelativePos(Vec3(145.f, 127.f, 1.f));
		}
		else if (m_iCapeNum == 2) {
			Transform()->SetRelativePos(Vec3(145.f, -40.f, 1.f));
		}
		else if (m_iCapeNum == 3) {
			Transform()->SetRelativePos(Vec3(-3.f, -122.f, 1.f));
		}
		else if (m_iCapeNum == 4) {
			Transform()->SetRelativePos(Vec3(-147.f, -35.f, 1.f));
		}
		else if (m_iCapeNum == 5) {
			Transform()->SetRelativePos(Vec3(-150.f, 126.f, 1.f));
		}
		else {
			assert(nullptr);
		}


		if (KEY_TAP(KEY::RIGHT)) {
			++m_iCapeNum;
			if (m_iCapeNum > 5) m_iCapeNum = 0;
			Ptr<CSound> MoveSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\MenuMove.wav");
			MoveSound->Play(1, 0.3, true);
		}

		if (KEY_TAP(KEY::LEFT)) {
			--m_iCapeNum;
			if (m_iCapeNum < 0) m_iCapeNum = 5;
			Ptr<CSound> MoveSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\MenuMove.wav");
			MoveSound->Play(1, 0.3, true);
		}

		if (KEY_TAP(KEY::ENTER)) {
			CGameObject* Player = CLevelMgr::GetInst()->FindParentObjectByName(L"Player");
			CPlayerScript* PlayerMainScript = Player->GetScript<CPlayerScript>();

			if (m_iCapeNum == 0) {
				Vec4 CapeColor = Vec4(1.f, 0.f, 0.f, 1.f);
				PlayerMainScript->SetCapeColor(CapeColor);
			}
			else if (m_iCapeNum == 1) {
				Vec4 CapeColor = Vec4(0.f, 1.f, 0.f, 1.f);
				PlayerMainScript->SetCapeColor(CapeColor);
			}
			else if (m_iCapeNum == 2) {
				Vec4 CapeColor = Vec4(1.f, 1.f, 0.f, 1.f);
				PlayerMainScript->SetCapeColor(CapeColor);
			}
			else if (m_iCapeNum == 3) {
				Vec4 CapeColor = Vec4(1.f, 0.f, 1.f, 1.f);
				PlayerMainScript->SetCapeColor(CapeColor);
			}
			else if (m_iCapeNum == 4) {
				Vec4 CapeColor = Vec4(0.f, 1.f, 1.f, 1.f);
				PlayerMainScript->SetCapeColor(CapeColor);
			}
			else if (m_iCapeNum == 5) {
				Vec4 CapeColor = Vec4(0.f, 0.f, 1.f, 1.f);
				PlayerMainScript->SetCapeColor(CapeColor);
			}
			else {
				assert(nullptr);
			}

			Ptr<CSound> Equip = CResMgr::GetInst()->FindRes<CSound>(L"sound\\Equip.wav");
			Equip->Play(1, 0.3, true);
		}
	}
}

void CWardrobeArrowScript::begin()
{
	MeshRender()->GetDynamicMaterial();
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, nullptr);
}

void CWardrobeArrowScript::SaveToLevelFile(FILE* _File)
{
}

void CWardrobeArrowScript::LoadFromLevelFile(FILE* _FILE)
{
	MeshRender()->GetDynamicMaterial();
	Ptr<CTexture> Arrow = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\ArrowLeftLarge.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, Arrow);
}

void CWardrobeArrowScript::Activate()
{
	m_bOpen = true;
	Ptr<CTexture> Arrow = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\ArrowLeftLarge.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, Arrow);
}

void CWardrobeArrowScript::Deactivate()
{
	m_bOpen = false;
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, nullptr);
}


