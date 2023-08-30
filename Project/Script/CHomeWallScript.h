#pragma once
#include <Engine/CScript.h>

class CHomeWallScript :
    public CScript
{
private:

public:
    virtual void tick() override;
    virtual void begin() override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;

    CLONE(CHomeWallScript);
public:
    CHomeWallScript();
    ~CHomeWallScript();
};