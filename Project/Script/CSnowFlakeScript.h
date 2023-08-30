#pragma once
#include <Engine/CScript.h>
class CSnowFlakeScript :
    public CScript
{
private:
    float       m_fStartAngle;
    float       m_fDegree;
    float       m_fRotation;

    Vec3        m_vDirection;
    float       m_fForce;


public:

    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Other) override;
    virtual void OnOverlap(CCollider2D* _Other) override;
    virtual void EndOverlap(CCollider2D* _Other) override;

    void SetStartangle(float _angle) { m_fStartAngle = _angle; }
public:
    CLONE(CSnowFlakeScript);
public:
    CSnowFlakeScript();
    ~CSnowFlakeScript();
};