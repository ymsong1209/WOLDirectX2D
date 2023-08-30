#pragma once
#include <Engine/CScript.h>

class CPortalParticleScript :
    public CScript
{
private:
    bool        m_bPortalActivated;
public:
    virtual void tick() override;
    virtual void begin() override;

    virtual void BeginOverlap(CCollider2D* _Other) override;
    virtual void OnOverlap(CCollider2D* _Other) override;
    virtual void EndOverlap(CCollider2D* _Other) override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;

    void Activate();

    CLONE(CPortalParticleScript);
public:
    CPortalParticleScript();
    ~CPortalParticleScript();
};