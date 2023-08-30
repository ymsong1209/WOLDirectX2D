#pragma once
#include <Engine/CScript.h>
class CMainLightScript :
    public CScript
{
private:
    float   m_fTime;
    float   m_fAccTime;
    bool    m_bDark;
    float   m_fDarkTime;
public:

    virtual void begin() override;
    virtual void tick() override;

    void SetToDark();
    void SetToDay();

private:
    CLONE(CMainLightScript);
public:
    CMainLightScript();
    ~CMainLightScript();
};

