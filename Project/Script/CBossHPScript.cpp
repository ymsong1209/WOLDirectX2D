#include "pch.h"
#include "CBossHPScript.h"
#include "CBossScript.h"

CBossHPScript::CBossHPScript()
	:CScript((UINT)SCRIPT_TYPE::BOSSHPSCRIPT)
{
}

CBossHPScript::~CBossHPScript()
{
}

void CBossHPScript::begin()
{
	MeshRender()->GetDynamicMaterial();
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, nullptr);
}

void CBossHPScript::tick()
{
	if (m_bUIActive) {
		CGameObject* Boss = CLevelMgr::GetInst()->GetCurLevel()->FindParentObjectByName(L"Boss");
		CBossScript* BossMainScript = Boss->GetScript<CBossScript>();

		int CurHP = BossMainScript->GetBossHp();
		int MaxHP = BossMainScript->GetBossMAXHp();
		
		float hp = (float)CurHP / (float)MaxHP;

		Transform()->SetRelativeScale(Vec3(382.f * (float)hp, 38.f, 1.f));
		Transform()->SetRelativePos(Vec3(-382.f / 2.f + Transform()->GetRelativeScale().x / 2.f, 260.f, 15.f));
	}
}

void CBossHPScript::SaveToLevelFile(FILE* _File)
{
}

void CBossHPScript::LoadFromLevelFile(FILE* _File)
{
	Ptr<CTexture> HP = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\UI_HPBAR.png");
	MeshRender()->GetDynamicMaterial();
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, HP);
}

void CBossHPScript::Activate()
{
	m_bUIActive = true;
	Ptr<CTexture> HP = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\UI_HPBAR.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, HP);
}

void CBossHPScript::Deactivate()
{
	m_bUIActive = false;
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, nullptr);
}



