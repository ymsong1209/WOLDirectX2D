#include "pch.h"
#include "CAnim2D.h"
#include "CTimeMgr.h"
#include "CPathMgr.h"
#include "CResMgr.h"

CAnim2D::CAnim2D()
	: m_pOwner(nullptr)
	, m_iCurFrm(0)
	, m_bFinish(false)
	, m_fTime(0.f)
	, m_bPause(false)
{
}

CAnim2D::CAnim2D(const CAnim2D& _other)
	: CEntity(_other)
	, m_pOwner(nullptr)
	, m_vecFrm(_other.m_vecFrm)
	, m_AtlasTex(_other.m_AtlasTex)
	, m_vBackSize(_other.m_vBackSize)
	, m_iCurFrm(_other.m_iCurFrm)
	, m_fTime(_other.m_fTime)
	, m_bFinish(_other.m_bFinish)
	, m_bPause(_other.m_bPause)
	, m_RelativePath(_other.m_RelativePath)
{

}

CAnim2D::~CAnim2D()
{

}

void CAnim2D::finaltick()
{
	if (m_bFinish)
		return;

	//Pause가 false이면 play이므로 애니메이션 시간이 흘러야한다.
	if (!m_bPause) {
		m_fTime += DT;
	}
	

	if (m_vecFrm[m_iCurFrm].fDuration < m_fTime)
	{
		m_fTime = m_fTime - m_vecFrm[m_iCurFrm].fDuration;
		++m_iCurFrm;

		if (m_vecFrm.size() <= m_iCurFrm)
		{
			m_iCurFrm = m_vecFrm.size() - 1;
			m_bFinish = true;
		}
	}
}

void CAnim2D::Create(const wstring& _strAnimName, Ptr<CTexture> _AtlasTex
	, Vec2 _vLeftTop, Vec2 _vSlice, Vec2 _vBackSize, int _FrameCount, int _FPS)
{
	assert(_AtlasTex.Get());

	SetName(_strAnimName);

	m_AtlasTex = _AtlasTex;

	Vec2 vResolution = Vec2(m_AtlasTex->Width(), m_AtlasTex->Height());

	m_vBackSize = _vBackSize / vResolution;

	for (size_t i = 0; i < _FrameCount; ++i)
	{
		tAnim2DFrm frm = {};

		frm.fDuration = 1.f / (float)_FPS;
		frm.LeftTopUV = Vec2(_vLeftTop.x + _vSlice.x * i, _vLeftTop.y) / vResolution;
		frm.SliceUV = _vSlice / vResolution;

		//frm.Offset = Vec2(0.05f, 0.f);

		m_vecFrm.push_back(frm);
	}
}

void CAnim2D::Save(const wstring& _strRelativePath)
{
	wstring strFilepath = CPathMgr::GetInst()->GetContentPath();
	strFilepath += _strRelativePath;

	// 파일 입출력
	FILE* pFile = nullptr;
	errno_t iErrNum = _wfopen_s(&pFile, strFilepath.c_str(), L"wb");

	if (nullptr == pFile)
	{
		wchar_t szStr[256] = {};
		wsprintf(szStr, L"Animation Save 실패, Error Number : %d", iErrNum);
		MessageBox(nullptr, szStr, L"파일 저장 실패", MB_OK);
		return;
	}

	// Animation 이름 저장
	fwprintf_s(pFile, L"\n");

	fwprintf_s(pFile, L"[ANIMATION_NAME]\n");
	fwprintf_s(pFile, GetName().c_str());
	fwprintf_s(pFile, L"\n\n");

	// 아틀라스 텍스쳐 키값 저장	
	fwprintf_s(pFile, L"[ATLAS_KEY]\n");
	fwprintf_s(pFile, m_AtlasTex->GetKey().c_str());
	fwprintf_s(pFile, L"\n\n");

	fwprintf_s(pFile, L"[ATLAS_PATH]\n");
	fwprintf_s(pFile, m_AtlasTex->GetRelativePath().c_str());
	fwprintf_s(pFile, L"\n\n");

	fwprintf_s(pFile, L"[ATLAS_SIZE]\n");
	fwprintf_s(pFile, L"%.1f %.1f\n", m_AtlasTex->Width(), m_AtlasTex->Height());
	fwprintf_s(pFile, L"\n\n");

	fwprintf_s(pFile, L"[BACK_SIZE]\n");
	fwprintf_s(pFile, L"%f %f\n", m_vBackSize.x, m_vBackSize.y);
	fwprintf_s(pFile, L"\n\n");


	// 프레임 정보 저장
	wchar_t szNum[50] = {};

	fwprintf_s(pFile, L"[FRAME_COUNT]\n");

	size_t iFrmCount = m_vecFrm.size();
	_itow_s((int)iFrmCount, szNum, 50, 10);

	fwprintf_s(pFile, szNum);
	fwprintf_s(pFile, L"\n\n");

	for (size_t i = 0; i < iFrmCount; ++i)
	{
		fwprintf_s(pFile, L"[%zd_FRAME]\n", i);

		// LEFT_TOP
		fwprintf_s(pFile, L"[LEFT_TOP]\n");
		fwprintf_s(pFile, L"%.1f %.1f\n", m_vecFrm[i].LeftTopUV.x * m_AtlasTex->Width(), m_vecFrm[i].LeftTopUV.y * m_AtlasTex->Height());

		// SIZE
		fwprintf_s(pFile, L"[SIZE]\n");
		fwprintf_s(pFile, L"%.1f %.1f\n", m_vecFrm[i].SliceUV.x * m_AtlasTex->Width(), m_vecFrm[i].SliceUV.y * m_AtlasTex->Height());

		// OFFSET
		fwprintf_s(pFile, L"[OFFSET]\n");
		fwprintf_s(pFile, L"%.1f %.1f\n", m_vecFrm[i].Offset.x, m_vecFrm[i].Offset.y);

		// DURATION
		fwprintf_s(pFile, L"[DURATION]\n");
		fwprintf_s(pFile, L"%.2f\n", m_vecFrm[i].fDuration);

		fwprintf_s(pFile, L"\n");
	}

	fclose(pFile);
}

void CAnim2D::Load(const wstring& _strRelativePath)
{
	m_vecFrm.clear();
	wstring strFilepath = CPathMgr::GetInst()->GetContentPath();
	strFilepath += _strRelativePath;

	m_RelativePath = _strRelativePath;

	// 파일 입출력
	FILE* pFile = nullptr;
	errno_t iErrNum = _wfopen_s(&pFile, strFilepath.c_str(), L"rb");

	if (nullptr == pFile)
	{
		wchar_t szStr[256] = {};
		wsprintf(szStr, L"Animation Load 실패, Error Number : %d", iErrNum);
		MessageBox(nullptr, szStr, L"파일 부르기 실패", MB_OK);
		return;
	}

	size_t iFrameCount = 0;
	Vec2 AtlasSize = Vec2(0.f, 0.f);
	wstring strAtlasKey;
	wstring strAltasRelativePath;

	while (true)
	{
		wchar_t szBuffer[256] = {};
		fwscanf_s(pFile, L"%s", szBuffer, 256);

		if (!wcscmp(szBuffer, L"[ANIMATION_NAME]"))
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
		else if (!wcscmp(szBuffer, L"[BACK_SIZE]"))
		{

			fwscanf_s(pFile, L"%f %f", &m_vBackSize.x, &m_vBackSize.y);

		}

		else if (!wcscmp(szBuffer, L"[FRAME_COUNT]"))
		{
			fwscanf_s(pFile, L"%zd", &iFrameCount);

			for (size_t i = 0; i < iFrameCount; ++i)
			{
				tAnim2DFrm frm = {};

				while (true)
				{
					wchar_t szBuffer[256] = {};
					fwscanf_s(pFile, L"%s", szBuffer, 256);

					if (!wcscmp(szBuffer, L"[LEFT_TOP]"))
					{
						fwscanf_s(pFile, L"%f %f", &frm.LeftTopUV.x, &frm.LeftTopUV.y);
						frm.LeftTopUV /= AtlasSize;
					}

					else if (!wcscmp(szBuffer, L"[SIZE]"))
					{
						fwscanf_s(pFile, L"%f %f", &frm.SliceUV.x, &frm.SliceUV.y);
						frm.SliceUV /= AtlasSize;
					}

					else if (!wcscmp(szBuffer, L"[OFFSET]"))
					{
						fwscanf_s(pFile, L"%f %f", &frm.Offset.x, &frm.Offset.y);
					}

					else if (!wcscmp(szBuffer, L"[DURATION]"))
					{
						fwscanf_s(pFile, L"%f", &frm.fDuration);
						break;
					}
					
				}

				m_vecFrm.push_back(frm);
			}

			break;
		}
	}
	
	m_AtlasTex = CResMgr::GetInst()->Load<CTexture>(strAtlasKey, strAltasRelativePath);

	fclose(pFile);
}
