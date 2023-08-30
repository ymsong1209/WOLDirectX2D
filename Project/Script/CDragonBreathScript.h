#pragma once
#include <Engine/CScript.h>

class CDragonBreathScript :
    public CScript
{
private:
    float       m_fInputAngle;
    float       m_fDegree;
    Vec3        m_vStartPos;
    Vec3        m_vDirection;
    float       m_fForce;
    Vec3        m_vPrevPos;

    float       m_fLife;
    float       m_fOffset;

    float       m_fWaitTime;

    bool        m_bSoundPlayed;
public:

    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Other) override;
    virtual void OnOverlap(CCollider2D* _Other) override;
    virtual void EndOverlap(CCollider2D* _Other) override;

    void SetInputAngle(float _angle) { m_fInputAngle = _angle; }
    void SetStartPos(Vec3 _pos) { m_vStartPos = _pos; }
    void SetOffset(float _life) { m_fLife = _life; }
    void SetWaitTime(float _time) { m_fWaitTime = _time; }
public:
    CLONE(CDragonBreathScript);
public:
    CDragonBreathScript();
    ~CDragonBreathScript();
};