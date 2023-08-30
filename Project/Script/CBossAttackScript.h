#pragma once
#include <Engine/CScript.h>

enum class EType {
    DRILL,
    ROCKPUNCH,
    LEAPATTACK,
    TOWEROFTERRA,
    SHUTLIGHT,
    END,
};

class CBossAttackScript :
    public CScript
{
private:
    int             m_iAttackCount;
    UINT            m_iAttackType;
    int             m_iRockPunchCount;

    CGameObject*    m_pDrill;
    bool            m_bDrillSpawned;
    
    int             m_iLeapStage;

    Vec3            m_vBossPos;
    Vec3            m_vMiddlePos;
    Vec3            m_vPlayerPos;
    Vec2            m_vBossToMiddle;
    Vec2            m_vMiddleToPlayer;

    float           m_fTime;

    bool            m_bDrillSound;
public:

    virtual void begin() override;
    virtual void tick() override;

    virtual void Enter() override;
    virtual void Exit() override;

public:
    void DrillAttack();
    void RockPunchAttack();
    void TowerOfTerraAttack();
    void ShutLightAttack();
    void LeapWindUp();
    void Leap();
    void LeapFall();
    void LeapLand();
    void ResetAttackCount() { m_iAttackCount = 0; }
private:
    CLONE(CBossAttackScript);
public:
    CBossAttackScript();
    ~CBossAttackScript();
};