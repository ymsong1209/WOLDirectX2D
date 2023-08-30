#pragma once
#include <Engine/CScript.h>
class CBossDeadScript :
    public CScript
{
private:
    float   m_fTime;
    bool    m_bSummoned;
public:

    virtual void begin() override;
    virtual void tick() override;

    virtual void Enter() override;
    virtual void Exit() override;

private:
    CLONE(CBossDeadScript);
public:
    CBossDeadScript();
    ~CBossDeadScript();
};