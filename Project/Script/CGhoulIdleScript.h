#pragma once
#include <Engine/CScript.h>

class CGhoulIdleScript :
    public CScript
{
private:
    float       m_fTime;
public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CGhoulIdleScript);
public:
    CGhoulIdleScript();
    ~CGhoulIdleScript();
};
