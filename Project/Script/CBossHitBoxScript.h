#pragma once
#include <Engine/CScript.h>

class CBossHitBoxScript :
    public CScript
{
public:

    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Other) override;

private:
    CLONE(CBossHitBoxScript);
public:
    CBossHitBoxScript();
    ~CBossHitBoxScript();
};