#pragma once
#include <Engine/CScript.h>

class CSwordManScript :
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
    const int& GetSwordManDir() { return m_iDir; }
    void SetSwordManDir(int _dir) { m_iDir = _dir; }

    Vec3 GetPlayerPos() { return m_vPlayerPos;}
    void SetPlayerPos(Vec3 _Pos) { m_vPlayerPos = _Pos; }

    const bool& IsHit() { return m_bIsHit;}
    void SetHit(bool _hit) { m_bIsHit = _hit; }

    const bool& IsFall() { return m_bFall; }
    void SetFall(bool _fall) { m_bFall = _fall; }

    const int& GetSwordManHP() { return m_iHp; }
    void SetSwordManHp(int _hp) { m_iHp = _hp; }

    const bool& GetSwordManDeadState() { return m_bIsDeadState; }
    void SetSwordManDeadState(bool _state) { m_bIsDeadState = _state; }

    const int& GetSwordManWaveNum() { return m_iWaveNum; }
    void SetSwordManWaveNum(int num) { m_iWaveNum = num; }

    CLONE(CSwordManScript);
public:
    CSwordManScript();
    ~CSwordManScript();
};


