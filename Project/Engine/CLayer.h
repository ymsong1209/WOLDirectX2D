#pragma once
#include "CEntity.h"
class CGameObject;

class CLayer :
    public CEntity
{
private:
    vector<CGameObject*>    m_vecParentObj; // 레이어에 속해있는 부모오브젝트
    vector<CGameObject*>    m_vecObject;    // 계층에 상관없이 해당 레이어에 속해있는 모든 오브젝트
    int                     m_iLayerIdx;    // 레이어 번호 (0~31)
    
public:
    void begin();
    void tick();
    void finaltick();
  

public:
    int GetLayerIndex() { return m_iLayerIdx; }
    const vector<CGameObject*>& GetParentObject() { return m_vecParentObj; }
    const vector<CGameObject*>& GetObjects() { return m_vecObject; }


private:
    // Layer 에 부모오브젝트 입력
    // _bMove : 자식 오브젝트들이 부모 오브젝트를 따라서 이동 할 것인지 체크
    void AddGameObject(CGameObject* _Object, bool _bMove); // EventMgr를 통해 실행된다. SpawnGameObject사용할것
    void RegisterObject(CGameObject* _Object) { m_vecObject.push_back(_Object); } //GameObject의 Finaltick에서만 실행됨
    void RemoveFromParentList(CGameObject* _Obj); //GameObject의 ChangeToChildType를 통해 호출
    void AddParentList(CGameObject* _Obj); //GameObject의 AddParentList를 통해 호출

    CLONE(CLayer)
public:
    CLayer();
    ~CLayer();

    friend class CLevel;
    friend class CGameObject;
    friend class CEventMgr;
};

