#pragma once
#include <Engine/CScript.h>

class CGameObject;
class CPlayerCameraScript :
    public CScript
{
private:
    CGameObject* m_pPlayer;
    Vec2         m_vOffset;
    float        m_fAccTime;
    float        m_fTime;
    bool         m_bCameraShake;
    float        m_fShakeDir;
    float        m_fRange;
    float        m_fShakeSpeed;

public:
    virtual void begin() override;
    virtual void tick() override;

    void CameraShake(float _time, float _Range, float m_fShakeSpeed);
private:
    CLONE(CPlayerCameraScript);
public:
    CPlayerCameraScript();
    ~CPlayerCameraScript();
};

