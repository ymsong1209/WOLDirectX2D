#pragma once

#include <Engine/CScript.h>

class CPlayerWalkScript :
    public CScript
{
private:
    float       m_fWalkTime;
    float       m_fAfterImageCreateTime;
    bool        m_bDashSound;

    float       m_fWalkSoundTime;
    bool        m_bWalkSound;
public:

    virtual void begin() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    void ChangeToAttack();
    void ChangeDir();

    CLONE(CPlayerWalkScript);
public:
    CPlayerWalkScript();
    ~CPlayerWalkScript();
};
