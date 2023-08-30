#pragma once
#include <Engine/CScript.h>
class CRainParticleScript :
    public CScript
{
private:
    tParticleModule             m_ModuleData;

public:
    virtual void begin() override;
    virtual void tick() override;

    CLONE(CRainParticleScript);
public:
    CRainParticleScript();
    ~CRainParticleScript();
};

