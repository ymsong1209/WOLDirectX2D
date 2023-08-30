#pragma once
#include <Engine/CScript.h>


class CMainMenuScript :
    public CScript
{
public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

private:
    CLONE(CMainMenuScript);
public:
    CMainMenuScript();
    ~CMainMenuScript();
};
