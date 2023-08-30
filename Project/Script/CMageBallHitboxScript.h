#pragma once
#include <Engine/CScript.h>

class CMageBallHitboxScript :
    public CScript
{
private:

public:
    virtual void begin() override;
    virtual void tick() override;

    void AddCollider();

    virtual void BeginOverlap(CCollider2D* _Other) override;
    virtual void OnOverlap(CCollider2D* _Other) override;
    virtual void EndOverlap(CCollider2D* _Other) override;

    CLONE(CMageBallHitboxScript);
public:
    CMageBallHitboxScript();
    ~CMageBallHitboxScript();
};