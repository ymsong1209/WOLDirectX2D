#include "pch.h"
#include "CRenderMgr.h"

#include "CDevice.h"
#include "CConstBuffer.h"
#include "CStructuredBuffer.h"

#include "CCamera.h"
#include "CLight2D.h"
#include "CResMgr.h"

CRenderMgr::CRenderMgr()
    : m_Light2DBuffer(nullptr)
    , m_bEditorCameraUse(true)
    , RENDER_FUNC(nullptr)
    , m_pEditorCam(nullptr)
{
    Vec2 vResolution = CDevice::GetInst()->GetRenderResolution();
    m_RTCopyTex = CResMgr::GetInst()->CreateTexture(L"RTCopyTex"
        , (UINT)vResolution.x, (UINT)vResolution.y
        , DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE
        , D3D11_USAGE_DEFAULT);

  
}

CRenderMgr::~CRenderMgr()
{
    if (nullptr != m_Light2DBuffer)
        delete m_Light2DBuffer;
}


void CRenderMgr::init()
{
    // Light2DBuffer ����ȭ ���� ����
    // �ʱ⿡�� 10���� ����������, ������ �� �߰��Ǹ� �ڵ����� ũ�⸦ �÷���
    m_Light2DBuffer = new CStructuredBuffer;
    m_Light2DBuffer->Create(sizeof(tLightInfo), 10, SB_TYPE::READ_ONLY, true);
}

void CRenderMgr::render()
{
    // ������ ����, ClearTarget
    float arrColor[4] = { 0.f, 0.f, 0.f, 1.f };
    CDevice::GetInst()->ClearTarget(arrColor);

    // ��� Ÿ�� ����    
    CDevice::GetInst()->OMSet();

    //���� ������ ����
    UpdateData();


    // ���� �Լ� ȣ��
    (this->*RENDER_FUNC)();


    Clear();
}

void CRenderMgr::render_play()
{
   

    // ī�޶� ���� ������
    for (size_t i = 0; i < m_vecCam.size(); ++i)
    {
        if (nullptr == m_vecCam[i])
            continue;

        m_vecCam[i]->SortObject();//ī�޶� �ȿ� ������ ��ü���� �з�
        m_vecCam[i]->render();
    }
    //DebugShape�� ����� ���̰� �ϰ� ������ render_editorŰ��
    //Release�������� PostProcess�� ����� �۵��ؾ��ϱ� ������ ������Ѵ�.

    render_editor();
    
}

void CRenderMgr::render_editor()
{
    m_pEditorCam->SortObject();
    m_pEditorCam->render();
}


int CRenderMgr::RegisterCamera(CCamera* _Cam, int _idx)
{
    if (m_vecCam.size() <= _idx)
    {
        m_vecCam.resize(_idx + 1);
    }

    m_vecCam[_idx] = _Cam;
    return _idx;
}

void CRenderMgr::SetRenderFunc(bool _IsPlay)
{
    if (_IsPlay) {
        RENDER_FUNC = &CRenderMgr::render_play;
        m_bEditorCameraUse = false;
    }
    else {
        RENDER_FUNC = &CRenderMgr::render_editor;
        m_bEditorCameraUse = true;
    }
       
}

void CRenderMgr::CopyRenderTarget()
{
    Ptr<CTexture> pRTTex = CResMgr::GetInst()->FindRes<CTexture>(L"RenderTargetTex");
    CONTEXT->CopyResource(m_RTCopyTex->GetTex2D().Get(), pRTTex->GetTex2D().Get());
}


void CRenderMgr::UpdateData()
{
    // GlobalData �� ���� �������� ����
    GlobalData.Light2DCount = m_vecLight2D.size();

    // ����ȭ������ ũ�Ⱑ ���ڶ�� �� ũ�� ���� �����.
    if (m_Light2DBuffer->GetElementCount() < m_vecLight2D.size())
    {
        m_Light2DBuffer->Create(sizeof(tLightInfo), m_vecLight2D.size(), SB_TYPE::READ_ONLY, true);
    }

    // ����ȭ���۷� ���� �����͸� �ű��.
    m_Light2DBuffer->SetData(m_vecLight2D.data(), sizeof(tLightInfo) * m_vecLight2D.size());
    m_Light2DBuffer->UpdateData(12, PIPELINE_STAGE::PS_PIXEL);


    // ���� ��� ������ ���ε�
    CConstBuffer* pGlobalBuffer = CDevice::GetInst()->GetConstBuffer(CB_TYPE::GLOBAL);
    pGlobalBuffer->SetData(&GlobalData, sizeof(tGlobal));
    pGlobalBuffer->UpdateData();
    pGlobalBuffer->UpdateData_CS();
}

void CRenderMgr::Clear()
{
    m_vecLight2D.clear();
}