#include "pch.h"
#include "Animator2DUI.h"

#include <Engine/CResMgr.h>

#include "ImGuiMgr.h"
#include "ContentUI.h"

#include <Engine\CGameObject.h>
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim2D.h>



Animator2DUI::Animator2DUI()
    : ComponentUI("##Animator2D", COMPONENT_TYPE::ANIMATOR2D)
	, m_iAnimNum(0)
	
	, m_bLoop(false)

{
	
    SetName("Animator2D");
}

Animator2DUI::~Animator2DUI()
{
}


int Animator2DUI::render_update()
{
    if (FALSE == ComponentUI::render_update())
        return FALSE;

	m_bLoop = GetTarget()->Animator2D()->GetRepeat();
	m_vAnimList.clear();
	char szBuff[50] = {};
	map<wstring, CAnim2D*> MapAnim = GetTarget()->Animator2D()->GetMapAnim();
	CAnim2D* CurAnim = GetTarget()->Animator2D()->GetCurAnim();

	if (ImGui::Button("Load##LoadButton"))
	{
		LoadAnim();
	}

	if (!CurAnim) {
		return TRUE;
	}
	wstring targetKey = CurAnim->GetName();
	
	static int item_current_idx = 0;
	auto it = MapAnim.find(targetKey);
	if (it != MapAnim.end()) {
		m_iAnimNum = std::distance(MapAnim.begin(), it);
		item_current_idx = m_iAnimNum;
	}

	ImGui::Text("CurAnim");
	ImGui::SameLine();

	const map<wstring, Ptr<CRes>>& ResMtrl = CResMgr::GetInst()->GetResources(RES_TYPE::TEXTURE);
	
	
	for (const auto& pair : MapAnim)
	{
		m_vAnimList.push_back(string(pair.first.begin(), pair.first.end()));
	}

	//std::back_inserter하기 위해선 global.h에 #include <iterator>해야함
	vector<const char*> v2;
	v2.reserve(m_vAnimList.size());
	std::transform(m_vAnimList.begin(), m_vAnimList.end(), std::back_inserter(v2), [](const std::string& str) { return str.c_str(); });
;
	
	static ImGuiComboFlags flags = 0;
	
	if (ImGui::BeginCombo("##CurAnim", m_vAnimList[m_iAnimNum].c_str(), ImGuiComboFlags_PopupAlignLeft)) {
		for (int i = 0; i < v2.size(); ++i) {
			const bool is_selected = (item_current_idx == i);
			if (ImGui::Selectable(v2[i], is_selected))
				item_current_idx = i;

			if (ImGui::IsItemHovered() &&
				ImGui::IsMouseClicked(ImGuiMouseButton_::ImGuiMouseButton_Left))

			{
				
				string strKey = (char*)m_vAnimList[i].c_str();
				wstring wstrKey = wstring(strKey.begin(), strKey.end());
				GetTarget()->Animator2D()->Play(wstrKey, m_bLoop);
			}

			// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
	
	ChooseSamplerState();

	bool animpause = CurAnim->IsPause();
	string PlayButton = "";
	if (animpause) {
		PlayButton = "Play";
	}
	else {
		PlayButton = "Pause";
	}
	PlayButton += "##PlayPause";
	if (ImGui::Button(PlayButton.c_str())) {
		GetTarget()->Animator2D()->Pause();
	}

	ImGui::SameLine();
	if (ImGui::Button("Reset##StopButton"))
	{
		GetTarget()->Animator2D()->Reset();
	}

	ImGui::SameLine();
	
	string LoopButton = "";
	if (m_bLoop) {
		LoopButton = "Loop";
	}
	else {
		LoopButton = "NoLoop";
	}
	LoopButton += "##LoopNoLoop";
	if (ImGui::Button(LoopButton.c_str())) {
		GetTarget()->Animator2D()->SetRepeat(!m_bLoop);
		m_bLoop = !m_bLoop;
	}

	
	
	ImGui::SameLine();
	if (ImGui::Button("Erase##EraseButton"))
	{
		RemoveAnim();
	}
		 
	 
	const tAnim2DFrm& CurFrame = CurAnim->GetCurFrame();
	Ptr<CTexture> AtlasTex = CurAnim->GetAtlasTex();
	ImVec2 vResolution = ImVec2(AtlasTex->Width(), AtlasTex->Height());
	ImVec2 LeftTop = ImVec2(CurFrame.LeftTopUV.x * vResolution.x, CurFrame.LeftTopUV.y * vResolution.y);
	ImVec2 Slice = ImVec2(CurFrame.SliceUV.x * vResolution.x, CurFrame.SliceUV.y * vResolution.y);
	float Duration = CurFrame.fDuration;
	ImVec2 BackSize = ImVec2(CurAnim->GetBackSize().x * vResolution.x, CurAnim->GetBackSize().y * vResolution.y);
	ImGui::Text("CurFrm : %d", CurAnim->GetCurFrameNum());
	ImGui::Text("LeftTop : %.1f, %.1f", LeftTop.x, LeftTop.y);
	ImGui::Text("Slice : %.1f, %.1f", Slice.x, Slice.y);
	ImGui::Text("BackSize : %.1f, %.1f", BackSize.x, BackSize.y);
	ImGui::Text("Duration : %f", Duration);

	ImGui::Text("FramePreview");
	ID3D11ShaderResourceView* AtlasSRV = (AtlasTex->GetSRV()).Get();
	
	ImGui::Image((void*)AtlasSRV, ImVec2(Slice.x,Slice.y),
		ImVec2(CurFrame.LeftTopUV.x , CurFrame.LeftTopUV.y),
		ImVec2(CurFrame.LeftTopUV.x + CurFrame.SliceUV.x, CurFrame.LeftTopUV.y + CurFrame.SliceUV.y));
	
  
    


    return TRUE;
}

void Animator2DUI::LoadAnim()
{
	
	// open a file name
	OPENFILENAME ofn = {};

	wstring strAnimationFolderPath = CPathMgr::GetInst()->GetContentPath();
	strAnimationFolderPath += L"animation\\";

	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"anim\0*.anim\0ALL\0*.*";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = strAnimationFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetOpenFileName(&ofn))
		return;

	szFilePath;
	wstring filePath = wstring(szFilePath);
	wstring targetPath = filePath.substr(filePath.find(L"animation\\"));

	/*FILE* pFile = nullptr;
	_wfopen_s(&pFile, szFilePath, L"rb");*/

	// 마지막 '\\' 문자 이후의 문자열 추출
	std::wstring fileName = filePath.substr(filePath.find_last_of(L"\\") + 1);

	// ".anim" 확장자 제거
	fileName = fileName.substr(0, fileName.size() - 5);

	GetTarget()->Animator2D()->LoadAnim(targetPath);
	GetTarget()->Animator2D()->Play(fileName, m_bLoop);

	//애니메이션이 로딩되면서 텍스쳐도 로딩되었을 수도 있다.
	ContentUI* content = (ContentUI*)ImGuiMgr::GetInst()->FindUI("##Content");
	content->ResetContent();
}

void Animator2DUI::RemoveAnim()
{
	map<wstring, CAnim2D*>& MapAnim = GetTarget()->Animator2D()->GetMapAnim();
	CAnim2D* CurAnim = GetTarget()->Animator2D()->GetCurAnim();
	MapAnim.erase(CurAnim->GetName());
	m_iAnimNum = 0;
	if (MapAnim.size() != 0) {
		
		GetTarget()->Animator2D()->Play(MapAnim.begin()->first.c_str() , m_bLoop);
	}
	else {
		GetTarget()->Animator2D()->SetCurAnim(nullptr);
	}
	
}


void Animator2DUI::ChooseSamplerState()
{
	const char* SamplerType[] = { "ANISOTROPIC", "MIN_MAG_MIP_POINT" };

	int SamplerState = GetTarget()->Animator2D()->GetSamplerState();
	
	static int SamplerState_idx = 0;
	const char* SamplerState_preview_value = SamplerType[SamplerState_idx];
	static ImGuiComboFlags flags = 0;

	ImGui::Text("SamplerType");
	if (ImGui::BeginCombo("##SamplerType", SamplerState_preview_value, flags)) {
		for (int i = 0; i < IM_ARRAYSIZE(SamplerType); i++) {
			const bool is_selected = (SamplerState_idx == i);
			if (ImGui::Selectable(SamplerType[i], is_selected))
				SamplerState_idx = i;


			if (ImGui::IsItemHovered() &&
				ImGui::IsMouseClicked(ImGuiMouseButton_::ImGuiMouseButton_Left))

			{
				GetTarget()->Animator2D()->SetSamplerState(i);
			}

			// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

}