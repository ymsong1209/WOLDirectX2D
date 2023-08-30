#pragma once
#include <Engine/CScript.h>
#include "CPlayerScript.h"

class CSelectedSkillSlotScript :
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

    PLAYER_SKILL        m_pSelectedSkill;
    PLAYER_ATTACKBUTTON m_pSelectedAttackBtn;
    float               m_fSelectedSkillCoolTime;
    int                 m_iSelectedArrowNum;

    PLAYER_SKILL        m_pDestSkill;
    PLAYER_ATTACKBUTTON m_pDestAttackBtn;
    float               m_fDestSkillCoolTime;

    void SetSelectSkill(PLAYER_SKILL _skill, float _time) { m_pSelectedSkill = _skill; m_fSelectedSkillCoolTime = _time; }

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

    void Activate();
    void Deactivate();

public:

    CLONE(CSelectedSkillSlotScript);
public:
    CSelectedSkillSlotScript();
    ~CSelectedSkillSlotScript();

};