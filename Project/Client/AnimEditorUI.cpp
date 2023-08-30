#include "pch.h"
#include "AnimEditorUI.h"

#include <Engine\CGameObject.h>
#include <Engine\CKeyMgr.h>
#include <Engine/CPathMgr.h>
#include <Engine/CResMgr.h>

#include <Engine/CEntity.h>
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim2D.h>

struct Point
{
	int x;
	int y;
};


AnimEditorUI::AnimEditorUI()
	: UI("##AnimEditorUI")
	, m_iAtlasNum(0)
	, m_bDrawBox(false)
	, m_iLinearFrmCount(1)
	, m_fDuration(0.1f)
	, m_bGrid(false)
	, m_bDivideByPixel(false)
	, m_bSelectBFS(false)
	
{
	SetName("AnimEditor");
	//m_pAnimAtlas = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\link.png");
	m_pAnim = new CAnim2D;
	
}

AnimEditorUI::~AnimEditorUI()
{
	delete m_pAnim;
}

void AnimEditorUI::tick()
{

}

int AnimEditorUI::render_update()
{
	ImGui::PushItemWidth(500.f);
	ChooseAtlas();
	if (m_pAnimAtlas.Get() == nullptr) return TRUE;
	ImGui::PushItemWidth(300.f);
	//Load Atlas Button
	ImGui::SameLine();
	if (ImGui::Button("LoadAtlas")) {
		AddAtlas();
	}

	//Save Animation Button
	ImGui::SameLine();
	if (ImGui::Button("SaveAnimation")) {
		SaveAnimation();
	}
	ImGui::SameLine();
	if (ImGui::Button("LoadAnimation")) {
		LoadAnimation();
	}
	//Add Frm Button
	
	if (ImGui::Button("Add Frm")) {
		AddFrm();
	}
	ImGui::SameLine();
	if (ImGui::Button("Add Frm From Here")) {
		AddFrmFromCur();
	}
	ImGui::SameLine();
	if (ImGui::Button("Edit CurFrm")) {
		EditFrm();
	}
	ImGui::SameLine();
	if (ImGui::Button("Remove CurFrm")) {
		RemoveFrm();
	}
	ImGui::SameLine();
	if (ImGui::Button("Remove EveryFrm")) {
		RemoveEveryFrm();
	}

	if (ImGui::Button("Set Duration")) {
		SetDuration();
	}
	ImGui::SameLine();
	if (ImGui::Checkbox("Linear AddOption", &m_bLinearCut)) {
		m_iLinearFrmCount = 1;
		m_vSpace = ImVec2(0.f, 0.f);
	}
	ImGui::SameLine();
	if (ImGui::Checkbox("Grid Enable", &m_bGrid)) {
		
	}

	ImGui::SameLine();
	if (ImGui::Checkbox("Divide By Pixel", &m_bDivideByPixel)) {

	}
	if (ImGui::Checkbox("SelectWithBFS", &m_bSelectBFS)) {

	}

	



	ImVec2 UISize = ImGui::GetWindowSize();
	ImVec2 size = ImGui::GetContentRegionAvail();
	float AtlasWidth = m_pAnimAtlas->Width();
	float AtlasHeight = m_pAnimAtlas->Height();
	ImGui::Text("Atlas width = %.1f , %.1f", AtlasWidth, AtlasHeight);
	ImGui::SameLine();
	ImGui::Text("CurFrm : %d", m_iCurAnimNum);
	ImGui::Separator();
	
	ID3D11ShaderResourceView* Atlas = (m_pAnimAtlas->GetSRV()).Get();
	static float zoom = 0.5f;
	
	//Atlas 그리기
	if (ImGui::BeginChild("image",ImVec2(500.f,500.f), false, ImGuiWindowFlags_HorizontalScrollbar))
	{
		ImGuiIO& io = ImGui::GetIO();
		{
			
			ImVec2 uv_min = ImVec2(0.0f, 0.0f);                 // Top-left
			ImVec2 uv_max = ImVec2(1.0f, 1.0f);                 // Lower-right
			ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
			ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f); // 50% opaque white
			ImGui::Image((void*)Atlas, ImVec2(AtlasWidth * zoom, AtlasHeight * zoom), uv_min, uv_max, tint_col, border_col);
		}

		m_vAtlasRegionMin = ImGui::GetWindowContentRegionMin();
		m_vAtlasWindowPos = ImGui::GetWindowPos();
		ImVec2 vMin = ImGui::GetWindowContentRegionMin();
		ImVec2 vMax = ImGui::GetWindowContentRegionMax();

		vMin.x += ImGui::GetWindowPos().x + ImGui::GetScrollX(); 
		vMin.y += ImGui::GetWindowPos().y + ImGui::GetScrollY();
		vMax.x += ImGui::GetWindowPos().x + ImGui::GetScrollX();
		vMax.y += ImGui::GetWindowPos().y + ImGui::GetScrollY();
		
		ImDrawList* draw_list = ImGui::GetWindowDrawList();

		draw_list->PushClipRect(vMin, vMax, false);
		static ImVec2 scrolling(0.0f, 0.0f);
		static ImVector<ImVec2> points;
		if (m_bGrid)
		{
			const float GRID_STEP = zoom;
			for (float x = fmodf(scrolling.x, GRID_STEP); x < 500.f; x += GRID_STEP)
				draw_list->AddLine(ImVec2(vMin.x + x, vMin.y), ImVec2(vMin.x + x, vMax.y), IM_COL32(200, 200, 200, 40));
			for (float y = fmodf(scrolling.y, GRID_STEP); y < 500.f; y += GRID_STEP)
				draw_list->AddLine(ImVec2(vMin.x, vMin.y + y), ImVec2(vMax.x, vMin.y + y), IM_COL32(200, 200, 200, 40));
		}
		/*for (int n = 0; n < points.Size; n += 2)
			draw_list->AddLine(ImVec2(origin.x + points[n].x, origin.y + points[n].y), ImVec2(origin.x + points[n + 1].x, origin.y + points[n + 1].y), IM_COL32(255, 255, 0, 255), 2.0f);*/
		draw_list->PopClipRect();

		ImGui::GetForegroundDrawList()->AddRect(vMin, vMax, IM_COL32(255, 255, 0, 255));

		//box가 그려져있으면 scroll에 따라 box가 움직여줘야함
		if (m_bDrawBox) {
			m_vMouseStartPos.x = ImGui::GetWindowContentRegionMin().x + ImGui::GetWindowPos().x  + m_vAnimLeftTop.x * zoom;
			m_vMouseStartPos.y = ImGui::GetWindowContentRegionMin().y + ImGui::GetWindowPos().y  + m_vAnimLeftTop.y * zoom;
			m_vMouseEndPos.x = m_vMouseStartPos.x + m_vAnimSlice.x * zoom;
			m_vMouseEndPos.y = m_vMouseStartPos.y + m_vAnimSlice.y * zoom;
		}
		

		// Box그리기
		if (ImGui::IsItemHovered()) {
			if (m_bSelectBFS) {
				if (ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
					float x = (io.MousePos.x - (m_vAtlasRegionMin.x + m_vAtlasWindowPos.x)) / zoom;
					float y = (io.MousePos.y - (m_vAtlasRegionMin.y + m_vAtlasWindowPos.y)) / zoom;
						
					GetAlphaBoundary(x,y,zoom);
					m_bDrawBox = true;
				}
			}
			else {
				if (ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
					m_bDrawBox = false;
					m_vMouseStartPos = io.MousePos;
				}

				if (ImGui::IsMouseDown(ImGuiMouseButton_Right))
				{
					ImGui::GetForegroundDrawList()->AddRect(m_vMouseStartPos, io.MousePos, IM_COL32(255, 255, 0, 255), 1.0f);
				}
				if (ImGui::IsMouseReleased(ImGuiMouseButton_Right)) {
					m_vMouseEndPos = io.MousePos;
					m_bDrawBox = true;

				}
			}

			


		}
		if (m_bDrawBox) {
			if (m_bLinearCut) {
				ImGui::GetForegroundDrawList()->AddRect(m_vMouseStartPos, m_vMouseEndPos, IM_COL32(255, 0, 0, 255), 1.0f);
				for (int i = 1; i < m_iLinearFrmCount; ++i) {
					ImGui::GetForegroundDrawList()->AddRect(ImVec2((m_vSpace.x + m_vAnimSlice.x)*i*zoom + m_vMouseStartPos.x, m_vMouseStartPos.y)
														,ImVec2((m_vSpace.x + m_vAnimSlice.x) * i*zoom + m_vMouseEndPos.x, m_vMouseEndPos.y), IM_COL32(255, 0, 0, 255), 1.0f);
				}
			}
			else {
				ImGui::GetForegroundDrawList()->AddRect(m_vMouseStartPos, m_vMouseEndPos, IM_COL32(255, 0, 0, 255), 1.0f);
			}
			
		}
	}
	ImGui::EndChild();

	//Anim Preview

	ImGui::SameLine();
	ImVec2 uv_min = ImVec2((m_vMouseStartPos.x - (m_vAtlasRegionMin.x + m_vAtlasWindowPos.x)) / AtlasWidth / zoom,
		(m_vMouseStartPos.y - (m_vAtlasRegionMin.y + m_vAtlasWindowPos.y)) / AtlasHeight / zoom);                 // Top-left
	ImVec2 uv_max = ImVec2((m_vMouseEndPos.x - (m_vAtlasRegionMin.x + m_vAtlasWindowPos.x)) / AtlasWidth / zoom,
		(m_vMouseEndPos.y - (m_vAtlasRegionMin.y + m_vAtlasWindowPos.y)) / AtlasHeight / zoom);                 // Lower-right
	ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
	ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f); // 50% opaque white

	m_vAnimSlice = Vec2((uv_max.x - uv_min.x) * AtlasWidth, (uv_max.y - uv_min.y) * AtlasHeight);
	m_vAnimLeftTop = Vec2((m_vMouseStartPos.x - (m_vAtlasRegionMin.x + m_vAtlasWindowPos.x)) / zoom,
		(m_vMouseStartPos.y - (m_vAtlasRegionMin.y + m_vAtlasWindowPos.y)) / zoom);
	ImGui::Image((void*)Atlas, ImVec2((m_vMouseEndPos.x - m_vMouseStartPos.x) / zoom, (m_vMouseEndPos.y - m_vMouseStartPos.y) / zoom)
		, uv_min, uv_max, tint_col, border_col);
	
	


	

	

	if (ImGui::InputFloat("zoom", &zoom, 0.5f, 1.0f))
	{
		if (zoom < 1.0f)
			zoom = 1.0f;
		m_vMouseStartPos.x = m_vAtlasRegionMin.x + m_vAtlasWindowPos.x + m_vAnimLeftTop.x * zoom;
		m_vMouseStartPos.y = m_vAtlasRegionMin.y + m_vAtlasWindowPos.y + m_vAnimLeftTop.y * zoom;
		m_vMouseEndPos.y = m_vMouseStartPos.y + m_vAnimSlice.y * zoom;
		m_vMouseEndPos.x = m_vMouseStartPos.x + m_vAnimSlice.x * zoom;
	}
	
	if(ImGui::SliderFloat("zoom2", &zoom, 0.5f, 10.f)) {
		m_vMouseStartPos.x = m_vAtlasRegionMin.x + m_vAtlasWindowPos.x + m_vAnimLeftTop.x * zoom;
		m_vMouseStartPos.y = m_vAtlasRegionMin.y + m_vAtlasWindowPos.y + m_vAnimLeftTop.y * zoom;
		m_vMouseEndPos.y = m_vMouseStartPos.y + m_vAnimSlice.y * zoom;
		m_vMouseEndPos.x = m_vMouseStartPos.x + m_vAnimSlice.x * zoom;
	};

	//if (ImGui::DragFloat("BoxLeftTop.x", &m_vMouseStartPos.x)) {
	//	m_vAnimLeftTop.x = (m_vMouseStartPos.x - (m_vAtlasRegionMin.x + m_vAtlasWindowPos.x)) / zoom;
	//}
	//ImGui::SameLine();
	//if(ImGui::DragFloat("BoxLeftTop.y", &m_vMouseStartPos.y)) {
	//	m_vAnimLeftTop.y = (m_vMouseStartPos.y - (m_vAtlasRegionMin.y + m_vAtlasWindowPos.y)) / zoom;
	//}
	//
	//if (ImGui::DragFloat("BoxRightBottom.x", &m_vMouseEndPos.x)) {
	//	m_vAnimSlice.x = (m_vMouseEndPos.x - m_vMouseStartPos.x) / zoom;
	//}
	//ImGui::SameLine();
	//if(ImGui::DragFloat("BoxRightBottom.y", &m_vMouseEndPos.y)) {
	//	m_vAnimSlice.y = (m_vMouseEndPos.y - m_vMouseStartPos.y) / zoom;
	//}

	if(ImGui::DragFloat("AnimLeftTop.x", &m_vAnimLeftTop.x)){
		m_vMouseStartPos.x = m_vAtlasRegionMin.x + m_vAtlasWindowPos.x + m_vAnimLeftTop.x * zoom;
		m_vMouseEndPos.x = m_vMouseStartPos.x + m_vAnimSlice.x * zoom;
	}
	ImGui::SameLine();
	if (ImGui::DragFloat("AnimLeftTop.y", &m_vAnimLeftTop.y)) {
		m_vMouseStartPos.y = m_vAtlasRegionMin.y + m_vAtlasWindowPos.y + m_vAnimLeftTop.y * zoom;
		m_vMouseEndPos.y = m_vMouseStartPos.y + m_vAnimSlice.y * zoom;
	}

	if (ImGui::DragFloat("AnimSlice.x", &m_vAnimSlice.x)) {
		m_vMouseEndPos.x = m_vMouseStartPos.x + m_vAnimSlice.x * zoom;
	}
	ImGui::SameLine();
	if(ImGui::DragFloat("AnimSlice.y", &m_vAnimSlice.y)) {
		m_vMouseEndPos.y = m_vMouseStartPos.y + m_vAnimSlice.y * zoom;
	}
	ImGui::InputFloat("Duration", &m_fDuration, 0.1f, 1.0f);
	ImGui::SliderFloat("Duration2", &m_fDuration, 0.0f, 1.0f);

	if (m_bLinearCut) {
		if (ImGui::InputInt("Linear Frm Count", &m_iLinearFrmCount)) {
			if (m_iLinearFrmCount < 1) {
				m_iLinearFrmCount = 1;
			}
		}
		ImGui::DragFloat2("Space Between Frm", (float*)&m_vSpace);
	}

	if (m_bDivideByPixel) {
		m_vMouseStartPos = ImVec2(round(m_vMouseStartPos.x), round(m_vMouseStartPos.y));
		m_vMouseEndPos = ImVec2(round(m_vMouseEndPos.x), round(m_vMouseEndPos.y));
		m_vBackSize.x = round(m_vBackSize.x);
		m_vBackSize.y = round(m_vBackSize.y);
		m_vAnimLeftTop.x = round(m_vAnimLeftTop.x);
		m_vAnimLeftTop.y = round(m_vAnimLeftTop.y);
		m_vAnimSlice.x = round(m_vAnimSlice.x);
		m_vAnimSlice.y = round(m_vAnimSlice.y);
		m_vOffset.x = round(m_vOffset.x);
		m_vOffset.y = round(m_vOffset.y);
		m_vSpace = ImVec2(round(m_vSpace.x), round(m_vSpace.y));
				
	}
	
	ImGui::Text("BackSize : %.1f, %.1f", m_vBackSize.x, m_vBackSize.y);

	DrawFrmList();
	

	
	return TRUE;
}

void AnimEditorUI::ChooseAtlas()
{
	const map<wstring, Ptr<CRes>>& ResTex = CResMgr::GetInst()->GetResources(RES_TYPE::TEXTURE);
	Clear();
	for (const auto& pair : ResTex)
	{
		AddItem(string(pair.first.begin(), pair.first.end()));
	}
	vector<string> TexVec = GetTexData();

	vector<const char*> v2;
	v2.reserve(TexVec.size());
	std::transform(TexVec.begin(), TexVec.end(), std::back_inserter(v2), [](const std::string& str) { return str.c_str(); });


	static int atlas_idx = 0;

	/*if (ResTex.size() == 0) {
		m_pAnimAtlas = CResMgr::GetInst()->FindRes<CTexture>(L"Link");
	}*/


	static ImGuiComboFlags flags = 0;
	if (ImGui::BeginCombo("ChooseAtlas", TexVec[atlas_idx].c_str(), flags)) {
		for (int i = 0; i < v2.size(); ++i) {
			const bool is_selected = (atlas_idx == i);
			if (ImGui::Selectable(v2[i], is_selected))
				atlas_idx = i;


			if (ImGui::IsItemHovered() &&
				ImGui::IsMouseClicked(ImGuiMouseButton_::ImGuiMouseButton_Left))

			{
				TexVec[i].c_str();
				string strKey = (char*)TexVec[i].c_str();
				m_pAnimAtlas = CResMgr::GetInst()->FindRes<CTexture>(wstring(strKey.begin(), strKey.end()));
			}


			// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
}


void AnimEditorUI::AddAtlas()
{
	// open a file name
	OPENFILENAME ofn = {};

	wstring strAnimationFolderPath = CPathMgr::GetInst()->GetContentPath();
	strAnimationFolderPath += L"texture\\";

	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"ALL\0*.*";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = strAnimationFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetOpenFileName(&ofn))
		return;

	szFilePath;
	wstring filePath = wstring(szFilePath);
	wstring targetPath = filePath.substr(filePath.find(L"texture\\"));

	wstring filename;

	size_t pos1 = filePath.rfind(L"\\");
	size_t pos2 = filePath.find(L".");
	if (pos1 != std::wstring::npos && pos2 != std::wstring::npos) {
		filename = filePath.substr(pos1 + 1, pos2 - (pos1 + 1));
	}

	CResMgr::GetInst()->Load<CTexture>(targetPath, targetPath);
}

void AnimEditorUI::RemoveAtlas()
{
}

void AnimEditorUI::RemoveFrm()
{
	m_vecFrm.erase(m_vecFrm.begin() + m_iCurAnimNum);
	CheckBacksize();
}

void AnimEditorUI::RemoveEveryFrm()
{
	m_vecFrm.clear();
	m_vBackSize = Vec2(0.f, 0.f);
}

void AnimEditorUI::AddFrm()
{
	if (m_bLinearCut) {
		tAnim2DFrm frm = {};

		frm.fDuration = m_fDuration;
		frm.LeftTopUV = Vec2(m_vAnimLeftTop.x, m_vAnimLeftTop.y) / Vec2(m_pAnimAtlas->Width(), m_pAnimAtlas->Height());
		frm.SliceUV = m_vAnimSlice / Vec2(m_pAnimAtlas->Width(), m_pAnimAtlas->Height());


		m_vecFrm.push_back(frm);

		for (int i = 1; i < m_iLinearFrmCount; ++i) {
			tAnim2DFrm frm = {};

			frm.fDuration = m_fDuration;
			frm.LeftTopUV = Vec2((m_vSpace.x + m_vAnimSlice.x) * i + m_vAnimLeftTop.x, m_vAnimLeftTop.y) / Vec2(m_pAnimAtlas->Width(), m_pAnimAtlas->Height());
			frm.SliceUV = m_vAnimSlice / Vec2(m_pAnimAtlas->Width(), m_pAnimAtlas->Height());


			m_vecFrm.push_back(frm);
		}

		CheckBacksize();
	}
	else {
		tAnim2DFrm frm = {};

		frm.fDuration = m_fDuration;
		frm.LeftTopUV = Vec2(m_vAnimLeftTop.x, m_vAnimLeftTop.y) / Vec2(m_pAnimAtlas->Width(), m_pAnimAtlas->Height());
		frm.SliceUV = m_vAnimSlice / Vec2(m_pAnimAtlas->Width(), m_pAnimAtlas->Height());

		CheckBacksize();

		m_vecFrm.push_back(frm);
		
	}
	
}

void AnimEditorUI::AddFrmFromCur()
{
	m_vBackSize = Vec2(0.f, 0.f);
	if (m_bLinearCut) {
		tAnim2DFrm frm = {};

		frm.fDuration = m_fDuration;
		frm.LeftTopUV = Vec2(m_vAnimLeftTop.x, m_vAnimLeftTop.y) / Vec2(m_pAnimAtlas->Width(), m_pAnimAtlas->Height());
		frm.SliceUV = m_vAnimSlice / Vec2(m_pAnimAtlas->Width(), m_pAnimAtlas->Height());

		
		m_vecFrm.insert(m_vecFrm.begin() + m_iCurAnimNum, frm);
		for (int i = 1; i < m_iLinearFrmCount; ++i) {
			tAnim2DFrm frm = {};

			frm.fDuration = m_fDuration;
			frm.LeftTopUV = Vec2((m_vSpace.x + m_vAnimSlice.x) * i + m_vAnimLeftTop.x, (m_vSpace.y + m_vAnimSlice.y) * i + m_vAnimLeftTop.y) / Vec2(m_pAnimAtlas->Width(), m_pAnimAtlas->Height());
			frm.SliceUV = m_vAnimSlice / Vec2(m_pAnimAtlas->Width(), m_pAnimAtlas->Height());
			m_vecFrm.insert(m_vecFrm.begin() + m_iCurAnimNum, frm);
		}
		CheckBacksize();
	}
	else {
		tAnim2DFrm frm = {};

		frm.fDuration = m_fDuration;
		frm.LeftTopUV = Vec2(m_vAnimLeftTop.x, m_vAnimLeftTop.y) / Vec2(m_pAnimAtlas->Width(), m_pAnimAtlas->Height());
		frm.SliceUV = m_vAnimSlice / Vec2(m_pAnimAtlas->Width(), m_pAnimAtlas->Height());

		if (m_vBackSize.x < m_vAnimSlice.x) m_vBackSize.x = m_vAnimSlice.x;
		if (m_vBackSize.y < m_vAnimSlice.y) m_vBackSize.y = m_vAnimSlice.y;
		m_vecFrm.insert(m_vecFrm.begin() + m_iCurAnimNum, frm);
		CheckBacksize();
	}
	
}

void AnimEditorUI::EditFrm()
{
	tAnim2DFrm frm = {};

	frm.fDuration = m_fDuration;
	frm.LeftTopUV = Vec2(m_vAnimLeftTop.x, m_vAnimLeftTop.y) / Vec2(m_pAnimAtlas->Width(), m_pAnimAtlas->Height());
	frm.SliceUV = m_vAnimSlice / Vec2(m_pAnimAtlas->Width(), m_pAnimAtlas->Height());

	if (m_vBackSize.x < m_vAnimSlice.x) m_vBackSize.x = m_vAnimSlice.x;
	if (m_vBackSize.y < m_vAnimSlice.y) m_vBackSize.y = m_vAnimSlice.y;
	vector<tAnim2DFrm>::iterator iter = m_vecFrm.begin();
	iter += m_iCurAnimNum;
	(*iter).fDuration = frm.fDuration;
	(*iter).LeftTopUV = frm.LeftTopUV;
	(*iter).Offset	 = frm.Offset;
	(*iter).SliceUV = frm.SliceUV;

	CheckBacksize();

}

void AnimEditorUI::SaveAnimation()
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

	if (false == GetSaveFileName(&ofn))
		return;

	szFilePath;
	wstring filePath = wstring(szFilePath);
	int length = filePath.length();
	if (length < 5 || filePath.substr(length - 5) != L".anim") {
		filePath.append(L".anim");
	}
	wstring targetPath = filePath.substr(filePath.find(L"animation\\"));

	
	wstring temp = targetPath;
	wstring animname = L"";
	animname = temp.erase(0, 10);

	//애니메이션 파일경로로 애니메이션 이름을 정하는 함수, 애니메이션은 무조건 폴더 안에 있어야한다.
	animname.erase(animname.find(L".anim"));
	reverse(animname.begin(), animname.end());
	animname.erase(animname.find(L"\\"));
	reverse(animname.begin(), animname.end());
	animname;

	m_pAnim->SetName(animname);
	Vec2 size = Vec2(m_vBackSize.x / m_pAnimAtlas->Width(), m_vBackSize.y / m_pAnimAtlas->Height());
	m_pAnim->SetBackSize(size);
	m_pAnim->SetAtlasTex(m_pAnimAtlas);
	
	targetPath;

	vector<tAnim2DFrm>::iterator iter = m_vecFrm.begin();
	m_pAnim->GetFrmListRef().clear();
	
	for (int i = 0; i < m_vecFrm.size(); ++i) {
		tAnim2DFrm frm = {};
		frm.fDuration = (*iter).fDuration;
		frm.LeftTopUV = (*iter).LeftTopUV;
		frm.SliceUV = (*iter).SliceUV;
		frm.Offset = (*iter).Offset;
		m_pAnim->GetFrmListRef().push_back(frm);
		++iter;
	}
	m_pAnim->Save(targetPath);
}

void AnimEditorUI::LoadAnimation()
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


	m_pAnim->Load(targetPath);
	m_iCurAnimNum = 0;
	m_pAnimAtlas = m_pAnim->GetAtlasTex();
	m_vecFrm.clear();
	m_vecFrm = m_pAnim->GetFrmList();
	m_vBackSize = m_pAnim->GetBackSize() * Vec2(m_pAnimAtlas->Width(), m_pAnimAtlas->Height());
	/*vector<tAnim2DFrm>::iterator iter = m_pAnim->GetFrmList().begin();
	for (int i = 0; i < m_pAnim->GetFrmList().size(); ++i) {
		
		tAnim2DFrm frm = {};
		frm.fDuration = (*iter).fDuration;
		frm.LeftTopUV = (*iter).LeftTopUV;
		frm.SliceUV = (*iter).SliceUV;
		frm.Offset = (*iter).Offset;

		
		m_vecFrm.push_back(frm);
		++iter;
	}*/
	
}

void AnimEditorUI::DrawFrmList()
{
	
	ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	
	if(ImGui::BeginChild("FrmList", ImVec2(600.f,100.f),false, ImGuiWindowFlags_HorizontalScrollbar)) {
		for (int i = 0; i < m_vecFrm.size(); ++i) {
			vector<tAnim2DFrm>::iterator iter = m_vecFrm.begin();
			iter += i;
			Vec2 resolution = Vec2(m_pAnimAtlas->Width(), m_pAnimAtlas->Height());
			ID3D11ShaderResourceView* Atlas = (m_pAnimAtlas->GetSRV()).Get();
			string id = "FrmNum" + std::to_string(i);
			if (i == m_iCurAnimNum) {
				bg_col = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
				tint_col = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
			}
			else {
				bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
				tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
			}
			//iter->SliceUV.x* resolution.x, iter->SliceUV.y* resolution.y
			if (ImGui::ImageButton(id.c_str(), Atlas, ImVec2(100.f, 100.f),
				ImVec2(iter->LeftTopUV.x, iter->LeftTopUV.y), ImVec2(iter->LeftTopUV.x + iter->SliceUV.x, iter->LeftTopUV.y + iter->SliceUV.y)
				, bg_col, tint_col)) {
				m_vAnimSlice = iter->SliceUV * resolution;
				m_vAnimLeftTop = iter->LeftTopUV * resolution;
				m_fDuration = iter->fDuration;
				m_iCurAnimNum = i;
			}
			if (i != m_vecFrm.size() - 1) {
				ImGui::SameLine();
			}
		}
	}
	ImGui::EndChild();
	
}

void AnimEditorUI::SetDuration()
{
	vector<tAnim2DFrm>::iterator iter = m_vecFrm.begin();
	for (int i = 0; i < m_vecFrm.size(); ++i) {
		(*iter).fDuration = m_fDuration;
		++iter;
	}
	
}

void AnimEditorUI::CheckBacksize()
{
	m_vBackSize = Vec2(0.f, 0.f);
	for (int i = 0; i < m_vecFrm.size(); ++i)
	{
		tAnim2DFrm frm = m_vecFrm[i];
		if (m_vBackSize.x < m_vAnimSlice.x) m_vBackSize.x = m_vAnimSlice.x;
		if (m_vBackSize.y < m_vAnimSlice.y) m_vBackSize.y = m_vAnimSlice.y;
	}
}

bool AnimEditorUI::CheckAlpha(unsigned char* data, int x, int y, int width, int height)
{
	int offset = y * width * 4 + x * 4;
	unsigned char alpha = *(unsigned char*)(data + offset + 3);
	return alpha > 0;
}

void AnimEditorUI::GetAlphaBoundary(int x, int y, float _zoom)
{
	vector<Vec2> boundary;
	queue<Vec2> q;
	int minX = INT_MAX;
	int maxX = INT_MIN;
	int minY = INT_MAX;
	int maxY = INT_MIN;
	vector<Vec2> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
	q.push({ x, y });
	
	

	int width = m_pAnimAtlas->GetScratchWidth();
	int height = m_pAnimAtlas->GetScratchHeight();
	unsigned char* data = m_pAnimAtlas->GetScratchPixelData();
	
	vector<vector<bool>> visited(width, vector<bool>(height, false));
	visited[x][y] = true;

	int a = 0;

	while (!q.empty())
	{
		Vec2 p = q.front();
		q.pop();

		if (p.x < minX) minX = p.x;
		if (p.x > maxX) maxX = p.x;
		if (p.y < minY) minY = p.y;
		if (p.y > maxY) maxY = p.y;

		boundary.push_back(p);

		for (Vec2 direction : directions)
		{
			int newX = p.x + direction.x;
			int newY = p.y + direction.y;
			if (CheckBoundaries(newX, newY, width, height) && CheckAlpha(data, newX, newY, width, height) && !visited[newX][newY])
			{
				q.push({ newX, newY });
				visited[newX][newY] = true;
			}
		}
	}
	
	
	m_vAnimLeftTop = Vec2(minX, minY); //ImVec2(minX, minY);
	m_vAnimSlice = Vec2(maxX - minX, maxY - minY);
	m_vMouseStartPos.x = m_vAtlasRegionMin.x + m_vAtlasWindowPos.x + m_vAnimLeftTop.x * _zoom;
	m_vMouseStartPos.y = m_vAtlasRegionMin.y + m_vAtlasWindowPos.y + m_vAnimLeftTop.y * _zoom;
	m_vMouseEndPos.y = m_vMouseStartPos.y + m_vAnimSlice.y * _zoom;
	m_vMouseEndPos.x = m_vMouseStartPos.x + m_vAnimSlice.x * _zoom;
}

