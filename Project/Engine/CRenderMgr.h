#pragma once
#include "CSingleton.h"

class CCamera;
class CLight2D;
class CStructuredBuffer;


class CRenderMgr :
    public CSingleton<CRenderMgr>
{
    SINGLE(CRenderMgr);
private:
    vector<CCamera*>            m_vecCam; //카메라가 여러대일수도 있다.
    CCamera*                    m_pEditorCam;

    vector<tDebugShapeInfo>     m_vecShapeInfo;

    vector<tLightInfo>          m_vecLight2D;
    CStructuredBuffer*          m_Light2DBuffer;

    bool                        m_bEditorCameraUse;

    Ptr<CTexture>               m_RTCopyTex;

    void (CRenderMgr::* RENDER_FUNC)(void);

public:
    void init();
    void render();



public:
    int RegisterCamera(CCamera* _Cam, int _idx);
    void RegisterEditorCamera(CCamera* _Cam) { m_pEditorCam = _Cam; }
    void SetRenderFunc(bool _IsPlay);
    void RegisterLight2D(const tLightInfo& _Light2D) { m_vecLight2D.push_back(_Light2D); }
    void ClearCamera() { m_vecCam.clear(); }

    void AddDebugShapeInfo(const tDebugShapeInfo& _info) { m_vecShapeInfo.push_back(_info); }
    vector<tDebugShapeInfo>& GetDebugShapeInfo() { return m_vecShapeInfo; }

    bool GetEditorCameraUse() { return m_bEditorCameraUse; }
    CCamera* GetEditorCam() { return m_pEditorCam; }

    CCamera* GetMainCam()
    {
        if (m_vecCam.empty())
            return nullptr;

        return m_vecCam[0];
    }

    void CopyRenderTarget();

   
private:
    void UpdateData();
    void render_play();
    void render_editor();
    void Clear();
};
