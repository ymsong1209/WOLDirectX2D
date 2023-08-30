#pragma once
#include <Engine/CScript.h>
class CBackHandAttackScript :
    public CScript
{
private:
    float       m_fInputangle;
    Vec3        m_vDirection;
    float        m_fForce;
public:

    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Other) override;
    virtual void OnOverlap(CCollider2D* _Other) override;
    virtual void EndOverlap(CCollider2D* _Other) override;
 
public:
    void SetInputAngle(float _angle) { m_fInputangle = _angle; }
    CLONE(CBackHandAttackScript);
public:
    CBackHandAttackScript();
    ~CBackHandAttackScript();

};

