#pragma once
#include <Engine/CScript.h>

class CTowerScript :
    public CScript
{
private:
 
public:

    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Other) override;

private:
    CLONE(CTowerScript);
public:
    CTowerScript();
    ~CTowerScript();
};