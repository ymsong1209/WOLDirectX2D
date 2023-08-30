#pragma once
#include <Engine/CScript.h>

class CBossIdleScript :
    public CScript
{
public:

    virtual void begin() override;
    virtual void tick() override;

    virtual void Enter() override;
    virtual void Exit() override;

private:
    CLONE(CBossIdleScript);
public:
    CBossIdleScript();
    ~CBossIdleScript();
};