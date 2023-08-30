#pragma once
#include <Engine/CScript.h>
class CPlayerHurtUIScript :
    public CScript
{
    
    float   m_fTime;
    float   m_fAlphaCoefficient;
    float   m_fAlpha;

public:

    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

public:

    CLONE(CPlayerHurtUIScript);
public:
    CPlayerHurtUIScript();
    ~CPlayerHurtUIScript();

};