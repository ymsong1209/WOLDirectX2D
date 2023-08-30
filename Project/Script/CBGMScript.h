#pragma once
#include <Engine/CScript.h>

class CBGMScript :
    public CScript
{
private:
    CSound* m_pEarth;
    CSound* m_pIce;

    bool    m_bIcePlay;
public:

    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Other) override;

private:
    CLONE(CBGMScript);
public:
    CBGMScript();
    ~CBGMScript();


};
