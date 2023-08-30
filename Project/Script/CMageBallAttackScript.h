#pragma once
#include <Engine/CScript.h>

class CMageBallAttackScript :
    public CScript
{
    float       m_fAttackTime;
    float       m_fAfterImageTime;
    float       m_fForce;

    
public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CMageBallAttackScript);
public:
    CMageBallAttackScript();
    ~CMageBallAttackScript();
};
