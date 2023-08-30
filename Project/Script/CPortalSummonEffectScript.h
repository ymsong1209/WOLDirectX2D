#pragma once
#include <Engine/CScript.h>

class CPortalSummonEffectScript :
    public CScript
{
private:
    int         m_iPortalNum;
    bool        m_bAnimActive;
public:
    virtual void tick() override;
    virtual void begin() override;


    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;

    void SetPortalNum(int num) { m_iPortalNum = num; }
    void Activate();

    CLONE(CPortalSummonEffectScript);
public:
    CPortalSummonEffectScript();
    ~CPortalSummonEffectScript();
};