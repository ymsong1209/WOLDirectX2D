#pragma once
#include <Engine/CScript.h>
class CESkillSlotScript :
    public CScript
{
private:
    bool            m_bUIActive;

    Ptr<CTexture>   m_pNormalAttack;
    Ptr<CTexture>   m_pFireDragon;
    Ptr<CTexture>   m_pIceCrystal;
    Ptr<CTexture>   m_pMeteor;
    Ptr<CTexture>   m_pWaterBall;
    Ptr<CTexture>   m_pChaosBall;
    Ptr<CTexture>   m_pNone;

    Ptr<CTexture>   m_pCurSkillTex;
public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

    void Activate();
    void Deactivate();

public:

    CLONE(CESkillSlotScript);
public:
    CESkillSlotScript();
    ~CESkillSlotScript();

};