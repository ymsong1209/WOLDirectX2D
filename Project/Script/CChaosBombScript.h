#pragma once
#include <Engine/CScript.h>

class CChaosBombScript :
    public CScript
{
private:
    float       m_fShootSpeed;
    float       m_fForce;
    Vec3        m_vDirection;

    float       m_fScale;
    bool        m_bReady;

    bool        m_bCreateEffect;
public:

    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Other) override;
    virtual void OnOverlap(CCollider2D* _Other) override;
    virtual void EndOverlap(CCollider2D* _Other) override;

    void ShootBomb(Vec3 _vDirection);
public:
    CLONE(CChaosBombScript);
public:
    CChaosBombScript();
    ~CChaosBombScript();
};
