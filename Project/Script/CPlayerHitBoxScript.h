#pragma once
#include <Engine/CScript.h>

class CGameObject;
class CPlayerHitBoxScript :
    public CScript
{
private:
    CGameObject* m_pPlayer;
public:

    virtual void begin() override;
    virtual void tick() override;
    virtual void BeginOverlap(CCollider2D* _Other) override;
    virtual void OnOverlap(CCollider2D* _Other) override;
    virtual void EndOverlap(CCollider2D* _Other) override;

public:
  

    CLONE(CPlayerHitBoxScript);
public:
    CPlayerHitBoxScript();
    CPlayerHitBoxScript(const CPlayerHitBoxScript& _other);
    ~CPlayerHitBoxScript();
};

