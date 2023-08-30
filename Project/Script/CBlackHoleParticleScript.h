#pragma once
#include <Engine/CScript.h>

class CBlackHoleParticleScript :
    public CScript
{
private:
    Vec2    m_vPos;
    float   m_fRadius;
    Vec2    m_vMousePos;
    float   m_fAngle;
    float   m_fForce;

    CGameObject* m_pBlackOwner;
public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Other) override;
    virtual void OnOverlap(CCollider2D* _Other) override;
    virtual void EndOverlap(CCollider2D* _Other) override;


    void init();
    void SetBlackOwner(CGameObject* _owner) { m_pBlackOwner = _owner; }
public:
    CLONE(CBlackHoleParticleScript);
public:
    CBlackHoleParticleScript();
    ~CBlackHoleParticleScript();
};
