#include "pch.h"
#include "CEditorObjMgr.h"
#include "CEditorObjMgr.h"

#include "CGameObjectEx.h"
#include <Engine\components.h>

#include <Engine\CResMgr.h>
#include <Engine\CRenderMgr.h>
#include <Engine\CTimeMgr.h>
#include <Engine\CKeyMgr.h>
#include <Engine/CEventMgr.h>

#include <Script\CCameraMoveScript.h>

#include <Engine/CTimeMgr.h>

#include "CLevelSaveLoad.h"

#include "ImGuiMgr.h"
#include "InspectorUI.h"

CEditorObjMgr::CEditorObjMgr()
	: m_DebugShape{}
{

}

CEditorObjMgr::~CEditorObjMgr()
{
	Safe_Del_Vec(m_vecEditorObj);
	Safe_Del_Array(m_DebugShape);
}

void CEditorObjMgr::init()
{
	// 디버그 쉐이프 생성
	m_DebugShape[(UINT)SHAPE_TYPE::RECT] = new CGameObjectEx;
	m_DebugShape[(UINT)SHAPE_TYPE::RECT]->AddComponent(new CTransform);
	m_DebugShape[(UINT)SHAPE_TYPE::RECT]->AddComponent(new CMeshRender);
	m_DebugShape[(UINT)SHAPE_TYPE::RECT]->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh_Debug"));
	Ptr<CMaterial> mat = CResMgr::GetInst()->FindRes<CMaterial>(L"material\\DebugShapeMtrl.mtrl");
	m_DebugShape[(UINT)SHAPE_TYPE::RECT]->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"material\\DebugShapeMtrl.mtrl"));

	m_DebugShape[(UINT)SHAPE_TYPE::CIRCLE] = new CGameObjectEx;
	m_DebugShape[(UINT)SHAPE_TYPE::CIRCLE]->AddComponent(new CTransform);
	m_DebugShape[(UINT)SHAPE_TYPE::CIRCLE]->AddComponent(new CMeshRender);
	m_DebugShape[(UINT)SHAPE_TYPE::CIRCLE]->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"CircleMesh_Debug"));
	m_DebugShape[(UINT)SHAPE_TYPE::CIRCLE]->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"material\\DebugShapeMtrl.mtrl"));

	// EditorObject 생성
	CGameObjectEx* pEditorCamObj = new CGameObjectEx;
	pEditorCamObj->AddComponent(new CTransform);
	pEditorCamObj->AddComponent(new CCamera);
	pEditorCamObj->AddComponent(new CCameraMoveScript);

	pEditorCamObj->Camera()->SetLayerMaskAll(true);
	pEditorCamObj->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);


	m_vecEditorObj.push_back(pEditorCamObj);
	CRenderMgr::GetInst()->RegisterEditorCamera(pEditorCamObj->Camera());
}



void CEditorObjMgr::progress()
{
	// DebugShape 정보 가져오기
	vector<tDebugShapeInfo>& vecInfo = CRenderMgr::GetInst()->GetDebugShapeInfo();
	m_DebugShapeInfo.insert(m_DebugShapeInfo.end(), vecInfo.begin(), vecInfo.end());
	vecInfo.clear();


	tick();

	render();
}


void CEditorObjMgr::tick()
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

	

	//play,pause전환
	if (KEY_TAP(KEY::F8))
	{
		if (pCurLevel->GetState() == LEVEL_STATE::STOP)
		{
			//stop->play
			CTimeMgr::GetInst()->SetTimeScale(1.f);
			if (pCurLevel->GetName() == L"")
			{
				wchar_t szStr[256] = {};
				wsprintf(szStr, L"레벨 이름 없음 / 레벨을 먼저 저장하십시요");
				MessageBox(nullptr, szStr, L"레벨실행 실패.", MB_OK);
				return;
			}
			else {
				CLevelSaveLoad::SaveLevel(pCurLevel->GetName(), pCurLevel);
				CLevelMgr::GetInst()->GetCurLevel()->ChangeState(LEVEL_STATE::PLAY);
			}
			            
			
		}
		else if (pCurLevel->GetState() == LEVEL_STATE::PAUSE)
		{
			//pause->play			
			CTimeMgr::GetInst()->SetTimeScale(1.f);
			CLevelMgr::GetInst()->GetCurLevel()->ChangeState(LEVEL_STATE::PLAY);
		}
		else if (pCurLevel->GetState() == LEVEL_STATE::PLAY)
		{
			//play->pause
			CTimeMgr::GetInst()->SetTimeScale(0.f);
			CLevelMgr::GetInst()->GetCurLevel()->ChangeState(LEVEL_STATE::PAUSE);
		}

	}
	//play,pause -> stop
	if (KEY_TAP(KEY::F9))
	{
		if (pCurLevel->GetState() != LEVEL_STATE::STOP) {
			//플레이중인 레벨을 stop상태로 만들어서 mainCam을 EditorCam으로 전환한다.
			CLevelMgr::GetInst()->GetCurLevel()->ChangeState(LEVEL_STATE::STOP);
			CTimeMgr::GetInst()->SetTimeScale(0.f);
			CLevel* level = CLevelSaveLoad::LoadLevel(pCurLevel->GetName());

			tEvent evn = {};
			evn.Type = EVENT_TYPE::LEVEL_CHANGE;
			evn.wParam = (DWORD_PTR)level;

			CEventMgr::GetInst()->AddEvent(evn);

			//inspector 초기화
			InspectorUI* inspector = (InspectorUI*)ImGuiMgr::GetInst()->FindUI("##Inspector");
			inspector->SetTargetObject(nullptr);
		}
		
	}




	for (size_t i = 0; i < m_vecEditorObj.size(); ++i)
	{
		m_vecEditorObj[i]->tick();
	}

	for (size_t i = 0; i < m_vecEditorObj.size(); ++i)
	{
		m_vecEditorObj[i]->finaltick();
	}

}

void CEditorObjMgr::render()
{
	for (size_t i = 0; i < m_vecEditorObj.size(); ++i)
	{
		m_vecEditorObj[i]->render();
	}

	// DebugShape Render
	CGameObjectEx* pShapeObj = nullptr;

	vector<tDebugShapeInfo>::iterator iter = m_DebugShapeInfo.begin();
	for (; iter != m_DebugShapeInfo.end();)
	{
		switch (iter->eShape)
		{
		case SHAPE_TYPE::RECT:
			pShapeObj = m_DebugShape[(UINT)SHAPE_TYPE::RECT];
			break;
		case SHAPE_TYPE::CIRCLE:
			pShapeObj = m_DebugShape[(UINT)SHAPE_TYPE::CIRCLE];
			break;
		case SHAPE_TYPE::CUBE:
			break;
		case SHAPE_TYPE::SPHERE:
			break;
		}

		//월드 행렬이 단위행렬로 들어오고, pos,scale,rot이 따로 들어올때
		if (iter->matWorld != XMMatrixIdentity())
		{
			pShapeObj->Transform()->SetWorldMat(iter->matWorld);
		}
		else
		{
			pShapeObj->Transform()->SetRelativePos(iter->vWorldPos);
			pShapeObj->Transform()->SetRelativeScale(iter->vWorldScale);
			pShapeObj->Transform()->SetRelativeRot(iter->vWorldRotation);
			pShapeObj->finaltick();
		}

		pShapeObj->MeshRender()->GetMaterial()->SetScalarParam(VEC4_0, &iter->vColor);
		pShapeObj->render();

		iter->fCurTime += DT;
		if (iter->fMaxTime <= iter->fCurTime)
		{
			iter = m_DebugShapeInfo.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

