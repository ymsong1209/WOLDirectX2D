#include "pch.h"
#include "TileMapEditorUI.h"
#include "ImGuiMgr.h"
#include "TileMapAtlasEditorUI.h"


#include <Engine\CGameObject.h>
#include <Engine\CKeyMgr.h>
#include <Engine/CPathMgr.h>
#include <Engine/CResMgr.h>

#include <Engine/CEntity.h>
#include <Engine/CTileMap.h>
#include <Engine/CTexture.h>

TileMapEditorUI::TileMapEditorUI()
	: UI("##TileMapEditorUI")
	, m_iRow(1)
	, m_iCol(1)
	, m_bTilePropertyButton(false)
	, m_iTileType(0)

{
	SetName("TileMapEditorUI");
	IdlePushBack();
	m_pTileMap = new CTileMap;
}

TileMapEditorUI::~TileMapEditorUI()
{
	delete m_pTileMap;
}





void TileMapEditorUI::tick()
{

}

int TileMapEditorUI::render_update()
{
	if (ImGui::Button("Load Texture")) {
		LoadTexture();
		//SetAtlasInfo();
	}
	ImGui::SameLine();
	if (ImGui::Button("Save TileMap")) {
		SaveTileMap();
	}
	ImGui::SameLine();
	if (ImGui::Button("LoadTileMap")) {
		LoadTileMap();
	}
	ImGui::SameLine();
	if (ImGui::Button("SelectTile")) {
		m_bAtlasButton = !m_bAtlasButton;
	}
	//Tile속성 Edit
	ImGui::Text("Tile Property Edit mode : ");
	ImGui::SameLine();
	string boolTileProperty;
	if (m_bTilePropertyButton) {
		boolTileProperty = "True##TilePropertyMode";
	}
	else {
		boolTileProperty = "False##TilePropertyMode";
	}
	if (ImGui::Button(boolTileProperty.c_str())) {
		m_bTilePropertyButton = !m_bTilePropertyButton;
	}

	if (m_bTilePropertyButton) {
		ImGui::Text("Current Tile Type");
		vector<string> TileTypeName;
		TileTypeName.push_back("Default");
		TileTypeName.push_back("Ground");
		TileTypeName.push_back("Pit");

		if (ImGui::BeginCombo("##ChooseTileType", TileTypeName[m_iTileType].c_str(), ImGuiComboFlags_None)) {
			for (UINT i = 0; i < TileTypeName.size(); i++) {
				const bool is_left_selected = (m_iTileType == i);
				if (TileTypeName[i] != "") {
					if (ImGui::Selectable(TileTypeName[i].c_str(), is_left_selected)) {
						m_iTileType = i;
					}
				}
				// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
				if (is_left_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}
	}

	//Row Col 설정
	ImGui::PushItemWidth(300.f);
	if (ImGui::InputInt("Row", &m_iRow, 1))
	{
		if (m_iRow < 1)
			m_iRow = 1;
		while (m_vecTile.size() <= m_iRow * m_iCol) {
			IdlePushBack();
		}
	}
	if (ImGui::InputInt("Col", &m_iCol, 1))
	{
		if (m_iCol < 1)
			m_iCol = 1;
		while (m_vecTile.size() <= m_iRow * m_iCol) {
			IdlePushBack();
		}
		
	}

	ImGui::Text("Current TileNum : %d", m_iCurTile);

	SetAtlasInfo();

	DrawAtlasSlice();

	DrawTileMap();

	
	return TRUE;
}

void TileMapEditorUI::LoadTexture()
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

	
	CResMgr::GetInst()->Load<CTexture>(filename, targetPath);
	Ptr<CTexture> atlas = CResMgr::GetInst()->FindRes<CTexture>(filename);
	

	TileMapAtlasEditorUI* AtlasEditorUI = (TileMapAtlasEditorUI*)ImGuiMgr::GetInst()->FindUI("##TileMapAtlasEditorUI");
	ImGuiMgr::GetInst()->FindUI("##TileMapAtlasEditorUI");
	AtlasEditorUI->SetTexture(atlas);
	AtlasEditorUI->SetActive(true);
}

void TileMapEditorUI::SaveTileMap()
{
	// open a file name
	OPENFILENAME ofn = {};

	wstring strAnimationFolderPath = CPathMgr::GetInst()->GetContentPath();
	strAnimationFolderPath += L"tile\\";

	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"tile\0*.tile\0ALL\0*.*";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = strAnimationFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetSaveFileName(&ofn))
		return;

	szFilePath;
	wstring filePath = wstring(szFilePath);
	wstring targetPath = filePath.substr(filePath.find(L"tile\\"));

	wstring temp = targetPath;
	wstring tilename = L"";
	tilename = temp.erase(0, 5);
	tilename.erase(tilename.find(L".tile"));
	reverse(tilename.begin(), tilename.end());
	tilename.erase(tilename.find(L"\\"));
	reverse(tilename.begin(), tilename.end());


	Vec2 sliceSize = Vec2(m_vSliceSize.x, m_vSliceSize.y);
	m_pTileMap->SetName(tilename);
	m_pTileMap->SetSliceSize(sliceSize);
	m_pTileMap->SetTileCount(m_iCol, m_iRow);
	m_pTileMap->SetTile(m_vecTile);
	m_pTileMap->SetTilemapAtlas(m_pTileMapAtlas);
	m_pTileMap->SetAtlasTileCount(m_iAtlasCol, m_iAtlasRow);

	m_pTileMap->Save(targetPath);

}

void TileMapEditorUI::LoadTileMap()
{
	// open a file name
	OPENFILENAME ofn = {};

	wstring strAnimationFolderPath = CPathMgr::GetInst()->GetContentPath();
	strAnimationFolderPath += L"tile\\";

	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"tile\0*.tile\0ALL\0*.*";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = strAnimationFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetOpenFileName(&ofn))
		return;

	szFilePath;
	wstring filePath = wstring(szFilePath);
	wstring targetPath = filePath.substr(filePath.find(L"tile\\"));


	if (m_pTileMap->GetMaterial() == nullptr) {
		m_pTileMap->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"material\\TileMapMtrl.mtrl"));
	}
	m_pTileMap->Load(targetPath);


	m_iCurTile = 0;
	m_pTileMapAtlas = m_pTileMap->GetAtlasTex();
	m_vecTile.clear();
	m_vecTile = m_pTileMap->GetTile();
	m_iAtlasCol =  m_pTileMap->GetAtlasTileCountX();
	m_iAtlasRow =  m_pTileMap->GetAtlasTileCountY();
	m_iCol = m_pTileMap->GetTileCountX();
	m_iRow = m_pTileMap->GetTileCountY();
	m_vSliceSize = m_pTileMap->GetSliceSize();
}

void TileMapEditorUI::SetAtlasInfo()
{
	if (m_pTileMapAtlas == nullptr) return;

	m_vecAtlasInfo.clear();

	m_fAtlasWidth = m_pTileMapAtlas->Width();
	m_fAtlasHeight = m_pTileMapAtlas->Height();


	float slicex = (m_fAtlasWidth / m_iAtlasCol) / m_fAtlasWidth;
	float slicey = (m_fAtlasHeight / m_iAtlasRow) / m_fAtlasHeight;
	m_vSliceSize = Vec2(slicex, slicey);
	vector<tTile>::iterator iter = m_vecAtlasInfo.begin();
	//iter->vLeftTop
	for (int i = 0; i < m_iAtlasRow; ++i) {
		for (int j = 0; j < m_iAtlasCol; ++j) {
			tTile tile;
			tile.vLeftTop = Vec2(m_vSliceSize.x * j, m_vSliceSize.y * i);
			tile.vSlice = m_vSliceSize;
			m_vecAtlasInfo.push_back(tile);
		}
	}

}

void TileMapEditorUI::SetImageToAtlas()
{
	m_iRow = m_iAtlasRow;
	m_iCol = m_iAtlasCol;
	m_vecTile.clear();

	for (int i = 0; i < m_iRow; ++i) {
		for (int j = 0; j < m_iCol; ++j) {
			tTile tile;
			float x = 1.0 / m_iCol;
			float y = 1.0 / m_iRow;
			tile.vLeftTop = Vec2(x * j, y * i);
			tile.vSlice = Vec2(x, y);
			tile.Type = 0;

			m_vecTile.push_back(tile);
		}
	
	}

	
}

void TileMapEditorUI::DrawAtlasSlice()
{
	ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	if (!m_bAtlasButton) return;

	//ImGui::BeginChild("AtlasSlices", ImVec2(m_fAtlasWidth, m_fAtlasHeight), false, ImGuiWindowFlags_HorizontalScrollbar)
	if (ImGui::Begin("AtlasSlices", &m_bAtlasButton, ImGuiWindowFlags_HorizontalScrollbar)) {
		for (int i = 0; i < m_iAtlasRow; ++i) {
			for (int j = 0; j < m_iAtlasCol; ++j) {
				vector<tTile>::iterator iter = m_vecAtlasInfo.begin();
				int num = i * m_iAtlasCol + j;
				iter += num;
				Vec2 resolution = Vec2(m_fAtlasWidth, m_fAtlasHeight);
				ID3D11ShaderResourceView* Atlas = (m_pTileMapAtlas->GetSRV()).Get();
				string id = "AtlasTileFrm" + std::to_string(num);
				if (num == m_iCurTile) {
					bg_col = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
					tint_col = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
				}
				else {
					bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
					tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
				}
				//iter->SliceUV.x* resolution.x, iter->SliceUV.y* resolution.y
				if (ImGui::ImageButton(id.c_str(), Atlas, ImVec2(m_fAtlasWidth / m_iAtlasCol, m_fAtlasHeight / m_iAtlasRow),
					ImVec2(iter->vLeftTop.x, iter->vLeftTop.y), ImVec2(iter->vLeftTop.x + iter->vSlice.x, iter->vLeftTop.y + iter->vSlice.y)
					, bg_col, tint_col)) {
					m_iCurTile = num;
				}
				if (j != m_iAtlasCol - 1) {
					ImGui::SameLine();
				}
			}
		}
	}
	//ImGui::EndChild();
	ImGui::End();
	
}

void TileMapEditorUI::DrawTileMap()
{
	if (m_pTileMapAtlas == nullptr || m_iRow < 1 || m_iCol< 1) return;

	
	float tilemapwidth = m_iCol * 65.f;
	float tilemapheight = m_iRow * 65.f;
	if (ImGui::BeginChild("TileMapSlices", ImVec2(800, 800), false, ImGuiWindowFlags_HorizontalScrollbar)) {
		for (int i = 0; i < m_iRow; ++i) {
			for (int j = 0; j < m_iCol; ++j) {
				vector<tTile>::iterator iter = m_vecTile.begin();
				int num = m_iCol * i + j;
				iter += num;
				ImVec4 bg_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
				ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

				//Tile 속성 모드 킬시, 현재 타일 속성에 따라 배경색 변하게 하기
				if (m_bTilePropertyButton) {
					if ((*iter).Type == 0) {
						bg_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
						tint_col = ImVec4(0.0f, 0.0f, 1.0f, 1.0f);
					}
					else if ((*iter).Type == 1) {
						bg_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
						tint_col = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
					}
					else if ((*iter).Type == 2) {
						bg_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
						tint_col = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
					}
				
				}
				else {
					bg_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
					tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
				}
				
				Vec2 resolution = Vec2(m_fAtlasWidth, m_fAtlasHeight);
				ID3D11ShaderResourceView* Atlas = (m_pTileMapAtlas->GetSRV()).Get();
				string id = "TileFrm" + std::to_string(num);
				
				
				
				ImGui::Image((void*)Atlas, ImVec2(50.f, 50.f),
					ImVec2(iter->vLeftTop.x, iter->vLeftTop.y), ImVec2(iter->vLeftTop.x + iter->vSlice.x, iter->vLeftTop.y + iter->vSlice.y),bg_col, tint_col
				);

				if (ImGui::IsItemHovered() &&
					(ImGui::IsMouseClicked(ImGuiMouseButton_::ImGuiMouseButton_Right)|| ImGui::IsMouseDragging(ImGuiMouseButton_::ImGuiMouseButton_Right)) ) {

					if (m_bTilePropertyButton) {
						(*iter).Type = m_iTileType;						
					}
					else {
						vector<tTile>::iterator atlasiter = m_vecAtlasInfo.begin();
						for (int i = 0; i < m_iCurTile; ++i) ++atlasiter;

						tTile tile;
						tile.vLeftTop = (*atlasiter).vLeftTop;
						tile.vSlice = (*atlasiter).vSlice;

						(*iter).vLeftTop = tile.vLeftTop;
						(*iter).vSlice = tile.vSlice;
					}

					
				}
				if (j != m_iCol - 1) {
					ImGui::SameLine();
				}
				
			}
			
		}
	}
	ImGui::EndChild();
}

void TileMapEditorUI::IdlePushBack()
{
	tTile tile;
	
	m_vecTile.push_back(tile);
}
