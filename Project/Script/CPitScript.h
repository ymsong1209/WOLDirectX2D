#pragma once
#include <Engine/CScript.h>
class CPitScript :
    public CScript
{
    
public:

    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;

private:
    CLONE(CPitScript);
public:
    CPitScript();
    ~CPitScript();


};

