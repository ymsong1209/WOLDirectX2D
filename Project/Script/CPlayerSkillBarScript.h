#pragma once
#include <Engine/CScript.h>


class CPlayerSkillBarScript :
    public CScript
{

public:

    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

public:

    CLONE(CPlayerSkillBarScript);
public:
    CPlayerSkillBarScript();
    ~CPlayerSkillBarScript();

};