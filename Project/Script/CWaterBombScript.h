#pragma once
#include <Engine/CScript.h>

class CWaterBombScript :
    public CScript
{
private:
    float       m_fShootSpeed;
    float       m_fForce;
    Vec3        m_vDirection;

    float       m_fScale;
    bool        m_bReady;
public:

    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Other) override;
    virtual void OnOverlap(CCollider2D* _Other) override;
    virtual void EndOverlap(CCollider2D* _Other) override;

    void ShootBomb(Vec3 _vDirection);
public:
    CLONE(CWaterBombScript);
public:
    CWaterBombScript();
    ~CWaterBombScript();
};
