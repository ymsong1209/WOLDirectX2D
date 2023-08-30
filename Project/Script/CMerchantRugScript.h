#pragma once
#include <Engine/CScript.h>

class CMerchantRugScript :
    public CScript
{
private:
  
public:

    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;

private:
    CLONE(CMerchantRugScript);
public:
    CMerchantRugScript();
    ~CMerchantRugScript();
};
