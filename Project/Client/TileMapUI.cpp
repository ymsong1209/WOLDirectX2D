#include "pch.h"
#include "TileMapUI.h"

#include <Engine/CPathMgr.h>
#include <Engine/CResMgr.h>
#include <Engine/CTileMap.h>

TileMapUI::TileMapUI()
    : ComponentUI("##TileMap", COMPONENT_TYPE::TILEMAP)
{
    SetName("TileMap");
}

TileMapUI::~TileMapUI()
{
}

int TileMapUI::render_update()
{
    if (FALSE == ComponentUI::render_update())
        return FALSE;

    if (ImGui::Button("LoadTileMap##LoadTileMap")) {
        LoadTile();
    }


    return TRUE;
}

void TileMapUI::LoadTile()
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

	/*FILE* pFile = nullptr;
	_wfopen_s(&pFile, szFilePath, L"rb");*/

	GetTarget()->TileMap()->Load(targetPath);
}
