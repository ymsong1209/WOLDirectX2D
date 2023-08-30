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
	//��� Layer�� ���� �浹�ϴ��� �����ִ� �Լ�
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
	//Layer���� object�� �浹�˻縦 ���ش�.
	void CollisionBtwLayer(CLayer* _LeftLayer, CLayer* _RightLayer);
	//Object���� �浹�˻縦 ������ BeginOverlap, OnOverLap, EndOverlap �Ǻ�
	void CollisionBtwObject(CGameObject* _LeftObject, CGameObject* _RightObject);
	//Collider���� �浹�ߴ��� Ȯ��
	bool CollisionBtwCollider(CCollider2D* _pLeft, CCollider2D* _pRight);
};
