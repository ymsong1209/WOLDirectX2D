#pragma once
#include <Engine/CScript.h>

class CBossDrillScript :
    public CScript
{
private:
    bool        m_bRotate;
    Vec2        m_vDirection;
    CGameObject* m_pOwner;

public:

    virtual void begin() override;
    virtual void tick() override;

    void init();
    void SetOwner(CGameObject* owner) { m_pOwner = owner; }
    void SetDirection(Vec2 _dir) { m_vDirection = _dir; }
   

    virtual void BeginOverlap(CCollider2D* _Other) override;
private:
    CLONE(CBossDrillScript);
public:
    CBossDrillScript();
    ~CBossDrillScript();
};