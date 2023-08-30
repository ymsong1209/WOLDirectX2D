#pragma once
#include <Engine/CScript.h>
class CPlayerSkillSlotScript :
    public CScript
{
private:
    bool            m_bUIActive;
    Ptr<CTexture>   m_pChangeSkill;
public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

    void Activate();
    void Deactivate();

    const bool& GetUIActive() { return m_bUIActive; }
public:

    CLONE(CPlayerSkillSlotScript);
public:
    CPlayerSkillSlotScript();
    ~CPlayerSkillSlotScript();

};

