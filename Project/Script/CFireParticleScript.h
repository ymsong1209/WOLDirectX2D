#pragma once
#include <Engine/CScript.h>
class CFireParticleScript :
    public CScript
{
private:
    tParticleModule             m_ModuleData;

public:
    virtual void begin() override;
    virtual void tick() override;

    CLONE(CFireParticleScript);
public:
    CFireParticleScript();
    ~CFireParticleScript();
};

