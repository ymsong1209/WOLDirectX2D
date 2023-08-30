#pragma once
#include <Engine/CScript.h>
#include "CPlayerScript.h"
class CSkillArrowScript :
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


    const int& GetArrowNum() {return m_iCurBtn;}
    void Activate();
    void Deactivate();

public:

    CLONE(CSkillArrowScript);
public:
    CSkillArrowScript();
    ~CSkillArrowScript();

};

