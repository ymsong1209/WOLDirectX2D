#include "pch.h"
#include "CAstarMgr.h"
#include "CTileMap.h"
#include "CTransform.h"

CAstarMgr::CAstarMgr()
    : m_iXCount(0)
    , m_iYCount(0)
    , m_iCurPosX(0)
    , m_iCurPosY(0)
    , m_iDestPosX(0)
    , m_iDestPosY(0)
    , m_vTileSize{}
    , m_vTileScale{}
    , m_OpenList{}
    , m_vToDestPos(0.f,0.f)
{
}
CAstarMgr::~CAstarMgr()
{
}

// �� ƽ���� ��θ� ����ϹǷ� ������ ���� Ÿ���� ��ġ�� ��ȯ��.
Vec2 CAstarMgr::SetFind(Vec3 _CurPos, Vec3 _DestPos)
{
    
    Vec2 CurTilePos = Vec2(_CurPos.x + m_vTileScale.x / 2, _CurPos.y + m_vTileScale.y / 2);
    Vec2 DestTilePos = Vec2(_DestPos.x + m_vTileScale.x / 2, _DestPos.y + m_vTileScale.y / 2);

    int CurPosX = (int)CurTilePos.x / m_vTileSize.x;
    int CurPosY = (int)CurTilePos.y / m_vTileSize.y;
    // Tile �迭�� �»���� 0,0������, WorldPos�� �߾��� 0,0
    // ��, y�� �����������
    m_iCurPosX = CurPosX;
    m_iCurPosY = 79 - CurPosY;

    //���� �� �̷��� �𸣰ڴ�.
    m_iDestPosX = (int)DestTilePos.x / m_vTileSize.x;
    m_iDestPosY = 80 - (int)DestTilePos.y / m_vTileSize.y;

   
    Vec2 Pos = FindPath();
    m_vToDestPos;
  
    return Vec2(m_vToDestPos.x,m_vToDestPos.y);
}

void CAstarMgr::Rebuild(priority_queue<tNode*, vector<tNode*>, Compare>& _queue)
{
    priority_queue<tNode*, vector<tNode*>, Compare> tempQueue;

    while (!_queue.empty())
    {
        tempQueue.push(_queue.top());
        _queue.pop();
    }
    _queue.swap(tempQueue);
}

void CAstarMgr::CalculateCost(tNode* _pCurNode, tNode* _pOrigin)
{
    _pCurNode->pPrevNode = _pOrigin;
    _pCurNode->fFromParent = (m_vTileSize.x + m_vTileSize.y) / 2 + _pOrigin->fFromParent;
    _pCurNode->fToDest = abs(m_iDestPosX - _pCurNode->iIdxX) * m_vTileSize.x + abs(m_iDestPosY - _pCurNode->iIdxY) * m_vTileSize.y;
    _pCurNode->fFinal = _pCurNode->fFromParent + _pCurNode->fToDest;
}

void CAstarMgr::AddOpenList(int _iXIdx, int _iYIdx, tNode* _pOrigin)
{
    // ���� �������� �� �� �ִ� ���� OpenList�� �ִ´�.
    // ��� ������ ��� ���
    if (_iXIdx < 0 || _iXIdx >= m_iXCount || _iYIdx < 0 || _iYIdx >= m_iYCount
        || !m_arrNode[_iYIdx][_iXIdx].bMove)
        return;


    // �ش� ���� ���� ����Ʈ�� �ִ� ��� ���� �ʴ´�
    if (m_arrNode[_iYIdx][_iXIdx].bClosed)
        return;

    // Open List�� ����� ����ؼ� �ִ´�.
    if (false == m_arrNode[_iYIdx][_iXIdx].bOpen)
    {
        CalculateCost(&m_arrNode[_iYIdx][_iXIdx], _pOrigin);
        // Open List �� �ִ´�.
        m_arrNode[_iYIdx][_iXIdx].bOpen = true;
        m_OpenList.push(&m_arrNode[_iYIdx][_iXIdx]);
    }
    else // �̹� OpenList�� �ִ� ���
    {
        //����� ����ؼ� �� ȿ���� ���� ������ ��ü�Ѵ�.
        tNode node = m_arrNode[_iYIdx][_iXIdx];
        CalculateCost(&node, _pOrigin);

        if (m_arrNode[_iYIdx][_iXIdx].fFinal > node.fFinal)
        {
            m_arrNode[_iYIdx][_iXIdx] = node;

            // ���¸���Ʈ(�켱����ť) �缳��
            Rebuild(m_OpenList);
        }
    }
}
Vec2 CAstarMgr::FindPath()
{
    // ��������Ʈ �Ǵ� ������ OpenList�� �־��ٸ� �ʱ�ȭ
    for (int i = 0; i < 112; ++i)
    {
        for (int j = 0; j < 80; ++j)
        {
            if (true == m_arrNode[i][j].bClosed || true == m_arrNode[i][j].bOpen)
            {
                m_arrNode[i][j].bClosed = false;
                m_arrNode[i][j].bOpen = false;
                m_arrNode[i][j].bPath = false;
                m_arrNode[i][j].fFinal = 0.f;
                m_arrNode[i][j].fFromParent = 0.f;
                m_arrNode[i][j].fToDest = 0.f;
                m_arrNode[i][j].pPrevNode = nullptr;
            }
        }
    }
    // OpenList �ʱ�ȭ
    //Code 1.
    while (!m_OpenList.empty())
    {
        tNode* node = m_OpenList.top();
        m_OpenList.pop();
    }
    ////Code 2
  /*  priority_queue<tNode*, vector<tNode*>, Compare> newQueue;
    m_OpenList = newQueue;*/

    m_vToDestPos = Vec2(0.f, 0.f);
    if (false == m_arrNode[m_iDestPosY][m_iDestPosX].bMove
        || m_iCurPosX == m_iDestPosX && m_iCurPosY == m_iDestPosY)
    {
        return m_vToDestPos;
    }
    // ���� ��ġ ��带 ã�� �̹� �� ��ġ�� �����Ƿ� ù ��带 ��������Ʈ�� ����.
    int iCurX = m_iCurPosX;
    int iCurY = m_iCurPosY;

    tNode* pCurNode = &m_arrNode[iCurY][iCurX];
    pCurNode->bClosed = true;

    while (true)
    {
        // ���� �������� 4������ ��带 OpenList �� �ִ´�.
        // UP
        AddOpenList(pCurNode->iIdxX
            , pCurNode->iIdxY - 1, pCurNode);

        // RIGHT      
        AddOpenList(pCurNode->iIdxX + 1
            , pCurNode->iIdxY, pCurNode);

        // DOWN      
        AddOpenList(pCurNode->iIdxX
            , pCurNode->iIdxY + 1, pCurNode);

        // LEFT      
        AddOpenList(pCurNode->iIdxX - 1
            , pCurNode->iIdxY, pCurNode);

        // DIAGONAL
        AddOpenList(pCurNode->iIdxX - 1
            , pCurNode->iIdxY - 1, pCurNode);

        AddOpenList(pCurNode->iIdxX - 1
            , pCurNode->iIdxY + 1, pCurNode);

        AddOpenList(pCurNode->iIdxX + 1
            , pCurNode->iIdxY + 1, pCurNode);

        AddOpenList(pCurNode->iIdxX + 1
            , pCurNode->iIdxY - 1, pCurNode);

        //���� �� ���Ҵµ� �ƹ��͵� ����
        if (m_OpenList.empty()) {
            m_vToDestPos = Vec2(-1.f, -1.f);
            return m_vToDestPos;
        }

        // 2. Open List ���� ���� ȿ���� ���� ��带 ������.
        //  - �ش� ���� ClostList �� �ִ´�.
        pCurNode = m_OpenList.top();
        pCurNode->bClosed = true;

        m_OpenList.pop();

        // �������� ������ ��� Astar ����
        if (pCurNode->iIdxX == m_iDestPosX && pCurNode->iIdxY == m_iDestPosY)
        {
            break;
        }
    }

    // ���������� Ž���� �����ٸ� �Դ� ��带 �ǵ��ư��� �� ǥ�ø� ����.
    while (true)
    {
        m_arrNode[pCurNode->iIdxY][pCurNode->iIdxX].bPath = true;
        pCurNode = pCurNode->pPrevNode;

        if (pCurNode->iIdxX == m_iCurPosX && pCurNode->iIdxY == m_iCurPosY)
        {
            pCurNode->bPath = true;
            break;
        }
        // ���� ��ġ �ٷ� ���� Ÿ�� pos�� ��ȯ�Ѵ�.
        if (pCurNode->pPrevNode->iIdxX == m_iCurPosX && pCurNode->pPrevNode->iIdxY == m_iCurPosY)
        {
            m_vToDestPos = pCurNode->vPos;
        }
    }

    //Dest�� �� �� ���� ���̸� 0, 0�� ��ȯ�ϹǷ� ����ó�� �ʿ�
    return m_vToDestPos;
}

void CAstarMgr::LoadTile(CTileMap* _Tile)
{
    m_vTileSize = _Tile->GetSliceSize() * Vec2(_Tile->Transform()->GetRelativeScale().x, _Tile->Transform()->GetRelativeScale().y);
    //m_vTileSize = _Tile->GetSliceSize() * Vec2(_Tile->GetAtlasTex()->Width(), _Tile->GetAtlasTex()->Height());
    m_vTileScale = _Tile->GetOwner()->Transform()->GetRelativeScale();
    vector<tTile> vecTile = _Tile->GetTile();
    m_iXCount = _Tile->GetTileCountX();
    m_iYCount = _Tile->GetTileCountY();
    for (int i = 0; i < m_iYCount; ++i)
    {
        for (int j = 0; j < m_iXCount; ++j)
        {
            m_arrNode[i][j].iIdxX = (int)j;
            m_arrNode[i][j].iIdxY = (int)i;

            m_arrNode[i][j].vPos = vecTile[j + i * m_iXCount].vCenterPos;

            int tmp = j + i * m_iXCount;
            if (i == 5 && j == 79) {
                int a = 0;
                tmp = j + i * m_iXCount;
            }
            
            // Ÿ���� �̵����� ���� �Űܿ���
            if (1 == vecTile[j + i * m_iXCount].Type) {
                
                m_arrNode[i][j].bMove = true;
            }
            else
                m_arrNode[i][j].bMove = false;
            m_arrNode[i][j].bClosed = false;
            m_arrNode[i][j].bOpen = false;
            m_arrNode[i][j].bPath = false;
            m_arrNode[i][j].fFinal = 0.f;
            m_arrNode[i][j].fFromParent = 0.f;
            m_arrNode[i][j].fToDest = 0.f;
            m_arrNode[i][j].pPrevNode = nullptr;
        }
    }
}