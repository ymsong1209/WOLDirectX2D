#pragma once
#include <Engine/CScript.h>

class CBossWaveScript :
    public CScript
{
private:
    Ptr<CSound>        m_pBossBGM;
    bool               m_bWaveActive;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Other) override;
   
    void Activate();
    void Deactivate();

private:
    CLONE(CBossWaveScript);
public:
    CBossWaveScript();
    ~CBossWaveScript();
};

