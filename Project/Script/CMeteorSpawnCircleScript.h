#pragma once
#include <Engine/CScript.h>
class CGameObject;
class CMeteorSpawnCircleScript :
    public CScript
{
private:
    CGameObject* m_pMeteor;
public:

    virtual void begin() override;
    virtual void tick() override;

    void SetMeteor(CGameObject* _object) { m_pMeteor = _object; }
public:
    CLONE(CMeteorSpawnCircleScript);
public:
    CMeteorSpawnCircleScript();
    ~CMeteorSpawnCircleScript();
};
