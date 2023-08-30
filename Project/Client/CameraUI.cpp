#include "pch.h"
#include "CameraUI.h"
#include <Engine/CRenderMgr.h>
#include <Engine/CCamera.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>

CameraUI::CameraUI()
    : ComponentUI("##Camera", COMPONENT_TYPE::CAMERA)
	, m_iCameraMask(0)
{
    SetName("Camera");
}

CameraUI::~CameraUI()
{
}

int CameraUI::render_update()
{
    if (FALSE == ComponentUI::render_update())
        return FALSE;
	//Camera Index-----------//
	ImGui::Text("Camera Index : ");
	ImGui::SameLine();
	int CamIdx = GetTarget()->Camera()->GetCameraIndex();
	if (ImGui::InputInt("##CameraIndex", &CamIdx)) {
		GetTarget()->Camera()->SetCameraIndex(CamIdx);
	}

	//SetMainCam--------//
	if (ImGui::Button("SetMainCam")) {
		GetTarget()->Camera()->SetCameraIndex(CamIdx);
	}
	//Proj Type------------//
	ImGui::Text("Proj Type : ");
	ImGui::SameLine();
	string projtype;
	if (GetTarget()->Camera()->GetProjType() == PROJ_TYPE::ORTHOGRAPHIC) {
		projtype = "OrthoGraphic";
	}
	else if (GetTarget()->Camera()->GetProjType() == PROJ_TYPE::PERSPECTIVE) {
		projtype == "Perspective";
	}
	if (ImGui::Button(projtype.c_str())) {
		if (GetTarget()->Camera()->GetProjType() == PROJ_TYPE::ORTHOGRAPHIC) {
			GetTarget()->Camera()->SetProjType(PROJ_TYPE::PERSPECTIVE);
		}
		else if (GetTarget()->Camera()->GetProjType() == PROJ_TYPE::PERSPECTIVE) {
			GetTarget()->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
		}
	}

	//LayerMask---------------//
	UINT layermask = GetTarget()->Camera()->GetLayerMask();
	ImGui::Text("SetLayerMaskAll");
	ImGui::SameLine();
	if (ImGui::Button("True##Setlayermaskall")) {
		GetTarget()->Camera()->SetLayerMaskAll(true);
	}
	ImGui::SameLine();
	if (ImGui::Button("False##Setlayermaskall")) {
		GetTarget()->Camera()->SetLayerMaskAll(false);
	}

	ImGui::Text("Visible List");
	ImGui::Text("SetLayerMask : ");
	ImGui::SameLine();
	if (ImGui::InputInt("##SetLayerMask", &m_iCameraMask)) {
		if (m_iCameraMask < MAX_LAYER && 0<= m_iCameraMask) {
			
		}
		else {
			wchar_t szStr[256] = {};
			wsprintf(szStr, L"Max Layer를 초과한 값이 들어왔습니다.");
			MessageBox(nullptr, szStr, L"LayerMask 설정 실패.", MB_OK);
			m_iCameraMask = 0;
		}
	}
	ImGui::SameLine();
	if (ImGui::Button("True##SetLayerMask")) {

		// 레이어 마스크 확인
		if (layermask & (1 << m_iCameraMask))
		{
			wchar_t szStr[256] = {};
			wsprintf(szStr, L"현재 레이어가 이미 True상태입니다.");
			MessageBox(nullptr, szStr, L"LayerMask 설정 실패.", MB_OK);
		}
		else {
			GetTarget()->Camera()->SetLayerMask(m_iCameraMask, true);
		}
		
	}
	ImGui::SameLine();
	if (ImGui::Button("False##SetLayerMask")) {
		if (!(layermask & (1 << m_iCameraMask))) {
			wchar_t szStr[256] = {};
			wsprintf(szStr, L"현재 레이어가 이미 False상태입니다.");
			MessageBox(nullptr, szStr, L"LayerMask 설정 실패.", MB_OK);
		}
		else {
			GetTarget()->Camera()->SetLayerMask(m_iCameraMask, false);
		}
	}

	int scale = 0;
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		
		// 레이어 마스크 확인
		if (layermask & (1 << i))
		{
			CLevel* Curlevel = CLevelMgr::GetInst()->GetCurLevel();
			CLayer* layer = Curlevel->GetLayer(i);
			string layername =  string(layer->GetName().begin(), layer->GetName().end());
			if (layername.empty()) {
				string totalname = std::to_string(i) + " Layer : Empty Layer";
				ImGui::Text(totalname.c_str());
			}
			else {
				string totalname = std::to_string(i) + " Layer : " + layername;
				ImGui::Text(totalname.c_str());
			}
			
			++scale;
		}
		
	}
	
	SetSize(0.f, ImGui::GetTextLineHeight() * (scale+10));


    return TRUE;
}