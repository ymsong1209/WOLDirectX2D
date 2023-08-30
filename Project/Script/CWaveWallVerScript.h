#pragma once
#include <Engine/CScript.h>

class CWaveWallVerScript :
    public CScript
{
private:
    int         m_iWaveNum;

public:

    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;

    void BlockGate();
    void RemoveGate();
    void SetWaveNum(int _num) { m_iWaveNum = _num; }

private:
    CLONE(CWaveWallVerScript);
public:
    CWaveWallVerScript();
    ~CWaveWallVerScript();
};
