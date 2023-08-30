#include "pch.h"
#include "CMageBallAttackScript.h"
#include "CMageBallScript.h"
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim2D.h>
#include "CMageBallAfterImageScript.h"

CMageBallAttackScript::CMageBallAttackScript()
	:CScript((UINT)SCRIPT_TYPE::MAGEBALLATTACKSCRIPT)
	, m_fForce(400.f)
{
	SetActive(false);
}

CMageBallAttackScript::~CMageBallAttackScript()
{
}


void CMageBallAttackScript::begin()
{
}

void CMageBallAttackScript::tick()
{
	if (!IsActive()) return;
	m_fAttackTime += DT;
	m_fAfterImageTime += DT;

	Vec3 Direction = Transform()->GetRelativeRot();
	//float angle = Direction.z * 180.0 / XM_PI;
	RigidBody()->SetVelocity(Vec2(m_fForce * cos(Direction.z), m_fForce * sin(Direction.z)));

	if (m_fAttackTime > 5.0f)
	{
		ChangeState((UINT)SCRIPT_TYPE::MAGEBALLIDLESCRIPT, false);
	}
	if (m_fAfterImageTime > 0.1f) {
		CGameObject* afterimage = new CGameObject();
		afterimage->SetName(L"MageBallAfterImage");
		afterimage->SetLifeSpan(0.3f);
		afterimage->AddComponent(Transform()->Clone());
		afterimage->AddComponent(new CMeshRender);
		afterimage->AddComponent(new CMageBallAfterImageScript);
		afterimage->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
		afterimage->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"material\\OutlineMtrl.mtrl"));
		Vec4 OutlineColor = Vec4(1.f, 0.f, 0.f, 0.f);
		afterimage->MeshRender()->GetDynamicMaterial()->SetScalarParam(VEC4_0, OutlineColor);
		afterimage->AddComponent(Animator2D()->Clone());
		afterimage->Animator2D()->Pause();

		SpawnGameObject(afterimage, afterimage->Transform()->GetRelativePos(), 0);
		m_fAfterImageTime = 0.f;

	}
}

void CMageBallAttackScript::Enter()
{
	m_fAttackTime = 0.f;
	Animator2D()->Play(L"WizardBall_Attack", false);
	Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\MageFireballRelease.wav");
	pSound->Play(1, 0.2, true);
}

void CMageBallAttackScript::Exit()
{
	m_fAttackTime = 0.f;
	Animator2D()->GetCurAnim()->Reset();
}


