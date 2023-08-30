#pragma once
#include <Engine/CScript.h>
class CGhoulAttackScript :
    public CScript
{
private:
    bool        m_bAttackFinished;
public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CGhoulAttackScript);
public:
    CGhoulAttackScript();
    ~CGhoulAttackScript();
};
