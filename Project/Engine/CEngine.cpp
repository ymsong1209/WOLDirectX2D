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
	// ���� ������ �ڵ�
	m_hWnd = _hWnd;
	m_vResolution = Vec2((float)_iWidth, (float)_iHeight);

	// �ػ󵵿� �´� �۾����� ũ�� ����
	RECT rt = { 0, 0, (int)_iWidth, (int)_iHeight };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(m_hWnd, nullptr, 10, 10, rt.right - rt.left, rt.bottom - rt.top, 0);
	ShowWindow(m_hWnd, true);

	//Device �ʱ�ȭ
	if (FAILED(CDevice::GetInst()->init(m_hWnd, _iWidth, _iHeight)))
	{
		MessageBox(nullptr, L"Device �ʱ�ȭ ����", L"����", MB_OK);
		return E_FAIL;
	}

	//Manager �ʱ�ȭ
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

	// Event ó��, tick���� vectorũ�Ⱑ �����ɼ� �����Ƿ� render�ڿ� ȣ��
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


	//������ ����
	//1 = 255
	//float arrColor[4] = { 0.4f, 0.4f, 0.4f, 1.f };//ȸ��
	float arrColor[4] = { 0.f, 0.f, 0.f, 1.f };
	CDevice::GetInst()->ClearTarget(arrColor);


	CRenderMgr::GetInst()->render();

	//��ü�� �� �׸��� backbuffer�� frontbuffer�� ��ü������Ѵ�.
	// client�ʿ��� ��ü�� �׸� �� ������ (ex) debugshape)
	//�� �۾��� client�� main������ �ؾ��Ѵ�.
}
