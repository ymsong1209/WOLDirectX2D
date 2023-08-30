#pragma once
#include "CSingleton.h"

class CTileMap;

typedef struct _tagNode
{
    _tagNode*  pPrevNode;   // ���� ���
    float      fFromParent; // ���� ��忡�� ���� �������� �Ÿ�
    float      fToDest;    // ���� ��忡�� ������ ������ �Ÿ�
    float      fFinal;       // ���� �� ���� ��ģ ��(�켱���� ����)
    Vec2       vPos;

    int         iIdxX;
    int         iIdxY;
    bool        bMove;   // �̵� ���� �Ұ���
    bool        bOpen;   // OpenList �� ������
    bool        bClosed; // ClostList �� ����ִ���

    bool        bPath;
}tNode;

class Compare
{
public:
    bool operator() (tNode* _pLeft, tNode* _pRight)
    {
        return _pLeft->fFinal > _pRight->fFinal;
    }
};

class CAstarMgr :
    public CSingleton<CAstarMgr>
{
    SINGLE(CAstarMgr);
private:
    int      m_iXCount;
    int      m_iYCount;
    int      m_iCurPosX;
    int      m_iCurPosY;
    int      m_iDestPosX;
    int      m_iDestPosY;
    tNode   m_arrNode[112][80]; // Ÿ�� ���� �°� �Է�
    Vec2   m_vTileSize;
    Vec2   m_vTileScale;
    Vec2    m_vToDestPos;
    priority_queue<tNode*, vector<tNode*>, Compare>   m_OpenList;

private:
    void Rebuild(priority_queue<tNode*, vector<tNode*>, Compare>& _queue);
    Vec2 FindPath();
    void CalculateCost(tNode* _pCurNode, tNode* _pOrigin);
    void AddOpenList(int _iXIdx, int _iYIdx, tNode* _pOrigin);

public:
    Vec2 SetFind(Vec3 _CurPos, Vec3 _DestPos);
    void LoadTile(CTileMap* _Tile);
};
