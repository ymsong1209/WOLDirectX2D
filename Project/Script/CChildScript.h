#pragma once
#include <Engine/CScript.h>

class CTexture;
class CChildScript :
    public CScript
{

private:
    Ptr<CTexture> m_pTex;
public:
    virtual void tick() override;
    virtual void begin() override;
    virtual void BeginOverlap(CCollider2D* _Other) override;

    CLONE(CChildScript);
public:
    CChildScript();
    ~CChildScript();
};

