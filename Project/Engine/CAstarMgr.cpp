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

// 매 틱마다 경로를 계산하므로 가야할 다음 타일의 위치만 반환함.
Vec2 CAstarMgr::SetFind(Vec3 _CurPos, Vec3 _DestPos)
{
    
    Vec2 CurTilePos = Vec2(_CurPos.x + m_vTileScale.x / 2, _CurPos.y + m_vTileScale.y / 2);
    Vec2 DestTilePos = Vec2(_DestPos.x + m_vTileScale.x / 2, _DestPos.y + m_vTileScale.y / 2);

    int CurPosX = (int)CurTilePos.x / m_vTileSize.x;
    int CurPosY = (int)CurTilePos.y / m_vTileSize.y;
    // Tile 배열은 좌상단이 0,0이지만, WorldPos는 중앙이 0,0
    // 즉, y를 뒤집어줘야함
    m_iCurPosX = CurPosX;
    m_iCurPosY = 79 - CurPosY;

    //여긴 왜 이런지 모르겠다.
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
    // 현재 지점에서 갈 수 있는 곳을 OpenList에 넣는다.
    // 노드 범위를 벗어난 경우
    if (_iXIdx < 0 || _iXIdx >= m_iXCount || _iYIdx < 0 || _iYIdx >= m_iYCount
        || !m_arrNode[_iYIdx][_iXIdx].bMove)
        return;


    // 해당 길이 닫힌 리스트에 있는 경우 넣지 않는다
    if (m_arrNode[_iYIdx][_iXIdx].bClosed)
        return;

    // Open List에 비용을 계산해서 넣는다.
    if (false == m_arrNode[_iYIdx][_iXIdx].bOpen)
    {
        CalculateCost(&m_arrNode[_iYIdx][_iXIdx], _pOrigin);
        // Open List 에 넣는다.
        m_arrNode[_iYIdx][_iXIdx].bOpen = true;
        m_OpenList.push(&m_arrNode[_iYIdx][_iXIdx]);
    }
    else // 이미 OpenList에 있는 경우
    {
        //비용을 계산해서 더 효율이 좋은 것으로 대체한다.
        tNode node = m_arrNode[_iYIdx][_iXIdx];
        CalculateCost(&node, _pOrigin);

        if (m_arrNode[_iYIdx][_iXIdx].fFinal > node.fFinal)
        {
            m_arrNode[_iYIdx][_iXIdx] = node;

            // 오픈리스트(우선순위큐) 재설정
            Rebuild(m_OpenList);
        }
    }
}
Vec2 CAstarMgr::FindPath()
{
    // 닫힌리스트 또는 이전에 OpenList에 있었다면 초기화
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
    // OpenList 초기화
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
    // 현재 위치 노드를 찾고 이미 그 위치에 있으므로 첫 노드를 닫힌리스트에 넣음.
    int iCurX = m_iCurPosX;
    int iCurY = m_iCurPosY;

    tNode* pCurNode = &m_arrNode[iCurY][iCurX];
    pCurNode->bClosed = true;

    while (true)
    {
        // 현재 지점에서 4방향의 노드를 OpenList 에 넣는다.
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

        //모든걸 다 돌았는데 아무것도 없음
        if (m_OpenList.empty()) {
            m_vToDestPos = Vec2(-1.f, -1.f);
            return m_vToDestPos;
        }

        // 2. Open List 에서 가장 효율이 좋은 노드를 꺼낸다.
        //  - 해당 노드는 ClostList 에 넣는다.
        pCurNode = m_OpenList.top();
        pCurNode->bClosed = true;

        m_OpenList.pop();

        // 목적지에 도착한 경우 Astar 종료
        if (pCurNode->iIdxX == m_iDestPosX && pCurNode->iIdxY == m_iDestPosY)
        {
            break;
        }
    }

    // 목적지까지 탐색이 끝났다면 왔던 노드를 되돌아가며 길 표시를 해줌.
    while (true)
    {
        m_arrNode[pCurNode->iIdxY][pCurNode->iIdxX].bPath = true;
        pCurNode = pCurNode->pPrevNode;

        if (pCurNode->iIdxX == m_iCurPosX && pCurNode->iIdxY == m_iCurPosY)
        {
            pCurNode->bPath = true;
            break;
        }
        // 현재 위치 바로 다음 타일 pos를 반환한다.
        if (pCurNode->pPrevNode->iIdxX == m_iCurPosX && pCurNode->pPrevNode->iIdxY == m_iCurPosY)
        {
            m_vToDestPos = pCurNode->vPos;
        }
    }

    //Dest가 갈 수 없는 곳이면 0, 0을 반환하므로 예외처리 필요
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
            
            // 타일의 이동가능 상태 옮겨오기
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