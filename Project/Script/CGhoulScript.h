#pragma once
#include <Engine/CScript.h>

class CGhoulScript :
    public CScript
{
private:
    int         m_iWaveNum;
    int         m_iHp;
    bool        m_bIsHit; //낙하판정용, hit상태에서는 pitwall 무시
    bool        m_bFall; //낙하중일때는 모든 collide무시
    bool        m_bIsDeadState;
    int         m_iDir;
    Vec3        m_vPlayerPos;
public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Other) override;
    virtual void OnOverlap(CCollider2D* _Other) override;
    virtual void EndOverlap(CCollider2D* _Other) override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;


public:
    const int& GetGhoulDir() { return m_iDir; }
    void SetGhoulDir(int _dir) { m_iDir = _dir; }

    Vec3 GetPlayerPos() { return m_vPlayerPos; }
    void SetPlayerPos(Vec3 _Pos) { m_vPlayerPos = _Pos; }

    const bool& IsHit() { return m_bIsHit; }
    void SetHit(bool _hit) { m_bIsHit = _hit; }

    const bool& IsFall() { return m_bFall; }
    void SetFall(bool _fall) { m_bFall = _fall; }

    const int& GetGhoulHP() { return m_iHp; }
    void SetGhoulHp(int _hp) { m_iHp = _hp; }

    const bool& GetGhoulDeadState() { return m_bIsDeadState; }
    void SetGhoulDeadState(bool _state) { m_bIsDeadState = _state; }

    const int& GetGhoulWaveNum() { return m_iWaveNum; }
    void SetGhoulWaveNum(int num) { m_iWaveNum = num; }

    CLONE(CGhoulScript);
public:
    CGhoulScript();
    ~CGhoulScript();
};
