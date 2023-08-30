#pragma once
#include <Engine/CScript.h>

class CBossLeapAttackScript :
    public CScript
{
private:
    CGameObject* m_pOwner;
public:

    virtual void begin() override;
    virtual void tick() override;

   
   
private:
    CLONE(CBossLeapAttackScript);
public:
    CBossLeapAttackScript();
    ~CBossLeapAttackScript();
};