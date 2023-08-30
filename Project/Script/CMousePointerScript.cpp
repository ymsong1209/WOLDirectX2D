#include "pch.h"
#include "CMousePointerScript.h"

#include <Engine/CKeyMgr.h>
#include <Engine/CDevice.h>
#include <Engine/CTransform.h>
#include <Engine/CCamera.h>

#include <Engine/CRenderMgr.h>

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>
#include <Engine/CGameObject.h>

#include <Engine/CRay.h>


CMousePointerScript::CMousePointerScript()
	: CScript((UINT)SCRIPT_TYPE::MOUSEPOINTERSCRIPT)
{
	m_CRay = new CRay;
	AddScriptParam(SCRIPT_PARAM::VEC4, &m_vMousePos, "MousePos");
	AddScriptParam(SCRIPT_PARAM::VEC4, &m_vConvertedMousePos, "ConvertedMousePos");
}

CMousePointerScript::~CMousePointerScript()
{
	delete m_CRay;
}


void CMousePointerScript::begin()
{
	//GetOwner()->AddComponent(new CMeshRender);
	MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"material\\Std2DMtrl.mtrl"));
	MeshRender()->GetDynamicMaterial();
	Ptr<CTexture> Mouse = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\UI\\MouseCursor.png");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, Mouse);
	int i = 1;
	MeshRender()->GetMaterial()->SetScalarParam(INT_7, &i);

	Transform()->SetRelativeScale(100.f, 100.f, 1.f);
}

void CMousePointerScript::tick()
{
	Vec2 pos = CKeyMgr::GetInst()->GetMousePos();
	m_vMousePos = Vec4(pos.x,pos.y, 1.f,0.f);

	m_CRay->RayAtWorldSpace(m_vMousePos.x, m_vMousePos.y);
	//CRay* r = CRay::RayAtWorldSpace(300.f, 300.f);

	Vec3 RayPos = m_CRay->GetDirection();
	m_vConvertedMousePos = Vec4(RayPos.x, RayPos.y, RayPos.z, 1.f);

	Transform()->SetRelativePos(Vec3(m_vConvertedMousePos.x, m_vConvertedMousePos.y, 1.f));

}

