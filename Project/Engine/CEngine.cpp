#include "pch.h"
#include "CEngine.h"
#include "CDevice.h"
#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CLevelMgr.h"
#include "CCollisionMgr.h"
#include "CRenderMgr.h"
#include "CEventMgr.h"
#include "CFontMgr.h"


CEngine::CEngine()
	: m_hWnd(nullptr)
{
}

CEngine::~CEngine()
{
	//Release();
}

int CEngine::init(HWND _hWnd, UINT _iWidth, UINT _iHeight)
{
	// 메인 윈도우 핸들
	m_hWnd = _hWnd;
	m_vResolution = Vec2((float)_iWidth, (float)_iHeight);

	// 해상도에 맞는 작업영역 크기 조정
	RECT rt = { 0, 0, (int)_iWidth, (int)_iHeight };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(m_hWnd, nullptr, 10, 10, rt.right - rt.left, rt.bottom - rt.top, 0);
	ShowWindow(m_hWnd, true);

	//Device 초기화
	if (FAILED(CDevice::GetInst()->init(m_hWnd, _iWidth, _iHeight)))
	{
		MessageBox(nullptr, L"Device 초기화 실패", L"에러", MB_OK);
		return E_FAIL;
	}

	//Manager 초기화
	CPathMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CResMgr::GetInst()->init();
	CRenderMgr::GetInst()->init();
	CFontMgr::GetInst()->init();
	CLevelMgr::GetInst()->init();


	return S_OK;
}

void CEngine::progress()
{
	tick();

	render();

	// Event 처리, tick내에 vector크기가 변동될수 있으므로 render뒤에 호출
	CEventMgr::GetInst()->tick();
}

void CEngine::tick()
{
	//manager tick
	CResMgr::GetInst()->tick();
	CTimeMgr::GetInst()->tick();
	CKeyMgr::GetInst()->tick();

	CSound::g_pFMOD->update();

	CLevelMgr::GetInst()->tick();
	CCollisionMgr::GetInst()->tick();
}

void CEngine::render()
{
	CTimeMgr::GetInst()->render();


	//렌더링 시작
	//1 = 255
	//float arrColor[4] = { 0.4f, 0.4f, 0.4f, 1.f };//회색
	float arrColor[4] = { 0.f, 0.f, 0.f, 1.f };
	CDevice::GetInst()->ClearTarget(arrColor);


	CRenderMgr::GetInst()->render();

	//물체를 다 그리면 backbuffer랑 frontbuffer를 교체해줘야한다.
	// client쪽에서 물체를 그릴 수 있으니 (ex) debugshape)
	//이 작업을 client의 main문에서 해야한다.
}
