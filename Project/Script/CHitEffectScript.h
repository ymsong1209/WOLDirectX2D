#pragma once
#include <Engine/CScript.h>

class CHitEffectScript :
    public CScript
{
private:
  
public:
    virtual void tick() override;
    virtual void begin() override;


    CLONE(CHitEffectScript);
public:
    CHitEffectScript();
    ~CHitEffectScript();
};
