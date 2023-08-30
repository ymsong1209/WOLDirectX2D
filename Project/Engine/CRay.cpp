#include "pch.h"
#include "CRay.h"
#include "CDevice.h"
#include "CCamera.h"
#include "CRenderMgr.h"
#include "CTransform.h"

CRay::CRay()
	: m_vOriginal(0.f, 0.f, 0.f)
	, m_vDirection(0.f, 0.f, 0.f)
	, m_ESpace(ERaySpace::NONE)
{

}


CRay::~CRay()
{
}

void CRay::RayAtViewSpace(int _ScreenX, int _ScreenY)
{
	D3D11_VIEWPORT viewport = CDevice::GetInst()->GetViewport();


	CCamera* camera = nullptr;
	if (CRenderMgr::GetInst()->GetEditorCameraUse()) {
		camera = CRenderMgr::GetInst()->GetEditorCam();
	}
	else {
		camera = CRenderMgr::GetInst()->GetMainCam();
	}
	assert(camera);
	Matrix MatProj = camera->GetProjMat();

	Vec3 direction = Vec3(
		((2.0f * _ScreenX) / viewport.Width - 1.0f) / MatProj._11,
		((-2.0f * _ScreenY) / viewport.Height + 1.0f) / MatProj._22,
		1.0f);
	SetDirection(direction);
	SetSpace(ERaySpace::VIEW);

}

void CRay::RayAtWorldSpace(int _ScreenX, int _ScreenY)
{
	RayAtViewSpace(_ScreenX, _ScreenY);
	CCamera* camera = nullptr;
	if (CRenderMgr::GetInst()->GetEditorCameraUse()) {
		camera = CRenderMgr::GetInst()->GetEditorCam();
	}
	else {
		camera = CRenderMgr::GetInst()->GetMainCam();
	}
	
	assert(camera);
	Matrix MatView = camera->GetViewMat();

	Matrix InvMatView = MatView.Invert();

	Vec3 original = GetOriginal();
	Vec3 direction = GetDirection();
	original = XMVector3TransformCoord(original, InvMatView);
	direction = XMVector3TransformNormal(direction, InvMatView);




	Matrix CamWorld = camera->Transform()->GetWorldMat();

	Matrix CamWorldInv = CamWorld.Invert();
	original = XMVector3TransformCoord(original, CamWorldInv);
	direction = XMVector3TransformCoord(direction, CamWorld);


	SetOriginal(original);
	SetDirection(direction);

	SetSpace(ERaySpace::WORLD);
}