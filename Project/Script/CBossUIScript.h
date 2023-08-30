#pragma once
#include <Engine/CScript.h>

class CBossUIScript :
    public CScript
{
private:
    bool        m_bUIActive;

public:

    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

    void Activate();
    void Deactivate();

private:
    CLONE(CBossUIScript);
public:
    CBossUIScript();
    ~CBossUIScript();
};