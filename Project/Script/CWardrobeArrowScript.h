#pragma once
#include <Engine/CScript.h>

class CWardrobeArrowScript :
    public CScript
{
private:
    bool         m_bOpen;
    int          m_iCapeNum;
public:
    virtual void tick() override;
    virtual void begin() override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;

    void Activate();
    void Deactivate();

    const bool& GetOpen() { return m_bOpen; }
    CLONE(CWardrobeArrowScript);
public:
    CWardrobeArrowScript();
    ~CWardrobeArrowScript();
};
