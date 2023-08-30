#pragma once
#include <Engine/CScript.h>

class CMonsterSpawnPointScript :
    public CScript
{
private:
    int                         m_iWaveNum;
    int                         m_iMonsterCount;
    vector<CGameObject*>        m_vecMonster;
    vector<CGameObject*>        m_vecHorWall;
    vector<CGameObject*>        m_vecVerWall;
    bool                        m_bSpawned;
    
public:
    virtual void tick() override;
    virtual void begin() override;

    virtual void BeginOverlap(CCollider2D* _Other) override;
    virtual void OnOverlap(CCollider2D* _Other) override;
    virtual void EndOverlap(CCollider2D* _Other) override;

    

    CLONE(CMonsterSpawnPointScript);

    const int& GetWaveNum() { return m_iWaveNum; }
    void SetWaveNum(int _num) { m_iWaveNum = _num; }
    void AddMonster(CGameObject* Monster); //Monster의 begin에서 집어넣음
    void AddVerWall(CGameObject* wall) { m_vecVerWall.push_back(wall); }
    void AddHorWall(CGameObject* wall) { m_vecHorWall.push_back(wall); }
    void RemoveMonsterCount(); //Monster가 죽을때 실행함
    
    void SpawnMonster();

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;
public:
    CMonsterSpawnPointScript();
    ~CMonsterSpawnPointScript();
};


