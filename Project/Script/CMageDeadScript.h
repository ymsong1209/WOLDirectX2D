#pragma once
#include <Engine/CScript.h>


class CMageDeadScript :
    public CScript
{
private:

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CMageDeadScript);
public:
    CMageDeadScript();
    ~CMageDeadScript();
};
