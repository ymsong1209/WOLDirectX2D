#pragma once
#include <Engine/CScript.h>

class CMageScript :
    public CScript
{
private:
    int         m_iWaveNum;
    int         m_iHp;
    int         m_iDir;
    Vec3        m_vPlayerPos;
    bool        m_bIsDeadState;
    bool        m_bFall;
    bool        m_bIsHit;
public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Other) override;
    virtual void OnOverlap(CCollider2D* _Other) override;
    virtual void EndOverlap(CCollider2D* _Other) override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;


public:
    const int& GetMageDir() { return m_iDir; }
    void SetMageDir(int _dir) { m_iDir = _dir; }

    Vec3 GetPlayerPos() { return m_vPlayerPos; }
    void SetPlayerPos(Vec3 _Pos) { m_vPlayerPos = _Pos; }

    const bool& IsHit() { return m_bIsHit; }
    void SetHit(bool _hit) { m_bIsHit = _hit; }

    const bool& IsFall() { return m_bFall; }
    void SetFall(bool _fall) { m_bFall = _fall; }

    const int& GetMageHP() { return m_iHp; }
    void SetMageHp(int _hp) { m_iHp = _hp; }

    const bool& GetMageDeadState() { return m_bIsDeadState; }
    void SetMageDeadState(bool _state) { m_bIsDeadState = _state; }

    const int& GetMageWaveNum() { return m_iWaveNum; }
    void SetMageWaveNum(int num) { m_iWaveNum = num; }

    CLONE(CMageScript);
public:
    CMageScript();
    CMageScript(const CMageScript& _other);
    ~CMageScript();
};
