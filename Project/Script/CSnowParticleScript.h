#pragma once
#include <Engine/CScript.h>
class CSnowParticleScript :
    public CScript
{
private:
    tParticleModule             m_ModuleData;

public:
    virtual void begin() override;
    virtual void tick() override;

    CLONE(CSnowParticleScript);
public:
    CSnowParticleScript();
    ~CSnowParticleScript();
};

