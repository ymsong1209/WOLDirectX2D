#pragma once
#include "UI.h"

class CGameObject;
class ComponentUI;
class CTexture;
class CAnim2D;

struct Point;

class AnimEditorUI :
    public UI
{
private:
    Ptr<CTexture>           m_pAnimAtlas;
    
   
    vector<string>          m_vecTexData;

   
    int                     m_iAtlasNum;
    int                     m_iCurAnimNum;

    bool                    m_bDrawBox;
    ImVec2                  m_vMouseStartPos;
    ImVec2                  m_vMouseEndPos;

    CGameObject             m_Gameobject;
    CAnim2D*                m_pAnim;
    vector<tAnim2DFrm>      m_vecFrm;
    Vec2                    m_vBackSize;
    Vec2                    m_vAnimLeftTop;
    Vec2                    m_vAnimSlice;
    float                   m_fDuration;
    Vec2                    m_vOffset;

    ImVec2                  m_vAtlasRegionMin;
    ImVec2                  m_vAtlasWindowPos;

    bool                    m_bLinearCut;
    ImVec2                  m_vSpace;
    int                     m_iLinearFrmCount;

    bool                    m_bGrid;
    bool                    m_bDivideByPixel;
    bool                    m_bSelectBFS;
   

public:
    virtual void tick() override;
    virtual int render_update() override;

public:
    void AddItem(const string& _strItem) { m_vecTexData.push_back(_strItem); }
    vector<string> GetTexData() { return m_vecTexData; }
    void Clear() {m_vecTexData.clear();}

    void ChooseAtlas();
    
    void AddAtlas();
    void RemoveAtlas();



    
    void RemoveFrm();
    void RemoveEveryFrm();
    void AddFrm();
    void AddFrmFromCur();
    void EditFrm();
    void SaveAnimation();
    void LoadAnimation();
    void DrawFrmList();
    void SetDuration();
    void CheckBacksize();
    
   
    bool CheckBoundaries(int x, int y, int width, int height)
    {
        return x >= 0 && x < width&& y >= 0 && y < height;
    }
    bool CheckAlpha(unsigned char* data, int x, int y, int width, int height);
   
    void GetAlphaBoundary(int x, int y, float _zoom);



public:
    AnimEditorUI();
    ~AnimEditorUI();
};

