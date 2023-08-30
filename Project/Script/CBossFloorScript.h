#pragma once
#include <Engine/CScript.h>

class CTexture;

class CBossFloorScript :
    public CScript
{
private:
    Ptr<CTexture>  m_pTex;
public:

    virtual void begin() override;
    virtual void tick() override;

    void SelectTexture(DWORD_PTR _Key);
    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;

private:
    CLONE(CBossFloorScript);
public:
    CBossFloorScript();
    ~CBossFloorScript();

};
