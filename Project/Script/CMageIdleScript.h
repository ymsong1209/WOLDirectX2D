#pragma once
#include <Engine/CScript.h>

class CMageIdleScript :
    public CScript
{
private:
    float        m_fAttackCoolTime;
public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CMageIdleScript);
public:
    CMageIdleScript();
    ~CMageIdleScript();
};
