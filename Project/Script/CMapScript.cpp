#include "pch.h"
#include "CMapScript.h"
#include <Engine/CAstarMgr.h>


CMapScript::CMapScript()
	: CScript((UINT)SCRIPT_TYPE::MAPSCRIPT)
{
	AddScriptTexParam(m_pTex, "GroundTex");
	AddScriptParam(SCRIPT_PARAM::TEX, &m_pTex, "BackgroundTex");
}

CMapScript::~CMapScript()
{
}


void CMapScript::begin()
{
	TileMap()->GetDynamicMaterial();
	Ptr<CTexture> tileatlas = TileMap()->GetAtlasTex();
	TileMap()->GetMaterial()->SetTexParam(TEX_0, tileatlas);
	TileMap()->SetCenterPos();
	CAstarMgr::GetInst()->LoadTile(TileMap());
}

void CMapScript::tick()
{
	
}

void CMapScript::SelectTexture(DWORD_PTR _Key)
{
	string strKey = (char*)_Key;
	Ptr<CTexture> pTex = CResMgr::GetInst()->FindRes<CTexture>(wstring(strKey.begin(), strKey.end()));

	MeshRender()->GetMaterial()->SetTexParam(TEX_0, pTex);
}

void CMapScript::SaveToLevelFile(FILE* _File)
{
	/*int TexExist = 0;
	if (m_pTex.Get()) {
		TexExist = 1;
		fwrite(&TexExist, sizeof(int), 1, _File);
		
		wstring TexPath = m_pTex->GetRelativePath();
		SaveWString(TexPath, _File);
	}
	else {
		fwrite(&TexExist, sizeof(int), 1, _File);
	}*/

	
}

void CMapScript::LoadFromLevelFile(FILE* _FILE)
{
	/*int TexExist = 0;
	fread(&TexExist, sizeof(int), 1, _FILE);

	if (TexExist) {
		wstring TexPath;
		LoadWString(TexPath, _FILE);
		m_pTex = CResMgr::GetInst()->Load<CTexture>(wstring(TexPath.begin(), TexPath.end()), wstring(TexPath.begin(), TexPath.end()));
	}*/
}


