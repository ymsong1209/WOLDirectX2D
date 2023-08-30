#pragma once
#include <Engine/CScript.h>
class CGhoulSpawnScript :
    public CScript
{
private:

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CGhoulSpawnScript);
public:
    CGhoulSpawnScript();
    ~CGhoulSpawnScript();
};