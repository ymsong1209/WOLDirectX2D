#pragma once
#include "UI.h"

class CGameObject;
class ComponentUI;
class CTexture;
class CTileMap;


class TileMapAtlasEditorUI :
    public UI
{
private:
    Ptr<CTexture>           m_pTileMapAtlas;

    int                     m_iRow;
    int                     m_iCol;


    vector<tTile>           m_vAtlasInfo;
  

    bool                    m_bGrid;



public:
    void SetTexture(Ptr<CTexture> _other) { m_pTileMapAtlas = _other; }
   

public:
    virtual void tick() override;
    virtual int render_update() override;


public:
    TileMapAtlasEditorUI();
    ~TileMapAtlasEditorUI();

    
};

