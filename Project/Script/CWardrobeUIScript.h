#pragma once
#include <Engine/CScript.h>

class CWardrobeUIScript :
    public CScript
{
private:
    bool         m_bOpen;
public:
    virtual void tick() override;
    virtual void begin() override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;

    void Activate();
    void Deactivate();

    const bool& GetOpen() { return m_bOpen; }
    CLONE(CWardrobeUIScript);
public:
    CWardrobeUIScript();
    ~CWardrobeUIScript();
};
