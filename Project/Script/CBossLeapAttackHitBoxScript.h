#pragma once
#include <Engine/CScript.h>

class CBossLeapAttackHitBoxScript :
    public CScript
{
private:
    float   m_fTime;
public:

    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Other) override;

private:
    CLONE(CBossLeapAttackHitBoxScript);
public:
    CBossLeapAttackHitBoxScript();
    ~CBossLeapAttackHitBoxScript();
};