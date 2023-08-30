#pragma once
#include "CComponent.h"


class CScript;

class CFSM :
    public CComponent
{
   
public:
    CScript* m_pCurScript;
public:

public:
    virtual void finaltick() override;

    CScript* FindScript(UINT _ScriptType);
    
    CScript* GetScript() { return m_pCurScript; }
    

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

    CLONE(CFSM);

private:
    void ChangeState(UINT _ScriptType, bool _isRepeat);
    
public:
    CFSM();
    CFSM(const CFSM& _other);
    ~CFSM();

    //friend class CScript;
    friend class CEventMgr;
};