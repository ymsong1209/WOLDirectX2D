#pragma once
#include "UI.h"

class CGameObject;
class ComponentUI;
class CRay;

class WaveUI :
    public UI
{
private:
    CGameObject*        m_pWave;
    Vec3                m_vMousePos;
    CRay*               m_CRay;
    int                 m_iMonsterType; //0 : SwordMan 1: Wizard 2: HorizontalWall 3: Vertical Wall ;
    int                 m_iWaveNum;

public:
    void SelectMonster();
    void SetWave();
    void AddMonster();
    void ResetWave() { m_pWave = nullptr; }
public:
    virtual void tick() override;
    virtual int render_update() override;

public:
    WaveUI();
    ~WaveUI();


};