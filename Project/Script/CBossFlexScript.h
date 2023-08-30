#pragma once
#include <Engine/CScript.h>

class CBossFlexScript :
    public CScript
{
    float   m_fFlexTime;
    bool    m_bAnimationPlayed;
    
public:

    virtual void begin() override;
    virtual void tick() override;

    virtual void Enter() override;
    virtual void Exit() override;

    void AddFlexTime(float _time) { m_fFlexTime += _time; } //HitState에서 축적된 time
    void SetFlexTime(float _time) { m_fFlexTime = _time; }
private:
    CLONE(CBossFlexScript);
public:
    CBossFlexScript();
    ~CBossFlexScript();
};