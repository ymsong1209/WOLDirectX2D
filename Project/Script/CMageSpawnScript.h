#pragma once
#include <Engine/CScript.h>

class CMageSpawnScript :
    public CScript
{

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CMageSpawnScript);
public:
    CMageSpawnScript();
    ~CMageSpawnScript();
};