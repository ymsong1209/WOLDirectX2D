#pragma once
#include <Engine/CScript.h>

class CPlayerMarkerScript :
    public CScript
{
private:
    float m_fAlpha;
public:

    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

public:
    CLONE(CPlayerMarkerScript);
public:
    CPlayerMarkerScript();
    ~CPlayerMarkerScript();
};
