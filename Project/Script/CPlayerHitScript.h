#pragma once
#include <Engine/CScript.h>

class CPlayerHitScript :
    public CScript
{
private:
    Vec3        m_vDirection;
    float       m_fForce;
public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    void SetDirection(Vec3 _dir) { m_vDirection = _dir; }
    void SetForce(float _force) { m_fForce = _force; }

    CLONE(CPlayerHitScript);
public:
    CPlayerHitScript();
    ~CPlayerHitScript();
};