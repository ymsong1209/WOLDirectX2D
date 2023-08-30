#include "pch.h"
#include "CPlayerWalkScript.h"
#include "CPlayerScript.h"
#include <Engine/CKeyMgr.h>
#include <Engine/CTimeMgr.h>
#include "CScriptMgr.h"
#include "CPlayerAfterImageScript.h"
#include "CMousePointerScript.h"
#include "CPlayerDustScript.h"

CPlayerWalkScript::CPlayerWalkScript()
	: CScript((UINT)SCRIPT_TYPE::PLAYERWALKSCRIPT)
	, m_fWalkTime(0.f)
	, m_fAfterImageCreateTime(0.f)
	, m_bWalkSound(true)
{
	SetActive(false);
}

CPlayerWalkScript::~CPlayerWalkScript()
{
}



void CPlayerWalkScript::begin()
{
}

void CPlayerWalkScript::tick()
{
	if (!IsActive()) return;
	m_fWalkSoundTime += DT;
	if (m_fWalkSoundTime > 0.4f) {
		if (m_bWalkSound) {
			m_bWalkSound = !m_bWalkSound;
			Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\PlayerFootstep.wav");
			pSound->Play(1, 0.4, true);
		}
		else {
			m_bWalkSound = !m_bWalkSound;
			Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\PlayerFootstepAlt.wav");
			pSound->Play(1, 0.4, true);
		}
		m_fWalkSoundTime = 0.f;
	}


	m_fWalkTime += DT;
	CPlayerScript* PlayerMainScript = GetOwner()->GetScript<CPlayerScript>();

	if (m_fWalkTime > 3.0f) {
		PlayerMainScript->SetSpeed(400.f);
		m_fAfterImageCreateTime += DT;
		if (!m_bDashSound) {
			Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\RunSpeed.wav");
			pSound->Play(1, 0.17f, true);
			m_bDashSound = true;

			vector<CGameObject*> Childs = GetOwner()->GetChild();
			for (size_t i = 0; i < Childs.size(); ++i) {
				if (Childs[i]->GetName() == L"PlayerDust") {
					CPlayerDustScript* DustScript = Childs[i]->GetScript<CPlayerDustScript>();
					DustScript->ActivateDust();
				}
			}
		}
	}
	if (m_fAfterImageCreateTime > 0.1f) {
		CGameObject* afterimage = new CGameObject();
		afterimage->SetName(L"AfterImage");
		afterimage->SetLifeSpan(0.3f);
		afterimage->AddComponent(Transform()->Clone());
		afterimage->AddComponent(new CMeshRender);
		afterimage->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
		afterimage->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"material\\OutlineMtrl.mtrl"));
		afterimage->MeshRender()->GetDynamicMaterial();
		afterimage->AddComponent(Animator2D()->Clone());
		afterimage->Animator2D()->Pause();
		afterimage->AddComponent(new CPlayerAfterImageScript);
		CPlayerAfterImageScript* AfterImageScript = afterimage->GetScript<CPlayerAfterImageScript>();
		AfterImageScript->SetCapeColor(PlayerMainScript->GetCapeColor());

		SpawnGameObject(afterimage, afterimage->Transform()->GetRelativePos(), 0);
		m_fAfterImageCreateTime = 0.f;
	}

	//�߰� �̵�(UP)
	if (KEY_TAP(KEY::W)) {
		//�Ʒ��� ���ٰ� ���� ���� ���, slide
		if (PlayerMainScript->GetPlayerDir() & DIR_DOWN) {
			PlayerMainScript->SetPlayerDir(DIR_UP);
			ChangeState((UINT)SCRIPT_TYPE::PLAYERSLIDESCRIPT);
			return;
		}
		//�������̳� ������ �����ٰ� ���� ���� ���
		//�����̳� ������ �̵� �ִϸ��̼��� ������ ���� �ִϸ��̼Ǻ��� �켱������ ����.
		else if (PlayerMainScript->GetPlayerDir() & DIR_LEFT || PlayerMainScript->GetPlayerDir() & DIR_RIGHT) {
			Animator2D()->Play(L"Player_Walk_Up", true);
			PlayerMainScript->SetPlayerDir(PlayerMainScript->GetPlayerDir() | DIR_UP);
		}
	}
	//�߰� �̵�(Down)
	if (KEY_TAP(KEY::S)) {

		//���� ���ٰ� �Ʒ��� ���� ���, slide
		if (PlayerMainScript->GetPlayerDir() & DIR_UP) {
			PlayerMainScript->SetPlayerDir(DIR_DOWN);
			ChangeState((UINT)SCRIPT_TYPE::PLAYERSLIDESCRIPT);
			return;
		}
		//�������̳� ������ �����ٰ� �Ʒ��� ���� ���
		//�����̳� ������ �̵� �ִϸ��̼��� ������ ���� �ִϸ��̼Ǻ��� �켱������ ����.
		else if (PlayerMainScript->GetPlayerDir() & DIR_LEFT || PlayerMainScript->GetPlayerDir() & DIR_RIGHT) {
			Animator2D()->Play(L"Player_Walk_Down", true);
			PlayerMainScript->SetPlayerDir(PlayerMainScript->GetPlayerDir() | DIR_DOWN);
		}
	}
	//�߰� �̵�(����)
	if (KEY_TAP(KEY::A)) {
		//������ �̵� ���̿��µ� ���� ���� ��� Slide		
		if (PlayerMainScript->GetPlayerDir() & DIR_RIGHT) {
			//��+��, ��+�� �̵����̿��µ� ������ ���� ��� �׳� ������ ���� ��
			PlayerMainScript->SetPlayerDir(DIR_RIGHT);
			ChangeState((UINT)SCRIPT_TYPE::PLAYERSLIDESCRIPT);
			return;
		}
		else {
			//�ִϸ��̼� ��ȯ�� Idle->Walk�϶� �̹� ��ȯ��Ŵ
			PlayerMainScript->SetPlayerDir(PlayerMainScript->GetPlayerDir() | DIR_LEFT);
		}
	}
	//�߰� �̵�(������)
	if (KEY_TAP(KEY::D)) {
		//���� �̵� ���̿��µ� ������ ���� ��� Slide		
		if (PlayerMainScript->GetPlayerDir() & DIR_LEFT) {
			//��+��, ��+�� �̵����̿��µ� �������� ���� ��� �׳� ���� ���� ��
			PlayerMainScript->SetPlayerDir(DIR_LEFT);
			ChangeState((UINT)SCRIPT_TYPE::PLAYERSLIDESCRIPT);
			return;
		}
		else {
			//�ִϸ��̼� ��ȯ�� Idle->Walk�϶� �̹� ��ȯ��Ŵ
			PlayerMainScript->SetPlayerDir(PlayerMainScript->GetPlayerDir() | DIR_RIGHT);
		}
	}
	//���� Ű ����
	if (KEY_RELEASE(KEY::A)) {
		//���� Ű�� �����µ� �����ϴ� ���
		if (PlayerMainScript->GetPlayerDir() == DIR_LEFT) {
			//�ȴ°� �ƴ϶� �޸��� ���̸� Slide�ؾ���
			if (PlayerMainScript->GetSpeed() == 400.f) {
				ChangeState((UINT)SCRIPT_TYPE::PLAYERSLIDESCRIPT);
			}
			else {
				ChangeState((UINT)SCRIPT_TYPE::PLAYERIDLESCRIPT);
			}
			return;
		}
		PlayerMainScript->SetPlayerDir(PlayerMainScript->GetPlayerDir() & ~DIR_LEFT);
		//��+�� ������ �־��� ���
		if (PlayerMainScript->GetPlayerDir() & DIR_UP) {
			Animator2D()->Play(L"Player_Walk_Up", true);
		}
		//��+�� ������ �־��� ���
		else if (PlayerMainScript->GetPlayerDir() & DIR_DOWN) {
			Animator2D()->Play(L"Player_Walk_Down", true);
		}
		else {
			//���� �̻��ϴ�.
			assert(nullptr);
		}
	}
	//������ Ű ����
	if (KEY_RELEASE(KEY::D)) {
		//������ Ű�� �����µ� �����ϴ� ���
		if (PlayerMainScript->GetPlayerDir() == DIR_RIGHT) {
			if (PlayerMainScript->GetSpeed() == 400.f) {
				ChangeState((UINT)SCRIPT_TYPE::PLAYERSLIDESCRIPT);
			}
			else {
				ChangeState((UINT)SCRIPT_TYPE::PLAYERIDLESCRIPT);
			}
			return;
		}
		PlayerMainScript->SetPlayerDir(PlayerMainScript->GetPlayerDir() & ~DIR_RIGHT);
		//��+�� ������ �־��� ���
		if (PlayerMainScript->GetPlayerDir() & DIR_UP) {
			Animator2D()->Play(L"Player_Walk_Up", true);
		}
		//��+�� ������ �־��� ���
		else if (PlayerMainScript->GetPlayerDir() & DIR_DOWN) {
			Animator2D()->Play(L"Player_Walk_Down", true);
		}
		else {
			//���� �̻��ϴ�.
			assert(nullptr);
		}
	}
	//��Ű ����
	if (KEY_RELEASE(KEY::W)) {
		//��Ű�� �����µ� �����ϴ� ���
		if (PlayerMainScript->GetPlayerDir() == DIR_UP) {
			if (PlayerMainScript->GetSpeed() == 400.f) {
				ChangeState((UINT)SCRIPT_TYPE::PLAYERSLIDESCRIPT);
			}
			else {
				ChangeState((UINT)SCRIPT_TYPE::PLAYERIDLESCRIPT);
			}
			return;
		}
		PlayerMainScript->SetPlayerDir(PlayerMainScript->GetPlayerDir() & ~DIR_UP);
		//��+�� ������ �־��� ���
		if (PlayerMainScript->GetPlayerDir() & DIR_RIGHT) {
			Animator2D()->Play(L"Player_Walk_Right", true);
		}
		//��+�� ������ �־��� ���
		else if (PlayerMainScript->GetPlayerDir() & DIR_LEFT) {
			Animator2D()->Play(L"Player_Walk_Left", true);
		}
		else {
			//���� �̻��ϴ�.
			assert(nullptr);
		}
	}
	//��Ű ����
	if (KEY_RELEASE(KEY::S)) {
		//������ Ű�� �����µ� �����ϴ� ���
		if (PlayerMainScript->GetPlayerDir() == DIR_DOWN) {
			if (PlayerMainScript->GetSpeed() == 400.f) {
				ChangeState((UINT)SCRIPT_TYPE::PLAYERSLIDESCRIPT);
			}
			else {
				ChangeState((UINT)SCRIPT_TYPE::PLAYERIDLESCRIPT);
			}
			return;
		}
		PlayerMainScript->SetPlayerDir(PlayerMainScript->GetPlayerDir() & ~DIR_DOWN);
		//��+�� ������ �־��� ���
		if (PlayerMainScript->GetPlayerDir() & DIR_RIGHT) {
			Animator2D()->Play(L"Player_Walk_Right", true);
		}
		//��+�� ������ �־��� ���
		else if (PlayerMainScript->GetPlayerDir() & DIR_LEFT) {
			Animator2D()->Play(L"Player_Walk_Left", true);
		}
		else {
			//���� �̻��ϴ�.
			assert(nullptr);
		}
	}
	//Dash
	if (KEY_TAP(KEY::SPACE)) {
		ChangeState((UINT)SCRIPT_TYPE::PLAYERDASHSCRIPT);
	}


	// Velocity Change
	Vec3 vCurPos = Transform()->GetRelativePos();

	float PlayerSpeed = PlayerMainScript->GetSpeed();
	Vec2 CurVelocity = RigidBody()->GetVelocity();

	if (PlayerMainScript->GetPlayerDir() == (DIR_UP | DIR_RIGHT)) {
		RigidBody()->SetVelocity(Vec2(PlayerSpeed, PlayerSpeed));
	}
	else if (PlayerMainScript->GetPlayerDir() == (DIR_UP | DIR_LEFT)) {
		RigidBody()->SetVelocity(Vec2(-PlayerSpeed, PlayerSpeed));
	}
	else if (PlayerMainScript->GetPlayerDir() == (DIR_DOWN | DIR_LEFT)) {
		RigidBody()->SetVelocity(Vec2(-PlayerSpeed, -PlayerSpeed));
	}
	else if (PlayerMainScript->GetPlayerDir() == (DIR_DOWN | DIR_RIGHT)) {
		RigidBody()->SetVelocity(Vec2(PlayerSpeed, -PlayerSpeed));
	}
	else if (PlayerMainScript->GetPlayerDir() == (DIR_UP)) {
		RigidBody()->SetVelocity(Vec2(0.f, PlayerSpeed));
	}
	else if (PlayerMainScript->GetPlayerDir() == (DIR_DOWN)) {
		RigidBody()->SetVelocity(Vec2(0.f,-PlayerSpeed));
	}
	else if (PlayerMainScript->GetPlayerDir() == (DIR_RIGHT)) {
		RigidBody()->SetVelocity(Vec2(PlayerSpeed,0.f));
	}
	else if (PlayerMainScript->GetPlayerDir() == (DIR_LEFT)) {
		RigidBody()->SetVelocity(Vec2(-PlayerSpeed,0.f));
	}
	else {
		assert(nullptr);
	}

	ChangeToAttack();
}



void CPlayerWalkScript::Enter()
{
	CPlayerScript* PlayerMainScript = GetOwner()->GetScript<CPlayerScript>();
	PlayerMainScript->SetSpeed(300.f);
	int direction = PlayerMainScript->GetPlayerDir();
	if (direction & DIR_UP) {
		Animator2D()->Play(L"Player_Walk_Up", true);
	}
	else if (direction & DIR_DOWN) {
		Animator2D()->Play(L"Player_Walk_Down", true);
	}
	else if (direction & DIR_LEFT) {
		Animator2D()->Play(L"Player_Walk_Left", true);
	}
	else if (direction & DIR_RIGHT) {
		Animator2D()->Play(L"Player_Walk_Right", true);
	}
	else {
		assert(nullptr);
	}

	m_fWalkTime = 0.f;
	m_bDashSound = false;
	m_fWalkSoundTime = 0.f;
}

void CPlayerWalkScript::Exit()
{
	CPlayerScript* PlayerMainScript = GetOwner()->GetScript<CPlayerScript>();
	PlayerMainScript->SetSpeed(300.f);
	m_fWalkTime = 0.f;
	m_bDashSound = false;

	vector<CGameObject*> Childs = GetOwner()->GetChild();
	for (size_t i = 0; i < Childs.size(); ++i) {
		if (Childs[i]->GetName() == L"PlayerDust") {
			CPlayerDustScript* DustScript = Childs[i]->GetScript<CPlayerDustScript>();
			DustScript->DeActivateDust();
		}
	}
	m_fWalkSoundTime = 0.f;
}

void CPlayerWalkScript::ChangeToAttack()
{
	//GetMousePointer------------//
	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
	CPlayerScript* PlayerMainScript = GetOwner()->GetScript<CPlayerScript>();

	if (KEY_TAP(KEY::LBTN)) {
		if (PlayerMainScript->GetCurCoolTimePerBtn(PLAYER_ATTACKBUTTON::LBTN) <= 0.f) {
			PlayerMainScript->SetAttackBtn(PLAYER_ATTACKBUTTON::LBTN);
			ChangeDir();
			ChangeState((UINT)SCRIPT_TYPE::PLAYERATTACKSCRIPT);
		}
	}
	else if (KEY_TAP(KEY::RBTN)) {
		if (PlayerMainScript->GetCurCoolTimePerBtn(PLAYER_ATTACKBUTTON::RBTN) <= 0.f) {
			PlayerMainScript->SetAttackBtn(PLAYER_ATTACKBUTTON::RBTN);
			ChangeDir();
			ChangeState((UINT)SCRIPT_TYPE::PLAYERATTACKSCRIPT);
		}

	}
	else if (KEY_TAP(KEY::Q)) {
		if (PlayerMainScript->GetCurCoolTimePerBtn(PLAYER_ATTACKBUTTON::Q) <= 0.f) {
			PlayerMainScript->SetAttackBtn(PLAYER_ATTACKBUTTON::Q);
			ChangeDir();
			ChangeState((UINT)SCRIPT_TYPE::PLAYERATTACKSCRIPT);
		}

	}
	else if (KEY_TAP(KEY::E)) {
		if (PlayerMainScript->GetCurCoolTimePerBtn(PLAYER_ATTACKBUTTON::E) <= 0.f) {
			PlayerMainScript->SetAttackBtn(PLAYER_ATTACKBUTTON::E);
			ChangeDir();
			ChangeState((UINT)SCRIPT_TYPE::PLAYERATTACKSCRIPT);
		}

	}
	else if (KEY_TAP(KEY::R)) {
		if (PlayerMainScript->GetCurCoolTimePerBtn(PLAYER_ATTACKBUTTON::R) <= 0.f) {
			PlayerMainScript->SetAttackBtn(PLAYER_ATTACKBUTTON::R);
			ChangeDir();
			ChangeState((UINT)SCRIPT_TYPE::PLAYERATTACKSCRIPT);
		}

	}
}

void CPlayerWalkScript::ChangeDir()
{	//GetMousePointer------------//
	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
	CGameObject* mouse = Curlevel->FindParentObjectByName(L"MousePointer");
	CPlayerScript* PlayerMainScript = GetOwner()->GetScript<CPlayerScript>();
	CMousePointerScript* MouseScript = mouse->GetScript<CMousePointerScript>();
	Vec4 Mousepos = MouseScript->GetMousePos();
	Vec3 OwnerPos = GetOwner()->Transform()->GetRelativePos();

	// Calculate the angle between the player and the mouse
	double dx = Mousepos.x - OwnerPos.x;
	double dy = Mousepos.y - OwnerPos.y;
	double angle = atan2(dy, dx) * 180 / XM_PI;

	// Convert the angle to a direction
	if (angle > -45 && angle <= 45) {
		PlayerMainScript->SetPlayerDir(DIR_RIGHT);
	}
	else if (angle > 45 && angle <= 135) {
		PlayerMainScript->SetPlayerDir(DIR_UP);
	}
	else if (angle > 135 || angle <= -135) {
		PlayerMainScript->SetPlayerDir(DIR_LEFT);
	}
	else {
		PlayerMainScript->SetPlayerDir(DIR_DOWN);
	}
}


