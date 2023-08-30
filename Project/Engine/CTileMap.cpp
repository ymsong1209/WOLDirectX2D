#include "pch.h"
#include "CTileMap.h"


#include "CResMgr.h"
#include "CTransform.h"
#include "CMeshRender.h"

#include "CStructuredBuffer.h"
#include "CTexture.h"
#include "ptr.h"

CTileMap::CTileMap()
	: CRenderComponent(COMPONENT_TYPE::TILEMAP)
	, m_iTileCountX(1)
	, m_iTileCountY(1)
{
	SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"material\\TileMapMtrl.mtrl"));

	m_Buffer = new CStructuredBuffer;
	m_Buffer->Create(sizeof(tTile), m_iTileCountX * m_iTileCountY, SB_TYPE::READ_ONLY, true);
}

CTileMap::CTileMap(const CTileMap& _other)
	: CRenderComponent(COMPONENT_TYPE::TILEMAP)
	, m_iTileCountX(_other.m_iTileCountX)
	, m_iTileCountY(_other.m_iTileCountY)
	, m_iAtlasTileCountX(_other.m_iAtlasTileCountX)
	, m_iAtlasTileCountY(_other.m_iAtlasTileCountY)
	, m_vSliceSize(_other.m_vSliceSize)
{

	for (UINT i = 0; i < _other.m_vecTile.size(); ++i) {
		tTile tile = _other.m_vecTile[i];
		m_vecTile.push_back(tile);
	}

	SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"material\\TileMapMtrl.mtrl"));


	m_Buffer = new CStructuredBuffer;
	m_Buffer->Create(sizeof(tTile), m_iTileCountX * m_iTileCountY, SB_TYPE::READ_ONLY, true);

	m_pAtlas = _other.m_pAtlas;
}

CTileMap::~CTileMap()
{
	if (nullptr != m_Buffer)
		delete m_Buffer;
}

void CTileMap::finaltick()
{
}

void CTileMap::render()
{
	if (nullptr == GetMesh() || nullptr == GetMaterial())
		return;

	// Transform 에 UpdateData 요청
	Transform()->UpdateData();

	// 재질 업데이트
	GetMaterial()->SetScalarParam(INT_0, &m_iTileCountX);
	GetMaterial()->SetScalarParam(INT_1, &m_iTileCountY);
	GetMaterial()->UpdateData();

	// 구조화버퍼 업데이트
	UpdateData();

	// 렌더
	GetMesh()->render();
}

void CTileMap::UpdateData()
{
	m_Buffer->SetData(m_vecTile.data(), sizeof(tTile) * m_vecTile.size());
	m_Buffer->UpdateData(20, PIPELINE_STAGE::PS_PIXEL);
}

void CTileMap::SetTileCount(UINT _iXCount, UINT _iYCount)
{
	m_iTileCountX = _iXCount;
	m_iTileCountY = _iYCount;

	m_vecTile.clear();
	m_vecTile.resize(m_iTileCountX * m_iTileCountY);

	if (m_Buffer->GetElementCount() < m_vecTile.size())
	{
		m_Buffer->Create(sizeof(tTile), (UINT)m_vecTile.size(), SB_TYPE::READ_ONLY, true);
	}

	// 타일 세팅 테스트
	//for (size_t i = 0; i < m_iTileCountY; ++i)
	//{
	//	for (size_t j = 0; j < m_iTileCountX; ++j)
	//	{
	//		m_vecTile[i * m_iTileCountX + j].vLeftTop.x = m_vSliceSize.x * j;
	//		m_vecTile[i * m_iTileCountX + j].vLeftTop.y = 0.f;
	//		m_vecTile[i * m_iTileCountX + j].vSlice = m_vSliceSize;
	//	}
	//}

	//m_vecTile[0].vLeftTop = Vec2(m_vSliceSize.x * 7.f, m_vSliceSize.y * 5.f);
}

void CTileMap::SetCenterPos()
{
	Vec3 TileCenterPos = Transform()->GetRelativePos();
	Vec3 TileScale = Transform()->GetRelativeScale();
	Vec3 TileLeftTopPos = Vec3(TileCenterPos.x - TileScale.x / 2, TileCenterPos.y + TileScale.y / 2, TileCenterPos.z);
	Vec2 ScalePerTile = Vec2(TileScale.x / m_iTileCountX, TileScale.y / m_iTileCountY);
	for (size_t i = 0; i < m_iTileCountY; ++i)
	{
		for (size_t j = 0; j < m_iTileCountX; ++j)
		{
			if (j == 79 && i == 5) {
				int a = 0;
			}
			m_vecTile[i * m_iTileCountX + j].vCenterPos = Vec3(TileLeftTopPos.x + ScalePerTile.x * j + ScalePerTile.x / 2.f,
																TileLeftTopPos.y - ScalePerTile.y * i - ScalePerTile.y / 2.f,
																TileCenterPos.z);
		}
	}
}

void CTileMap::SetTile(vector<tTile> _tile)
{
	//assert(m_iTileCountX * m_iTileCountY >= _tile.size());

	vector<tTile>::iterator iter = _tile.begin();
	vector<tTile>::iterator tilemapiter = m_vecTile.begin();
	for (int i = 0; i < m_iTileCountX * m_iTileCountY; ++i) {
		(*tilemapiter).vLeftTop = (*iter).vLeftTop;
		(*tilemapiter).vSlice = (*iter).vSlice;
		(*tilemapiter).Type = (*iter).Type;
		++iter;
		++tilemapiter;
	}
}

void CTileMap::Save(const wstring& _strRelativePath)
{
	wstring strFilepath = CPathMgr::GetInst()->GetContentPath();
	strFilepath += _strRelativePath;

	// 파일 입출력
	FILE* pFile = nullptr;
	errno_t iErrNum = _wfopen_s(&pFile, strFilepath.c_str(), L"wb");

	if (nullptr == pFile)
	{
		wchar_t szStr[256] = {};
		wsprintf(szStr, L"Tile Save 실패, Error Number : %d", iErrNum);
		MessageBox(nullptr, szStr, L"파일 저장 실패", MB_OK);
		return;
	}

	// TileMap 이름 저장
	fwprintf_s(pFile, L"\n");

	fwprintf_s(pFile, L"[TILEMAP_NAME]\n");
	fwprintf_s(pFile, GetName().c_str());
	fwprintf_s(pFile, L"\n\n");

	// 아틀라스 텍스쳐 키값 저장	
	fwprintf_s(pFile, L"[ATLAS_KEY]\n");
	fwprintf_s(pFile, m_pAtlas->GetRelativePath().c_str());
	fwprintf_s(pFile, L"\n\n");

	fwprintf_s(pFile, L"[ATLAS_PATH]\n");
	fwprintf_s(pFile, m_pAtlas->GetRelativePath().c_str());
	fwprintf_s(pFile, L"\n\n");

	fwprintf_s(pFile, L"[ATLAS_SIZE]\n");
	fwprintf_s(pFile, L"%.1f %.1f\n", m_pAtlas->Width(), m_pAtlas->Height());
	fwprintf_s(pFile, L"\n\n");

	fwprintf_s(pFile, L"[TileCountX]\n");
	fwprintf_s(pFile, L"%d\n", (int)m_iTileCountX);
	fwprintf_s(pFile, L"\n\n");

	fwprintf_s(pFile, L"[TileCountY]\n");
	fwprintf_s(pFile, L"%d\n", (int)m_iTileCountY);
	fwprintf_s(pFile, L"\n\n");

	fwprintf_s(pFile, L"[AtlasTileCountX]\n");
	fwprintf_s(pFile, L"%d\n", (int)m_iAtlasTileCountX);
	fwprintf_s(pFile, L"\n\n");

	fwprintf_s(pFile, L"[AtlasTileCountY]\n");
	fwprintf_s(pFile, L"%d\n", (int)m_iAtlasTileCountY);
	fwprintf_s(pFile, L"\n\n");
	

	fwprintf_s(pFile, L"[Slice_Size]\n");
	fwprintf_s(pFile, L"%f %f\n", m_vSliceSize.x, m_vSliceSize.y);
	fwprintf_s(pFile, L"\n\n");


	// 프레임 정보 저장
	wchar_t szNum[50] = {};

	fwprintf_s(pFile, L"[FRAME_COUNT]\n");

	size_t iTileCount = m_vecTile.size();
	_itow_s((int)iTileCount, szNum, 50, 10);

	fwprintf_s(pFile, szNum);
	fwprintf_s(pFile, L"\n\n");

	for (size_t i = 0; i < iTileCount; ++i)
	{
		fwprintf_s(pFile, L"[%zd_FRAME]\n", i);

		// LEFT_TOP
		fwprintf_s(pFile, L"[LEFT_TOP]\n");
		fwprintf_s(pFile, L"%.1f %.1f\n", m_vecTile[i].vLeftTop.x * m_pAtlas->Width(), m_vecTile[i].vLeftTop.y * m_pAtlas->Height());

		// SIZE
		fwprintf_s(pFile, L"[SIZE]\n");
		fwprintf_s(pFile, L"%.1f %.1f\n", m_vecTile[i].vSlice.x * m_pAtlas->Width(), m_vecTile[i].vSlice.y * m_pAtlas->Height());

		// TileProperty
		fwprintf_s(pFile, L"[Property]\n");
		fwprintf_s(pFile, L"%d\n", m_vecTile[i].Type);
		fwprintf_s(pFile, L"\n");
	}

	fclose(pFile);
}

void CTileMap::Load(const wstring& _strRelativePath)
{
	m_vecTile.clear();
	wstring strFilepath = CPathMgr::GetInst()->GetContentPath();
	strFilepath += _strRelativePath;

	// 파일 입출력
	FILE* pFile = nullptr;
	errno_t iErrNum = _wfopen_s(&pFile, strFilepath.c_str(), L"rb");

	if (nullptr == pFile)
	{
		wchar_t szStr[256] = {};
		wsprintf(szStr, L"TileMap Load 실패, Error Number : %d", iErrNum);
		MessageBox(nullptr, szStr, L"파일 부르기 실패", MB_OK);
		return;
	}

	size_t iTileCount = 0;
	Vec2 AtlasSize = Vec2(0.f, 0.f);
	wstring strAtlasKey;
	wstring strAltasRelativePath;

	while (true)
	{
		wchar_t szBuffer[256] = {};
		fwscanf_s(pFile, L"%s", szBuffer, 256);

		if (!wcscmp(szBuffer, L"[TILEMAP_NAME]"))
		{
			fwscanf_s(pFile, L"%s", szBuffer, 256);
			SetName(szBuffer);
		}

		else if (!wcscmp(szBuffer, L"[ATLAS_KEY]"))
		{
			fwscanf_s(pFile, L"%s", szBuffer, 256);
			strAtlasKey = szBuffer;
		}

		else if (!wcscmp(szBuffer, L"[ATLAS_PATH]"))
		{
			fwscanf_s(pFile, L"%s", szBuffer, 256);
			strAltasRelativePath = szBuffer;
		}
		else if (!wcscmp(szBuffer, L"[ATLAS_SIZE]"))
		{
			fwscanf_s(pFile, L"%f %f", &AtlasSize.x, &AtlasSize.y);
		}
		else if (!wcscmp(szBuffer, L"[TileCountX]"))
		{
			fwscanf_s(pFile, L"%d", &m_iTileCountX);
		}
		else if (!wcscmp(szBuffer, L"[TileCountY]"))
		{
			fwscanf_s(pFile, L"%d", &m_iTileCountY);
		}
		else if (!wcscmp(szBuffer, L"[AtlasTileCountX]"))
		{
			fwscanf_s(pFile, L"%d", &m_iAtlasTileCountX);
		}
		else if (!wcscmp(szBuffer, L"[AtlasTileCountY]"))
		{
			fwscanf_s(pFile, L"%d", &m_iAtlasTileCountY);
		}
		else if (!wcscmp(szBuffer, L"[Slice_Size]"))
		{
			fwscanf_s(pFile, L"%f %f", &m_vSliceSize.x, &m_vSliceSize.y);
			SetTileCount(m_iTileCountX, m_iTileCountY);
			m_vecTile.clear();
		}
		else if (!wcscmp(szBuffer, L"[FRAME_COUNT]"))
		{
			fwscanf_s(pFile, L"%zd", &iTileCount);

			for (size_t i = 0; i < iTileCount; ++i)
			{
				tTile tile = {};

				while (true)
				{
					wchar_t szBuffer[256] = {};
					fwscanf_s(pFile, L"%s", szBuffer, 256);

					if (!wcscmp(szBuffer, L"[LEFT_TOP]"))
					{
						fwscanf_s(pFile, L"%f %f", &tile.vLeftTop.x, &tile.vLeftTop.y);
						tile.vLeftTop /= AtlasSize;
					}

					else if (!wcscmp(szBuffer, L"[SIZE]"))
					{
						fwscanf_s(pFile, L"%f %f", &tile.vSlice.x, &tile.vSlice.y);
						tile.vSlice /= AtlasSize;
					}

					else if (!wcscmp(szBuffer, L"[Property]"))
					{
						
						int i = 0;
						fwscanf_s(pFile, L"%d", &i);
						tile.Type = i;
						break;
					}
				}

				m_vecTile.push_back(tile);
			}

			break;
		}
	}

	m_pAtlas = CResMgr::GetInst()->Load<CTexture>(strAtlasKey, strAltasRelativePath);
	GetMaterial()->SetTexParam(TEX_0, m_pAtlas);

	fclose(pFile);
}


void CTileMap::SaveToLevelFile(FILE* _File)
{
	CRenderComponent::SaveToLevelFile(_File);

	fwrite(&m_iTileCountX, sizeof(UINT), 1, _File);
	fwrite(&m_iTileCountY, sizeof(UINT), 1, _File);
	fwrite(&m_vSliceSize, sizeof(Vec2), 1, _File);
	fwrite(m_vecTile.data(), sizeof(tTile), m_vecTile.size(), _File);
	wstring path = m_pAtlas->GetRelativePath();
	SaveWString(path, _File);
}

void CTileMap::LoadFromLevelFile(FILE* _File)
{
	CRenderComponent::LoadFromLevelFile(_File);

	fread(&m_iTileCountX, sizeof(UINT), 1, _File);
	fread(&m_iTileCountY, sizeof(UINT), 1, _File);
	fread(&m_vSliceSize, sizeof(Vec2), 1, _File);

	SetTileCount(m_iTileCountX, m_iTileCountY);

	fread(m_vecTile.data(), sizeof(tTile), m_iTileCountX * m_iTileCountY, _File);

	wstring strAtlasPath;
	LoadWString(strAtlasPath, _File);

	m_pAtlas = CResMgr::GetInst()->FindRes<CTexture>(strAtlasPath);
	GetDynamicMaterial()->SetTexParam(TEX_0, m_pAtlas);
}
