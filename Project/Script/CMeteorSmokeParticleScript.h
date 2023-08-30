#pragma once
#include <Engine/CScript.h>

class CMeteorSmokeParticleScript :
    public CScript
{
private:
    float           m_fTime;

public:

    virtual void begin() override;
    virtual void tick() override;

public:
    CLONE(CMeteorSmokeParticleScript);
public:
    CMeteorSmokeParticleScript();
    ~CMeteorSmokeParticleScript();
};
