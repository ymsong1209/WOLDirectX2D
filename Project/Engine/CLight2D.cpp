#include "pch.h"
#include "CLight2D.h"

#include "CRenderMgr.h"
#include "CTransform.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
CLight2D::CLight2D()
	: CComponent(COMPONENT_TYPE::LIGHT2D)
{
}

CLight2D::~CLight2D()
{
}


void CLight2D::finaltick()
{
	m_LightInfo.vWorldPos = Transform()->GetWorldPos();
	m_LightInfo.vWorldDir = Transform()->GetWorldDir(DIR_TYPE::RIGHT);
	//if (KEY_PRESSED(KEY::_4)) {
	//	float angle = GetAngle();
	//	SetAngle(angle += 100 * DT);
	//	//m_LightInfo.Angle += 100 *DT;
	//}
	//else if (KEY_PRESSED(KEY::_5)) {
	//	float angle = GetAngle();
	//	SetAngle(angle -= 100 * DT);
	//	//m_LightInfo.Angle -= 100 * DT;
	//}
	//else if (KEY_PRESSED(KEY::_6)) {
	//	Vec3 vRot = Transform()->GetRelativeRot();
	//	vRot.z += DT * XM_PI;
	//	Transform()->SetRelativeRot(vRot);
	//}
	//else if (KEY_PRESSED(KEY::_7)) {
	//	Vec3 vRot = Transform()->GetRelativeRot();
	//	vRot.z -= DT * XM_PI;
	//	Transform()->SetRelativeRot(vRot);
	//}

	//m_LightInfo.Angle = m_LightInfo.Angle * XM_PI / 180.f;
	CRenderMgr::GetInst()->RegisterLight2D(m_LightInfo);
}

void CLight2D::SaveToLevelFile(FILE* _File)
{
	fwrite(&m_LightInfo, sizeof(tLightInfo), 1, _File);
}

void CLight2D::LoadFromLevelFile(FILE* _File)
{
	fread(&m_LightInfo, sizeof(tLightInfo), 1, _File);
}