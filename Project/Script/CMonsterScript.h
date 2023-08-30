#pragma once
#include <Engine/CScript.h>
class CGameObject;
class CMonsterScript :
    public CScript
{
private:
    CGameObject* m_pPlayer;
    bool         m_bTrace;
    float        m_fTime;
public:
    virtual void tick() override;
    virtual void begin() override;
    virtual void BeginOverlap(CCollider2D* _Other) override;
    virtual void OnOverlap(CCollider2D* _Other) override;
    virtual void EndOverlap(CCollider2D* _Other) override;
    

    CLONE(CMonsterScript);
public:
    CMonsterScript();
    ~CMonsterScript();
};


