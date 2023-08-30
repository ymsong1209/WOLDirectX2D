#pragma once
#include <Engine/CScript.h>
class CPlayerDustScript :
    public CScript
{
private:
public:

    virtual void begin() override;
    virtual void tick() override;

    void ActivateDust();
    void DeActivateDust();
public:
    CLONE(CPlayerDustScript);
public:
    CPlayerDustScript();
    ~CPlayerDustScript();
};
