#pragma once
#include <Engine/CScript.h>

class CSwordManIdleScript :
    public CScript
{
private:
    float       m_fTime;
public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CSwordManIdleScript);
public:
    CSwordManIdleScript();
    ~CSwordManIdleScript();
};
