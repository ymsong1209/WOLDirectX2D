#pragma once
#include <Engine/CScript.h>

class CDragonArcArcanaScript :
    public CScript
{
public:

    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;

    virtual void BeginOverlap(CCollider2D* _Other) override;
    virtual void OnOverlap(CCollider2D* _Other) override;
    virtual void EndOverlap(CCollider2D* _Other) override;

private:
    CLONE(CDragonArcArcanaScript);
public:
    CDragonArcArcanaScript();
    ~CDragonArcArcanaScript();
};
