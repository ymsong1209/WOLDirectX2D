#pragma once
#include <Engine/CScript.h>

class CMerchantScript :
    public CScript
{
private:

public:

    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;

    void Laugh();

private:
    CLONE(CMerchantScript);
public:
    CMerchantScript();
    ~CMerchantScript();
};
