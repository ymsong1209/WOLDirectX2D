#pragma once
#include <Engine/CScript.h>
class CExplosionParticleScript :
    public CScript
{
private:
    tParticleModule     m_ModuleData;
    bool                m_btime;
    float               m_ftime;

public:
    virtual void begin() override;
    virtual void tick() override;

    CLONE(CExplosionParticleScript);
public:
    CExplosionParticleScript();
    ~CExplosionParticleScript();
};

