#pragma once
#include <Engine/CScript.h>

class CDashEffectScript :
    public CScript
{
private:
public:

    virtual void begin() override;
    virtual void tick() override;

public:
    CLONE(CDashEffectScript);
public:
    CDashEffectScript();
    ~CDashEffectScript();
};
