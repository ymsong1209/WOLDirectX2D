#pragma once
#include <Engine/CScript.h>

class CMageAttackScript :
    public CScript
{
private:
    float       m_fAttackCoolTime;
    CSound*     m_pSound;
public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CMageAttackScript);
public:
    CMageAttackScript();
    ~CMageAttackScript();
};
