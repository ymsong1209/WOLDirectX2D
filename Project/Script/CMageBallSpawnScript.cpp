#include "pch.h"
#include "CMageBallSpawnScript.h"
#include "CMageBallScript.h"
#include "CMageBallHitboxScript.h"
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim2D.h>

CMageBallSpawnScript::CMageBallSpawnScript()
	:CScript((UINT)SCRIPT_TYPE::MAGEBALLSPAWNSCRIPT)
{
	SetActive(false);
}

CMageBallSpawnScript::~CMageBallSpawnScript()
{
}


void CMageBallSpawnScript::begin()
{
}

void CMageBallSpawnScript::tick()
{
	if (!IsActive()) return;
	if (Animator2D()->GetCurAnim()->IsFinish()) {
	
		Transform()->SetRelativeScale(Vec3(80.f, 80.f, 1.f));
		vector<CGameObject*> childs = GetOwner()->GetChild();

		CGameObject* HitBox = childs[0];
		CMageBallHitboxScript* HitBoxScript = HitBox->GetScript<CMageBallHitboxScript>();
		HitBoxScript->AddCollider();
		ChangeState((UINT)SCRIPT_TYPE::MAGEBALLIDLESCRIPT, false);
	}
}

void CMageBallSpawnScript::Enter()
{
	Animator2D()->SetSamplerState(1);
	Transform()->SetRelativeScale(Vec3(250.f, 250.f, 1.f));
	Animator2D()->Play(L"WizardBall_Spawn", false);
}

void CMageBallSpawnScript::Exit()
{
	
}


