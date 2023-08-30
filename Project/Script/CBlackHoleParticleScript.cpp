#include "pch.h"
#include "CBlackHoleParticleScript.h"
#include <Engine/CResMgr.h>
#include <Engine/CRenderMgr.h>
#include <Engine/CCamera.h>
#include <Engine/CDevice.h>
#include <Engine/CEventMgr.h>
CBlackHoleParticleScript::CBlackHoleParticleScript()
	:CScript((UINT)SCRIPT_TYPE::BLACKHOLEPARTICLESCRIPT)
	, m_fRadius(0.5f)
	, m_fForce(300.f)
	, m_fAngle(1.f)
{
	AddScriptParam(SCRIPT_PARAM::VEC2, &m_vPos, "Pos");
	AddScriptParam(SCRIPT_PARAM::VEC2, &m_vMousePos, "MousePos");
}

CBlackHoleParticleScript::~CBlackHoleParticleScript()
{
}

void CBlackHoleParticleScript::begin()
{
	MeshRender()->GetDynamicMaterial();
	Ptr<CTexture> copytex = CResMgr::GetInst()->FindRes<CTexture>(L"RTCopyTex");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, copytex);
}

void CBlackHoleParticleScript::tick()
{
	MeshRender()->GetDynamicMaterial();
	Ptr<CTexture> copytex = CResMgr::GetInst()->FindRes<CTexture>(L"RTCopyTex");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, copytex);

	Vec3 ParentPos = m_pBlackOwner->Transform()->GetRelativePos();
	Transform()->SetRelativePos(ParentPos);

	//Scale키우기
	m_fAngle += DT;
	Vec3 Scale = Transform()->GetRelativeScale();
	Scale.x += DT * 200;
	Scale.y += DT * 200;
	if (Scale.x > 400.f || Scale.y > 400.f) {
		DestroyObject(GetOwner());
		DestroyObject(m_pBlackOwner);
	}
	Transform()->SetRelativeScale(Scale);


	m_vPos = Vec2(Transform()->GetRelativePos().x ,Transform()->GetRelativePos().y);
	CCamera* MainCam = CRenderMgr::GetInst()->GetMainCam();
	Matrix CamWorld = MainCam->Transform()->GetWorldMat();
	if (MainCam) {
		Matrix CamWorldInv = CamWorld.Invert();
		m_vPos = XMVector3TransformCoord(m_vPos, MainCam->GetViewMat());
		Matrix MatProj = MainCam->GetProjMat();
		D3D11_VIEWPORT viewport = CDevice::GetInst()->GetViewport();
		m_vPos.x = (m_vPos.x * MatProj._11 + 1.0f) * viewport.Width / 2.0f;
		m_vPos.y = (m_vPos.y * MatProj._22 - 1.0f) * viewport.Height / -2.0f;
	}

	
	MeshRender()->GetMaterial()->SetScalarParam(VEC2_0, &m_vPos);
	MeshRender()->GetMaterial()->SetScalarParam(FLOAT_0, &m_fRadius);
	MeshRender()->GetMaterial()->SetScalarParam(FLOAT_1, &m_fAngle);
}

void CBlackHoleParticleScript::BeginOverlap(CCollider2D* _Other)
{
	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
	if (Curlevel->GetLayer(_Other->GetOwner()->GetLayerIndex())->GetName() == L"MonsterHitBox") {
		CGameObject* Monster = _Other->GetOwner()->GetParent();
		//몬스터 당기기
		Monster->RigidBody()->SetVelocity(Vec2(0.f, 0.f));
		Vec3 MonsterPos = Monster->Transform()->GetRelativePos();
		Vec3 CenterPos = Transform()->GetRelativePos();
		Vec3 Direction = Vec3(CenterPos.x - MonsterPos.x , CenterPos.y - MonsterPos.y, 1.f);
		
		float tmpx = Direction.x / Transform()->GetRelativeScale().x;
		float tmpy = Direction.y / Transform()->GetRelativeScale().y;
		float x =  (Direction.x / Transform()->GetRelativeScale().x) * m_fForce;
		float y = (Direction.y / Transform()->GetRelativeScale().y) * m_fForce;
		Direction = Direction.Normalize();
		Monster->RigidBody()->AddVelocity(Vec2(x, y));
	}
}

void CBlackHoleParticleScript::OnOverlap(CCollider2D* _Other)
{
	CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
	if (Curlevel->GetLayer(_Other->GetOwner()->GetLayerIndex())->GetName() == L"MonsterHitBox") {
		CGameObject* Monster = _Other->GetOwner()->GetParent();
		//몬스터 당기기
		Monster->RigidBody()->SetVelocity(Vec2(0.f, 0.f));
		Vec3 MonsterPos = Monster->Transform()->GetRelativePos();
		Vec3 CenterPos = Transform()->GetRelativePos();
		Vec3 Direction = Vec3(CenterPos.x - MonsterPos.x, CenterPos.y - MonsterPos.y, 1.f);

		float x = (Direction.x / Transform()->GetRelativeScale().x) * m_fForce;
		float y = (Direction.y / Transform()->GetRelativeScale().y) * m_fForce;
		Direction = Direction.Normalize();
		Monster->RigidBody()->AddVelocity(Vec2(x, y));
	}
}

void CBlackHoleParticleScript::EndOverlap(CCollider2D* _Other)
{
}

void CBlackHoleParticleScript::init()
{

}


