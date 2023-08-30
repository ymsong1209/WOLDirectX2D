#pragma once
#include <Engine/CScript.h>

class CBossHitScript :
    public CScript
{
private:
    float   m_fTime;
public:

    virtual void begin() override;
    virtual void tick() override;

    virtual void Enter() override;
    virtual void Exit() override;

private:
    CLONE(CBossHitScript);
public:
    CBossHitScript();
    ~CBossHitScript();
};