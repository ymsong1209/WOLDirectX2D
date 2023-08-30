#pragma once
#include <Engine/CScript.h>

class CMeteorDamageZoneScript :
    public CScript
{
private:
    float          m_fForce;

public:

    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Other) override;
    virtual void OnOverlap(CCollider2D* _Other) override;
    virtual void EndOverlap(CCollider2D* _Other) override;

public:
    CLONE(CMeteorDamageZoneScript);
public:
    CMeteorDamageZoneScript();
    ~CMeteorDamageZoneScript();
};

