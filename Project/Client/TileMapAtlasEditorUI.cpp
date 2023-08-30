#include "pch.h"
#include "TileMapAtlasEditorUI.h"

#include <Engine\CGameObject.h>
#include <Engine\CKeyMgr.h>
#include <Engine/CPathMgr.h>
#include <Engine/CResMgr.h>

#include <Engine/CEntity.h>
#include <Engine/CTileMap.h>

#include "ImGuiMgr.h"
#include "TileMapEditorUI.h"

TileMapAtlasEditorUI::TileMapAtlasEditorUI()
	: UI("##TileMapAtlasEditorUI")
	, m_iRow(1)
	, m_iCol(1)
{
}

TileMapAtlasEditorUI::~TileMapAtlasEditorUI()
{
}



void TileMapAtlasEditorUI::tick()
{
}

int TileMapAtlasEditorUI::render_update()
{
	ImGui::PushItemWidth(300.f);
	
	if (ImGui::Button("Apply")) {
		SetActive(false);
		TileMapEditorUI* EditorUI = (TileMapEditorUI*)ImGuiMgr::GetInst()->FindUI("##TileMapEditorUI");
		EditorUI->SetAtlasRowCol(m_iRow, m_iCol);
		EditorUI->SetAtlas(m_pTileMapAtlas);
	}
	if (ImGui::Button("ImageToTilemap")) {
		SetActive(false);
		TileMapEditorUI* EditorUI = (TileMapEditorUI*)ImGuiMgr::GetInst()->FindUI("##TileMapEditorUI");
		EditorUI->SetAtlasRowCol(m_iRow, m_iCol);
		EditorUI->SetAtlas(m_pTileMapAtlas);
		EditorUI->SetImageToAtlas();
	}
	if (ImGui::InputInt("Row", &m_iRow, 1))
	{
		if (m_iRow < 1)
			m_iRow = 1;
	}
	if (ImGui::InputInt("Col", &m_iCol, 1))
	{
		if (m_iCol < 1)
			m_iCol = 1;
	}

	if (ImGui::Checkbox("Grid Enable", &m_bGrid)) {

	}
	ImGuiIO& io = ImGui::GetIO();
	ImGui::Text("AtlasSize : %f, %f", m_pTileMapAtlas->Width(), m_pTileMapAtlas->Height());
	Vec2 Tilesize = Vec2(m_pTileMapAtlas->Width() / m_iCol, m_pTileMapAtlas->Height() / m_iRow);
	ImGui::Text("CurTileSize : %f, %f", Tilesize.x, Tilesize.y);
	ImGui::Text("MousePos : %f, %f", io.MousePos.x, io.MousePos.y);

	ID3D11ShaderResourceView* Atlas = (m_pTileMapAtlas->GetSRV()).Get();
	float AtlasWidth = m_pTileMapAtlas->Width();
	float AtlasHeight = m_pTileMapAtlas->Height();
	static float zoom = 0.5f;

	//Atlas ±×¸®±â
	if (ImGui::BeginChild("image", ImVec2(500.f, 500.f), false, ImGuiWindowFlags_HorizontalScrollbar))
	{

		ImVec2 uv_min = ImVec2(0.0f, 0.0f);                 // Top-left
		ImVec2 uv_max = ImVec2(1.0f, 1.0f);                 // Lower-right
		ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
		ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f); // 50% opaque white
		ImGui::Image((void*)Atlas, ImVec2(AtlasWidth * zoom, AtlasHeight * zoom), uv_min, uv_max, tint_col, border_col);
	
		ImVec2 vMin = ImGui::GetWindowContentRegionMin();
		ImVec2 vMax = ImGui::GetWindowContentRegionMax();
		//ImVec2 test = ImGui::GetWindowContentRegionWidth();
		

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
		
		draw_list->PopClipRect();
		float a = (AtlasWidth * zoom) / m_iCol;
		float b = (AtlasHeight * zoom) / m_iRow;
		
		
		ImVec2 Slice(a,b);
		for (int i = 0; i < m_iRow; ++i) {
			//ImGui::GetBackgroundDrawList()->AddLine(ImVec2(vMin.x - ImGui::GetScrollX(), vMin.y - ImGui::GetScrollY() + Slice.y * i), ImVec2(vMin.x - ImGui::GetScrollX() + AtlasWidth * zoom, vMin.y - ImGui::GetScrollY() + Slice.y * i), IM_COL32(255, 0, 0, 255), 1.0f);
			ImGui::GetForegroundDrawList()->AddLine(ImVec2(vMin.x - ImGui::GetScrollX(), vMin.y - ImGui::GetScrollY() + Slice.y * i), ImVec2(vMin.x - ImGui::GetScrollX() + AtlasWidth * zoom, vMin.y - ImGui::GetScrollY() + Slice.y * i), IM_COL32(255, 0, 0, 255), 1.0f);
		}
		for (int j = 0; j < m_iCol; ++j) {
			//ImGui::GetBackgroundDrawList()->AddLine(ImVec2(vMin.x - ImGui::GetScrollX() + Slice.x * j, vMin.y - ImGui::GetScrollY()), ImVec2(vMin.x - ImGui::GetScrollX() + Slice.x * j, vMin.y - ImGui::GetScrollY() + AtlasHeight * zoom), IM_COL32(255, 0, 0, 255), 1.0f);
			ImGui::GetForegroundDrawList()->AddLine(ImVec2(vMin.x - ImGui::GetScrollX() + Slice.x * j, vMin.y - ImGui::GetScrollY()), ImVec2(vMin.x - ImGui::GetScrollX() + Slice.x * j, vMin.y - ImGui::GetScrollY() + AtlasHeight * zoom), IM_COL32(255, 0, 0, 255), 1.0f);
		}
		
		//ImGui::GetForegroundDrawList()->AddRect(ImVec2(vMin.x, vMin.y), ImVec2(vMin.x + AtlasWidth * zoom, vMin.y + AtlasHeight * zoom), IM_COL32(255, 0, 0, 255), 1.0f);

		
		/*const float GRID_STEP = zoom;
		for (float x = fmodf(Slice.x, GRID_STEP); x < 500.f; x += GRID_STEP)
			ImGui::GetForegroundDrawList()->AddLine(ImVec2(vMin.x + x, vMin.y), ImVec2(vMin.x + x, vMax.y), IM_COL32(255, 0, 0, 255), 1.0f);
		for (float y = fmodf(Slice.y, GRID_STEP); y < 500.f; y += GRID_STEP)
			ImGui::GetForegroundDrawList()->AddLine(ImVec2(vMin.x, vMin.y + y), ImVec2(vMax.x, vMin.y + y), IM_COL32(255, 0, 0, 255), 1.0f);*/
		
	}
	ImGui::EndChild();


	if (ImGui::InputFloat("zoom", &zoom, 0.5f, 1.0f))
	{
		if (zoom < 1.0f)
			zoom = 1.0f;
	}

	if (ImGui::SliderFloat("zoom2", &zoom, 0.5f, 10.f)) {

	};

	return TRUE;
}

