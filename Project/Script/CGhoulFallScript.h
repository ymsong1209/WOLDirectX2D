#pragma once
#include <Engine/CScript.h>
class CGhoulFallScript :
    public CScript
{
private:
    float m_fFalltime;
public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CGhoulFallScript);
public:
    CGhoulFallScript();
    ~CGhoulFallScript();
};