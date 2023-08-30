#pragma once
#include <Engine/CScript.h>
class CPotionScript :
    public CScript
{
private:
    bool        m_bFull;

public:

    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;

    virtual void BeginOverlap(CCollider2D* _Other) override;
    virtual void OnOverlap(CCollider2D* _Other) override;
    virtual void EndOverlap(CCollider2D* _Other) override;

    void Drink();

private:
    CLONE(CPotionScript);
public:
    CPotionScript();
    ~CPotionScript();
};