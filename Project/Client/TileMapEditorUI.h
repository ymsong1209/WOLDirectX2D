#pragma once
#include "UI.h"

class CGameObject;
class ComponentUI;
class CTexture;
class CTileMap;


class TileMapEditorUI :
    public UI
{

private:
    Ptr<CTexture>           m_pTileMapAtlas;
    CTileMap*               m_pTileMap;

    int                     m_iTileType;

    float                   m_fAtlasWidth;
    float                   m_fAtlasHeight;
    int                     m_iAtlasRow;
    int                     m_iAtlasCol;

    bool                    m_bAtlasButton;
    bool                    m_bTilePropertyButton;

    int                     m_iRow;
    int                     m_iCol;

    int                     m_iCurTile;

   

   
    vector<tTile>           m_vecAtlasInfo;
    vector<tTile>           m_vecTile;

    Vec2                    m_vSliceSize; //UV ±‚¡ÿ




public:

    void LoadTexture();
    void SaveTileMap();
    void LoadTileMap();

    void SetAtlasRowCol(int _irow, int _icol) { m_iAtlasRow = _irow; m_iAtlasCol = _icol; }
    void SetAtlas(Ptr<CTexture> _atlas) { m_pTileMapAtlas = _atlas; }
    void SetAtlasInfo();

    void SetImageToAtlas();


    void DrawAtlasSlice();
    void DrawTileMap();

    void IdlePushBack();


public:
    virtual void tick() override;
    virtual int render_update() override;

public:
   
public:
    TileMapEditorUI();
    ~TileMapEditorUI();

    
};

