#include "pch.h"
#include "CChaosBombScript.h"
#include "CBlackHoleParticleScript.h"
CChaosBombScript::CChaosBombScript()
	:CScript((UINT)SCRIPT_TYPE::WATERBOMBSCRIPT)
	, m_fShootSpeed(0.f)
	, m_fForce(50.f)
	, m_fScale(1.f)
	, m_bReady(false)
	, m_bCreateEffect(false)
{
}

CChaosBombScript::~CChaosBombScript()
{
}

void CChaosBombScript::begin()
{
	Animator2D()->LoadAnim(L"animation\\particle\\ChaosBall.anim");
	Animator2D()->Play(L"ChaosBall", true);
}

void CChaosBombScript::tick()
{
	m_fScale += DT * 60;
	m_fShootSpeed += DT * 1400;
	if (!m_bReady) {
		if (m_fScale > 80.f) m_fScale = 80.f;
	}
	//던졌을때
	else {
		//착지했을때 크기가 커진다.
		if (m_bCreateEffect) {
			//m_fScale += DT * 60;
			if (m_fScale > 80.f)m_fScale = 80.f;
		}
		else {
			if (m_fScale > 80.f) m_fScale = 80.f;
		}
	
	}
	if (m_fShootSpeed > 1500.f) m_fShootSpeed = 1500.f;
	Transform()->SetRelativeScale(Vec3(m_fScale, m_fScale, 1.f));

	if (m_bReady) {
		Vec2 vel = RigidBody()->GetVelocity();
		if ((vel.x == 0.f || vel.y == 0.f) && !m_bCreateEffect) {
			m_bCreateEffect = true;
			CGameObject* Distortion = new CGameObject;
			Distortion->SetName(L"Chaos Distortion");
			Distortion->AddComponent(new CTransform);
			Distortion->AddComponent(new CMeshRender);
			Distortion->AddComponent(new CCollider2D);
			Distortion->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"CircleMesh"));
			Distortion->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"material\\BlackHoleMtrl.mtrl"));
			Distortion->Collider2D()->SetAbsolute(false);
			Distortion->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::CIRCLE);
			Distortion->Collider2D()->SetOffsetScale(Vec2(1.f, 1.f));
			Distortion->AddComponent(new CBlackHoleParticleScript);
			CBlackHoleParticleScript* ParticleScript = Distortion->GetScript<CBlackHoleParticleScript>();
			ParticleScript->SetBlackOwner(GetOwner());
			SpawnGameObject(Distortion, Vec3(0.f,0.f,0.f), L"Default");
		}

		//데미지 넣기, state바꾸기
		if (m_bCreateEffect) {

		}
	}

}

void CChaosBombScript::BeginOverlap(CCollider2D* _Other)
{
	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();

	if (Curlevel->GetLayer(_Other->GetOwner()->GetLayerIndex())->GetName() == L"Wall") {
		RigidBody()->SetVelocity(Vec2(0.f, 0.f));

		// Calculate the direction from the wall to the player
		Matrix MatColliderPos = Collider2D()->GetColliderPosMat();
		Vec3 ColliderPos = Transform()->GetRelativePos() + Collider2D()->GetOffsetPos();
		Matrix MatWallColliderPos = _Other->GetColliderPosMat();
		Vec3 WallColliderPos = _Other->Transform()->GetRelativePos() + _Other->GetOffsetPos();

		Vec3 direction = WallColliderPos - ColliderPos;
		direction.Normalize();
		// Calculate the magnitude of the force based on the collider sizes and player speed
		Matrix MatColliderScale = Collider2D()->GetColliderScaleMat();
		Vec3 ColliderScale = Vec3(MatColliderScale._11, MatColliderScale._22, MatColliderScale._33);
		Matrix MatWallColliderScale = _Other->GetColliderScaleMat();
		Vec3 WallColliderScale = Vec3(MatWallColliderScale._11, MatWallColliderScale._22, MatWallColliderScale._33);

		float x;
		float y;
		float xratio = 0.f;
		float yratio = 0.f;

		// wall이 오른쪽에 있는 경우
		if (ColliderPos.x < WallColliderPos.x) {
			x = WallColliderPos.x - WallColliderScale.x / 2.0f - ColliderScale.x / 2.0f;
			xratio = (WallColliderPos.x - ColliderPos.x) / (WallColliderScale.x / 2.0f + ColliderScale.x / 2.0f);
		}
		//wall이 왼쪽에 있는 경우
		else {
			x = WallColliderPos.x + WallColliderScale.x / 2.0f + ColliderScale.x / 2.0f;
			xratio = (ColliderPos.x - WallColliderPos.x) / (WallColliderScale.x / 2.0f + ColliderScale.x / 2.0f);
		}

		//wall이 위쪽에 있는 경우
		if (ColliderPos.y < WallColliderPos.y) {
			y = WallColliderPos.y - WallColliderScale.y / 2.0f - ColliderScale.y / 2.0f;
			yratio = (WallColliderPos.y - ColliderPos.y) / (WallColliderScale.y / 2.0f + ColliderScale.y / 2.0f);
		}
		//wall이 아래쪽에 있는 경우
		else {
			y = WallColliderPos.y + WallColliderScale.y / 2.0f + ColliderScale.y / 2.0f;
			yratio = (ColliderPos.y - WallColliderPos.y) / (WallColliderScale.y / 2.0f + ColliderScale.y / 2.0f);
		}
		//x가 더 크다 -> 왼쪽이나 오른쪽으로 밀면됨
		if (xratio > yratio) {
			Transform()->SetRelativePos(Vec3(x - Collider2D()->GetOffsetPos().x,
				Transform()->GetRelativePos().y,
				Transform()->GetRelativePos().z));
		}
		else {
			Transform()->SetRelativePos(Vec3(Transform()->GetRelativePos().x,
				y - Collider2D()->GetOffsetPos().y,
				Transform()->GetRelativePos().z));
		}
	}
}

void CChaosBombScript::OnOverlap(CCollider2D* _Other)
{
	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
	RigidBody()->SetVelocity(Vec2(0.f, 0.f));
	if (Curlevel->GetLayer(_Other->GetOwner()->GetLayerIndex())->GetName() == L"Wall") {
		// Calculate the direction from the wall to the player
		Matrix MatColliderPos = Collider2D()->GetColliderPosMat();
		Vec3 ColliderPos = Transform()->GetRelativePos() + Collider2D()->GetOffsetPos();
		Matrix MatWallColliderPos = _Other->GetColliderPosMat();
		Vec3 WallColliderPos = _Other->Transform()->GetRelativePos() + _Other->GetOffsetPos();

		Vec3 direction = WallColliderPos - ColliderPos;
		direction.Normalize();
		// Calculate the magnitude of the force based on the collider sizes and player speed
		Matrix MatColliderScale = Collider2D()->GetColliderScaleMat();
		Vec3 ColliderScale = Vec3(MatColliderScale._11, MatColliderScale._22, MatColliderScale._33);
		Matrix MatWallColliderScale = _Other->GetColliderScaleMat();
		Vec3 WallColliderScale = Vec3(MatWallColliderScale._11, MatWallColliderScale._22, MatWallColliderScale._33);

		float x;
		float y;
		float xratio = 0.f;
		float yratio = 0.f;

		// wall이 오른쪽에 있는 경우
		if (ColliderPos.x < WallColliderPos.x) {
			x = WallColliderPos.x - WallColliderScale.x / 2.0f - ColliderScale.x / 2.0f;
			xratio = (WallColliderPos.x - ColliderPos.x) / (WallColliderScale.x / 2.0f + ColliderScale.x / 2.0f);
		}
		//wall이 왼쪽에 있는 경우
		else {
			x = WallColliderPos.x + WallColliderScale.x / 2.0f + ColliderScale.x / 2.0f;
			xratio = (ColliderPos.x - WallColliderPos.x) / (WallColliderScale.x / 2.0f + ColliderScale.x / 2.0f);
		}

		//wall이 위쪽에 있는 경우
		if (ColliderPos.y < WallColliderPos.y) {
			y = WallColliderPos.y - WallColliderScale.y / 2.0f - ColliderScale.y / 2.0f;
			yratio = (WallColliderPos.y - ColliderPos.y) / (WallColliderScale.y / 2.0f + ColliderScale.y / 2.0f);
		}
		//wall이 아래쪽에 있는 경우
		else {
			y = WallColliderPos.y + WallColliderScale.y / 2.0f + ColliderScale.y / 2.0f;
			yratio = (ColliderPos.y - WallColliderPos.y) / (WallColliderScale.y / 2.0f + ColliderScale.y / 2.0f);
		}
		//x가 더 크다 -> 왼쪽이나 오른쪽으로 밀면됨
		if (xratio > yratio) {
			Transform()->SetRelativePos(Vec3(x - Collider2D()->GetOffsetPos().x,
				Transform()->GetRelativePos().y,
				Transform()->GetRelativePos().z));
		}
		else {
			Transform()->SetRelativePos(Vec3(Transform()->GetRelativePos().x,
				y - Collider2D()->GetOffsetPos().y,
				Transform()->GetRelativePos().z));
		}
	}
}

void CChaosBombScript::EndOverlap(CCollider2D* _Other)
{
}

void CChaosBombScript::ShootBomb(Vec3 _Direction)
{
	m_fScale = 80.f;
	m_vDirection = _Direction;
	GetOwner()->AddComponent(new CCollider2D);
	Collider2D()->SetAbsolute(false);
	Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::CIRCLE);
	Collider2D()->SetOffsetScale(Vec2(1.f, 1.f));

	GetOwner()->AddComponent(new CRigidBody);
	RigidBody()->AddVelocity(Vec2(_Direction.Normalize().x * m_fShootSpeed, _Direction.Normalize().y * m_fShootSpeed));

	m_bReady = true;
}


