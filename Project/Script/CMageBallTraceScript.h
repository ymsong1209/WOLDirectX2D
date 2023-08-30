#pragma once
#include <Engine/CScript.h>

class CMageBallTraceScript :
    public CScript
{
private:
    float       m_fAttackCoolTime;
public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CMageBallTraceScript);
public:
    CMageBallTraceScript();
    ~CMageBallTraceScript();
};