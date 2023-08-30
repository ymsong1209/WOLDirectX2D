#pragma once
#include <Engine/CScript.h>
class CMeteorRingScript :
    public CScript
{
private:
   
public:

    virtual void begin() override;
    virtual void tick() override;

public:
    CLONE(CMeteorRingScript);
public:
    CMeteorRingScript();
    ~CMeteorRingScript();
};

