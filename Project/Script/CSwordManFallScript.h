#pragma once
#include <Engine/CScript.h>
class CSwordManFallScript :
    public CScript
{
private:
    float m_fFalltime;
public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CSwordManFallScript);
public:
    CSwordManFallScript();
    ~CSwordManFallScript();
};

