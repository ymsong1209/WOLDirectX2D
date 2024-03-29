#pragma once
#include "UI.h"
class CGameObject;
class ComponentUI;
class ResUI;
class ScriptUI;

#include <Engine\ptr.h>
#include <Engine\CRes.h>

class InspectorUI :
    public UI
{
private:
    CGameObject*        m_pTargetObj;
    ComponentUI*        m_arrComUI[(UINT)COMPONENT_TYPE::END];
    vector<ScriptUI*>   m_vecScriptUI;

    Ptr<CRes>           m_pTargetRes;
    ResUI*              m_arrResUI[(UINT)RES_TYPE::END];

public:
    virtual void init() override;
    virtual void tick() override;
    virtual int render_update() override;

public:
    void SetTargetObject(CGameObject* _Target, bool _isprefabObj = false);
    void SetTargetResource(Ptr<CRes> _Res);

    CGameObject* GetTargetObject() { return m_pTargetObj; }

private:
    void ClearTargetObject();
    void ClearTargetResource();
public:
    InspectorUI();
    ~InspectorUI();
};
