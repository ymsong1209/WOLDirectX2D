#pragma once
#include <Engine/CScript.h>


class CBossFireflyScript :
    public CScript
{

public:

    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;

private:
    CLONE(CBossFireflyScript);
public:
    CBossFireflyScript();
    ~CBossFireflyScript();

};
