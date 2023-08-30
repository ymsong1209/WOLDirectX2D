#pragma once
#include <Engine/CScript.h>

class CMapPortalScript :
    public CScript
{
private:
    int         m_iPortalNum;
    bool        m_bPortalActivated;
public:
    virtual void tick() override;
    virtual void begin() override;

    virtual void BeginOverlap(CCollider2D* _Other) override;
    virtual void OnOverlap(CCollider2D* _Other) override;
    virtual void EndOverlap(CCollider2D* _Other) override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;

    void SetPortalNum(int num) { m_iPortalNum = num; }

    CLONE(CMapPortalScript);
public:
    CMapPortalScript();
    ~CMapPortalScript();
};
