#pragma once
#include <Engine/CScript.h>
class CBossEnterScript :
    public CScript
{
public:

    virtual void begin() override;
    virtual void tick() override;

    virtual void Enter() override;
    virtual void Exit() override;

private:
    CLONE(CBossEnterScript);
public:
    CBossEnterScript();
    ~CBossEnterScript();
};