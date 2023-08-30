#pragma once
#include <Engine/CScript.h>
#include "CPlayerScript.h"


class CPlayerAttackScript :
    public CScript
{
private:
    PLAYER_ATTACKBUTTON     m_ECurAttackBtn;
    PLAYER_SKILL            m_ECurSkill;
    int                     m_IAttackCount;

    bool                    m_bReturnToAttack;
    bool                    m_bIsAnimationFinished;
    bool                    m_bIsSkillActivated;
    bool                    m_bIsFinalAttack;

    bool                    m_bIsCharging;
    bool                    m_bIsUlt;
    CGameObject*            m_pWater;
public:

    virtual void begin() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    void ChangeToAttack();
    void ChangeDir();
    void NormalAttack();
    void SnowFlakeAttack();
    void DragonAttack();
    void MeteorAttack();
    void WaterBombAttack();
    void ChaosBallAttack();

    void AttackCharging();

    CLONE(CPlayerAttackScript);
public:
    CPlayerAttackScript();
    ~CPlayerAttackScript();
};

