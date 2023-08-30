#include "pch.h"
#include "CMeshRender.h"

#include "CTransform.h"
#include "CAnimator2D.h"
CMeshRender::CMeshRender()
	: CRenderComponent(COMPONENT_TYPE::MESHRENDER)
{
}

CMeshRender::~CMeshRender()
{
}

void CMeshRender::finaltick()
{
}

void CMeshRender::render()
{
	//전위연산자이기 때문에 ptr에서 따로 함수 구현하였음.
	if (nullptr == GetMesh() || nullptr == GetMaterial())
		return;

	// Transform 에 UpdateData 요청
	Transform()->UpdateData();

	// Animator2D 컴포넌트가 있다면
	if (Animator2D())
	{
		Animator2D()->UpdateData();
	}

	// 재질을 update하면 texture랑 상수분기점을 update시켜준다.
	GetMaterial()->UpdateData();

	//렌더
	GetMesh()->render();

	// Animation 관련 정보 제거
	if (Animator2D())
		Animator2D()->Clear();
}