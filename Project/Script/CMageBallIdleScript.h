#pragma once
#include <Engine/CScript.h>

class CMageBallIdleScript :
    public CScript
{
private:
    float        m_fAttackTime;
public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CMageBallIdleScript);
public:
    CMageBallIdleScript();
    ~CMageBallIdleScript();
};