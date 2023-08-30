#pragma once
#include <Engine/CScript.h>
class CDragonParticleScript :
    public CScript
{
private:
    float       m_fAngle;
    float       m_fWaitTime;
public:
    virtual void begin() override;
    virtual void tick() override;

    void SetWaittime(float _time) { m_fWaitTime = _time; }
public:
    CLONE(CDragonParticleScript);
public:
    CDragonParticleScript();
    ~CDragonParticleScript();
};

