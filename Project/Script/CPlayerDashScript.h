#pragma once
#include <Engine/CScript.h>
class CPlayerDashScript :
    public CScript
{
private:
    float       m_fDashTime;
public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CPlayerDashScript);
public:
    CPlayerDashScript();
    CPlayerDashScript(const CPlayerDashScript& _other);
    ~CPlayerDashScript();
};

