#pragma once
#include <Engine/CScript.h>

class CPressEnterScript :
    public CScript
{
private:
    float              m_fTime;
    Ptr<CSound>        m_pMenuBGM;
    float              m_fAlphaCoefficient;
    float              m_fAlpha;
public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

private:
    CLONE(CPressEnterScript);
public:
    CPressEnterScript();
    ~CPressEnterScript();
};
