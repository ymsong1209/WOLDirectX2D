#pragma once
#include <Engine/CScript.h>
class CRockFistScript :
    public CScript
{
private:
    Vec3        m_vBossPos;
    Vec3        m_vPlayerPos;
    bool        m_bChanged;
    float       m_fChargeTime;
    Vec3        m_vDirection;
public:

    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Other) override;

    void SetBossPos(Vec3 _pos) { m_vBossPos = _pos; }
    void SetPlayerPos(Vec3 _pos) { m_vPlayerPos = _pos; }
private:
    CLONE(CRockFistScript);
public:
    CRockFistScript();
    ~CRockFistScript();
};

