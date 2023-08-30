#pragma once
#include <Engine/CScript.h>
class CMeteorFloorCrackScript :
    public CScript
{
private:
    float           m_fTime;

public:

    virtual void begin() override;
    virtual void tick() override;

public:
    CLONE(CMeteorFloorCrackScript);
public:
    CMeteorFloorCrackScript();
    ~CMeteorFloorCrackScript();
};

