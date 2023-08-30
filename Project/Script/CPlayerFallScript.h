#pragma once
#include <Engine/CScript.h>

class CPlayerFallScript :
    public CScript
{
private:
    float       m_fFalltime;
public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CPlayerFallScript);
public:
    CPlayerFallScript();
    ~CPlayerFallScript();
};