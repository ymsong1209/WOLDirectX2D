#pragma once
#include <Engine/CScript.h>

class CMageBallDeadScript :
    public CScript
{

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CMageBallDeadScript);
public:
    CMageBallDeadScript();
    ~CMageBallDeadScript();
};
