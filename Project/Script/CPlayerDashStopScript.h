#pragma once
#include <Engine/CScript.h>
class CPlayerDashStopScript :
    public CScript
{
private:
    bool         m_bIsLeftorRight;
    bool         m_bTick;//낙하 판정을 위해 1frame skip
public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    virtual void BeginOverlap(CCollider2D* _Other) override;
    virtual void OnOverlap(CCollider2D* _Other) override;
    virtual void EndOverlap(CCollider2D* _Other) override;

    CLONE(CPlayerDashStopScript);
public:
    CPlayerDashStopScript();
    ~CPlayerDashStopScript();
};

