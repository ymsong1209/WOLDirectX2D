#pragma once
#include <Engine/CScript.h>
#include "CPlayerScript.h"
class CSkillYellowArrowScript :
    public CScript
{
private:
    bool            m_bUIActive;
    Ptr<CTexture>   m_pArrowTex;

    int             m_iCurBtn;
public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;


    void SetArrowNum(int _num) { m_iCurBtn = _num; }
    void Activate();
    void Deactivate();

public:

    CLONE(CSkillYellowArrowScript);
public:
    CSkillYellowArrowScript();
    ~CSkillYellowArrowScript();

};