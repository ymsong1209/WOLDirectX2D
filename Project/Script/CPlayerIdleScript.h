#pragma once

#include <Engine/CScript.h>


class CPlayerIdleScript :
    public CScript
{
private:
    bool        m_bIdleToWalk;
    int         m_iWalkKeyCheck;
public:

    virtual void begin() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    void ChangeToAttack();
    void ChangeDir();
    CLONE(CPlayerIdleScript);
public:
    CPlayerIdleScript();
    ~CPlayerIdleScript();
};
