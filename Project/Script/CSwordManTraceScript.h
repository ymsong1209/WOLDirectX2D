#pragma once
#include <Engine/CScript.h>
class CSwordManTraceScript :
    public CScript
{
private:
    int          m_iMovingdirection;
    float        m_fTime;
    float        m_fForce;
public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CSwordManTraceScript);
public:
    CSwordManTraceScript();
    ~CSwordManTraceScript();
};
