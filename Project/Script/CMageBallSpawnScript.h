#pragma once
#include <Engine/CScript.h>

class CMageBallSpawnScript :
    public CScript
{
public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CMageBallSpawnScript);
public:
    CMageBallSpawnScript();
    ~CMageBallSpawnScript();
};