#pragma once
#include <Engine/CScript.h>

class CPlayerRScript :
    public CScript
{
private:
    Ptr<CTexture>   m_pNormalAttack;
    Ptr<CTexture>   m_pFireDragon;
    Ptr<CTexture>   m_pIceCrystal;
    Ptr<CTexture>   m_pMeteor;
    Ptr<CTexture>   m_pWaterBall;
    Ptr<CTexture>   m_pChaosBall;
    Ptr<CTexture>   m_pNone;

    Ptr<CTexture>   m_pCurSkill;

    float           m_fCurCoolTime;
    float           m_fCoolTime;

    float           m_fCoolPercentage;
public:

    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

public:

    CLONE(CPlayerRScript);
public:
    CPlayerRScript();
    ~CPlayerRScript();

};