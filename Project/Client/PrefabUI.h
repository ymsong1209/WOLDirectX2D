#pragma once
#include "ResUI.h"

class CRay;
class CGameObject;

class PrefabUI :
    public ResUI
{
private:
    Vec4            m_vMousePos;
    Vec4            m_vConvertedMousePos;
    CRay*           m_CRay;
    int             m_iSpawnLayerIdx;

    bool            m_bClickToSpawn;
    bool            m_bIsTransformAbsolute;
    Vec3            m_vClickedPosition;
    CGameObject*    m_pClonedObject;
   
public:
    virtual void tick() override;
    virtual int render_update() override;

    void SelectLayer();
    void SpawnPrefab();
    void SavePrefab();

public:
    PrefabUI();
    ~PrefabUI();
};


