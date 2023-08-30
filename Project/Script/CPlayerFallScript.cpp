#include "pch.h"
#include "CPlayerFallScript.h"
#include "CPlayerScript.h"
#include <Engine/CCollisionMgr.h>
CPlayerFallScript::CPlayerFallScript()
	: CScript((UINT)SCRIPT_TYPE::PLAYERFALLSCRIPT)
	, m_fFalltime(0.f)
{
	SetActive(false);
}
CPlayerFallScript::~CPlayerFallScript()
{
}

void CPlayerFallScript::begin()
{
}

void CPlayerFallScript::tick()
{
	if (!IsActive()) return;
	RigidBody()->SetVelocity(Vec2(0.f, -350.f));
	m_fFalltime += DT;
	if (m_fFalltime > 0.7f) {
		ChangeState((UINT)SCRIPT_TYPE::PLAYERIDLESCRIPT);
		m_fFalltime = 0.f;
	}
}

void CPlayerFallScript::Enter()
{
	m_fFalltime = 0.f;
	CPlayerScript* PlayerMainScript = GetOwner()->GetScript<CPlayerScript>();
	Vec3 Pos = Transform()->GetRelativePos();
	Transform()->SetRelativePos(Vec3(Pos.x, Pos.y, 550.f));
	int dir = PlayerMainScript->GetPlayerDir();
	if (dir & DIR_UP) {
		Animator2D()->Play(L"Player_Fall_Up", true);
	}
	else if (dir & DIR_DOWN) {
		Animator2D()->Play(L"Player_Fall_Down", true);
	}
	else if (dir & DIR_RIGHT) {
		Animator2D()->Play(L"Player_Fall_Right", true);
	}
	else if (dir & DIR_LEFT) {
		Animator2D()->Play(L"Player_Fall_Left", true);
	}
	else {
		assert(nullptr);
		//Player가 4방향으로 정돈이 안되어있다.
	}

	RigidBody()->SetVelocity(Vec2(0.f, 0.f));

	Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\Fall.wav");
	pSound->Play(1, 0.5f, true);
}

void CPlayerFallScript::Exit()
{
	CPlayerScript* PlayerMainScript = GetOwner()->GetScript<CPlayerScript>();
	Vec3 pos = PlayerMainScript->GetDashStartPos();
	Transform()->SetRelativePos(Vec3(pos.x, pos.y, 350.f));
	CCollisionMgr::GetInst()->LayerCheck(L"Player", L"PitWall");
	CGameObject* portal = new CGameObject;
	portal->SetName(L"portal");
	portal->AddComponent(new CTransform);
	portal->AddComponent(new CMeshRender);
	portal->AddComponent(new CAnimator2D);
	portal->Transform()->SetRelativePos(Vec3(pos.x, pos.y, 350.f));
	portal->Transform()->SetRelativeScale(Vec3(100.f, 150.f, 1.f));
	portal->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	portal->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"material\\Std2DLightMtrl.mtrl"));
	portal->MeshRender()->GetDynamicMaterial();
	portal->Animator2D()->LoadAnim(L"animation\\particle\\portal.anim");
	portal->Animator2D()->Play(L"portal", false);
	portal->SetLifeSpan(0.3);
	SpawnGameObject(portal, Vec3(pos.x, pos.y, 350.f), L"Default");
	Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\FallRecover.wav");
	pSound->Play(1, 0.5f, true);
	
}
