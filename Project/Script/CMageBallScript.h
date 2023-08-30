#pragma once
#include <Engine/CScript.h>

class CMageBallScript :
    public CScript
{
private:
    int         m_iWaveNum;
    bool        m_bIsDeadState;
public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    virtual void BeginOverlap(CCollider2D* _Other) override;
    virtual void OnOverlap(CCollider2D* _Other) override;
    virtual void EndOverlap(CCollider2D* _Other) override;

    void SetDeadState(bool _state) { m_bIsDeadState = _state; }
    const bool& IsDeadState() { return m_bIsDeadState; }

    void SetBallWaveNum(int _num) { m_iWaveNum = _num; }
    const int& GetBallWaveNum() { return m_iWaveNum; }

    CLONE(CMageBallScript);
public:
    CMageBallScript();
    ~CMageBallScript();
};