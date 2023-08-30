#pragma once
#include <Engine/CScript.h>

class CTerraScript :
    public CScript
{
private:
    Vec3         m_vBossPos;
    Vec3         m_vPlayerPos;
    Vec2         m_vDirection;
    float        m_fTime;
    float        m_fAccTime;
    CSound* m_pTerraSound;
public:

    virtual void begin() override;
    virtual void tick() override;

    void SetBossPos(Vec3 _pos) { m_vBossPos = _pos; }
    void SetPlayerPos(Vec3 _pos) { m_vPlayerPos = _pos; }

private:
    CLONE(CTerraScript);
public:
    CTerraScript();
    ~CTerraScript();
};