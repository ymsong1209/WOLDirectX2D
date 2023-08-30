#pragma once
#include <Engine/CScript.h>

class CPlayerColorScript :
    public CScript
{
private:
    Vec4     m_vColor;
public:

    virtual void begin() override;
    virtual void tick() override;

private:
 
    CLONE(CPlayerColorScript);
   
public:
    CPlayerColorScript();
    ~CPlayerColorScript();
};

