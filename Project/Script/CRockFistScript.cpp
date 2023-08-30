#include "pch.h"
#include "CRockFistScript.h"
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CResMgr.h>
#include "CPlayerScript.h"
#include "CPlayerHitScript.h"
CRockFistScript::CRockFistScript()
	:CScript((UINT)SCRIPT_TYPE::ROCKFISTSCRIPT)
	,m_bChanged(false)
{
}

CRockFistScript::~CRockFistScript()
{
}


void CRockFistScript::begin()
{
	MeshRender()->GetDynamicMaterial();
	Ptr<CTexture> Rock = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\Boss\\Boss_Box.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, Rock);

}

void CRockFistScript::tick()
{
	if (GetOwner()->IsDead()) return;

	m_fChargeTime += DT;
	if (m_fChargeTime > 1.f) {
		if (m_bChanged == false) {
			m_bChanged = true;
			//x축으로 더 멀리 있음 ->왼쪽 or오른쪽 봐야함
			if (abs(m_vBossPos.x - m_vPlayerPos.x) > abs(m_vBossPos.y - m_vPlayerPos.y)) {
				if (m_vBossPos.x < m_vPlayerPos.x) {
					Transform()->SetRelativeRot(Vec3(0.f, 0.f, XMConvertToRadians(270.f)));
					Ptr<CTexture> Rock = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\Boss\\EarthBossRockFistRight.png");
					MeshRender()->GetMaterial()->SetTexParam(TEX_0, Rock);
					m_vDirection = Vec3(1.0f, 0.f, 0.f);
				}
				else {
					Transform()->SetRelativeRot(Vec3(XMConvertToRadians(180.f), 0.f, XMConvertToRadians(270.f)));
					Ptr<CTexture> Rock = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\Boss\\EarthBossRockFistRight.png");
					MeshRender()->GetMaterial()->SetTexParam(TEX_0, Rock);
					m_vDirection = Vec3(-1.0f, 0.f, 0.f);
				}
			}
			else {
				if (m_vBossPos.y < m_vPlayerPos.y) {
					Ptr<CTexture> Rock = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\Boss\\EarthBossRockFistUp.png");
					MeshRender()->GetMaterial()->SetTexParam(TEX_0, Rock);
					m_vDirection = Vec3(0.0f, 1.f, 0.f);
				}
				else {
					Transform()->SetRelativeRot(Vec3(0.f, 0.f, XMConvertToRadians(180.f)));
					Ptr<CTexture> Rock = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\Boss\\EarthBossRockFistDown.png");
					MeshRender()->GetMaterial()->SetTexParam(TEX_0, Rock);
					m_vDirection = Vec3(0.0f, -1.f, 0.f);
				}
			}
		}	
	}
	if (m_bChanged) {
		Vec3 Direction = Vec3(m_vPlayerPos.x - m_vBossPos.x, m_vPlayerPos.y - m_vBossPos.y, 1.f);
		Direction.Normalize();
		RigidBody()->SetVelocity(Vec2(Direction.x * 600.f, Direction.y * 600.f));
	}

	if (m_fChargeTime > 5.f) {
		DestroyObject(GetOwner());
	}
}

void CRockFistScript::BeginOverlap(CCollider2D* _Other)
{
	if (_Other->GetOwner()->GetName() == L"PlayerHitBox" ||
		_Other->GetOwner()->GetLayerIndex() == CLevelMgr::GetInst()->GetCurLevel()->FindLayerByName(L"Wall")->GetLayerIndex()) {
		CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
		if (Curlevel->GetLayer(_Other->GetOwner()->GetLayerIndex())->GetName() == L"PlayerHitBox") {
			CGameObject* Player = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"Player");
			CPlayerScript* PlayerMainScript = Player->GetScript<CPlayerScript>();
			CPlayerHitScript* PlayerHitScript = Player->GetScript<CPlayerHitScript>();

			if (PlayerMainScript->IsPlayerDeadState() == false) {
				PlayerMainScript->ChangeState((UINT)SCRIPT_TYPE::PLAYERHITSCRIPT, false);
				PlayerHitScript->SetDirection(Vec3(m_vDirection.x * -1, m_vDirection.y * -1, 0.f));
			}
			
		}
		Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\EarthPebble.wav");
		pSound->Play(1, 0.2, true);
		DestroyObject(GetOwner());
	}
}
