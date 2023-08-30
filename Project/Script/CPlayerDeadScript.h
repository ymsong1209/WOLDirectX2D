#pragma once
#include <Engine/CScript.h>

class CPlayerDeadScript :
    public CScript
{
private:
    float       m_fDissolveTime;
    float       m_fDissolveRange;
    Vec4        m_vDissolveColor;
    bool        m_bDissolveActive;


public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;
    void DissolveActive();



    CLONE(CPlayerDeadScript);
public:
    CPlayerDeadScript();
    CPlayerDeadScript(const CPlayerDeadScript& _other);
    ~CPlayerDeadScript();
};
