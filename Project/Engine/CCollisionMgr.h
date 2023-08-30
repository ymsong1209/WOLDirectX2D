#pragma once
#include "CSingleton.h"

class CLayer;
class CCollider2D;


union CollisionID
{
	struct
	{
		UINT LeftID;
		UINT RightID;
	};

	UINT_PTR id;
};


class CCollisionMgr :
	public CSingleton<CCollisionMgr>
{
	SINGLE(CCollisionMgr);
private:
	UINT					m_matrix[MAX_LAYER];
	map<UINT_PTR, bool>		m_mapColID;

public:
	//어느 Layer가 서로 충돌하는지 정해주는 함수
	void LayerCheck(UINT _left, UINT _right);
	void LayerCheck(const wstring& _strLeftLayer, const wstring& _strRightLayer);

	void Clear()
	{
		memset(m_matrix, 0, sizeof(UINT) * MAX_LAYER);
	}
	const UINT(&GetMatrix())[MAX_LAYER] {
		return m_matrix;
	}
	void SetMatrix(UINT _matrix[MAX_LAYER]);

public:
	void tick();

private:
	//Layer안의 object에 충돌검사를 해준다.
	void CollisionBtwLayer(CLayer* _LeftLayer, CLayer* _RightLayer);
	//Object간에 충돌검사를 진행해 BeginOverlap, OnOverLap, EndOverlap 판별
	void CollisionBtwObject(CGameObject* _LeftObject, CGameObject* _RightObject);
	//Collider끼리 충돌했는지 확인
	bool CollisionBtwCollider(CCollider2D* _pLeft, CCollider2D* _pRight);
};
