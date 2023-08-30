#pragma once
#include <Engine/CScript.h>

class CBossScript :
    public CScript
{
private:
    int         m_iHp;
    int         m_iMaxHP;
    bool        m_bIsDeadState;
    int         m_iDir;
    Vec3        m_vPlayerPos;

    float       m_fHitTime;//HitTime
    bool        m_bCanChangeToHit;
public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Other) override;
    virtual void OnOverlap(CCollider2D* _Other) override;
    virtual void EndOverlap(CCollider2D* _Other) override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;


public:
    const int& GetBossDir() { return m_iDir; }
    void SetBossDir(int _dir) { m_iDir = _dir; }

    const int& GetBossHp() { return m_iHp; }
    void SetBossHp(int _hp) { m_iHp = _hp; }

    const int& GetBossMAXHp() { return m_iMaxHP; }
    void SetBossMAXHp(int _hp) { m_iMaxHP = _hp; }

    void SetCanChangeToHit(bool _Bool) { m_bCanChangeToHit = _Bool; }
    const bool& GetCanChangeToHit() { return m_bCanChangeToHit; }

    const bool& GetBossDeadState() { return m_bIsDeadState; }
    void SetBossDeadState(bool _state) { m_bIsDeadState = _state; }

    CLONE(CBossScript);
public:
    CBossScript();
    ~CBossScript();
};
