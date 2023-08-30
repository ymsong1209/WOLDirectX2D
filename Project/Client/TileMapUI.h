#pragma once
#include "ComponentUI.h"
class TileMapUI :
    public ComponentUI
{

public:
    virtual int render_update() override;

public:
    void LoadTile();

public:
    TileMapUI();
    ~TileMapUI();
};
