#pragma once


#include <Engine/CScript.h>
class CSwordManWaitScript :
    public CScript
{
private:

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;

    CLONE(CSwordManWaitScript);
public:
    CSwordManWaitScript();
    ~CSwordManWaitScript();
};
