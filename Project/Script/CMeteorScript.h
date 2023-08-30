#pragma once
#include <Engine/CScript.h>
class CGameObject;
class CMeteorScript :
    public CScript
{
private:
    Vec3        m_vLandPos;
    Vec3        m_vFallStartPos;
    float       m_fAngle;

    float       m_fFallTime;
    bool        m_bMeteorRingSpawn;

    CGameObject* m_pSpawnCircle;
public:

    virtual void begin() override;
    virtual void tick() override;

    void SetLandPos(Vec3 _pos) { m_vLandPos = _pos; }
    void SetSpawnCircle(CGameObject* _object) {
        m_pSpawnCircle = _object;
    }
public:
    CLONE(CMeteorScript);
public:
    CMeteorScript();
    ~CMeteorScript();
};

