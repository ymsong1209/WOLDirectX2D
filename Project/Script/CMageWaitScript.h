#pragma once
#include <Engine/CScript.h>


class CMageWaitScript :
    public CScript
{

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;

    CLONE(CMageWaitScript);
public:
    CMageWaitScript();
    ~CMageWaitScript();
};