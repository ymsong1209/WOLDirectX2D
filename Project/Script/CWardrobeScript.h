#pragma once
#include <Engine/CScript.h>

class CWardrobeScript :
    public CScript
{
private:
    bool         m_bOpen;
public:
    virtual void tick() override;
    virtual void begin() override;

    virtual void BeginOverlap(CCollider2D* _Other) override;
    virtual void OnOverlap(CCollider2D* _Other) override;
    virtual void EndOverlap(CCollider2D* _Other) override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;

    CLONE(CWardrobeScript);
public:
    CWardrobeScript();
    ~CWardrobeScript();
};
