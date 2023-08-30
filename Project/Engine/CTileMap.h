#pragma once
#include "CRenderComponent.h"



class CStructuredBuffer;
class CTexture;

class CTileMap :
    public CRenderComponent
{
private:
    UINT                m_iTileCountX;  // Ÿ�� ����
    UINT                m_iTileCountY;  // Ÿ�� ����

    Vec2                m_vSliceSize;   // Ÿ�� �ϳ��� ũ��(UV ����)
  

    vector<tTile>       m_vecTile;
    CStructuredBuffer*  m_Buffer;

    Ptr<CTexture>       m_pAtlas; //Material�� TexParam0�� ����ؾ���
    UINT                m_iAtlasTileCountX;
    UINT                m_iAtlasTileCountY;

public:
    virtual void finaltick() override;
    virtual void render() override;

    void UpdateData();

    void SetTileCount(UINT _iXCount, UINT _iYCount);
    void SetSliceSize(Vec2 _vSliceSize) { m_vSliceSize = _vSliceSize; }
    void SetAtlasTileCount(UINT _iXCount, UINT _iYCount) { m_iAtlasTileCountX = _iXCount; m_iAtlasTileCountY = _iYCount; }
    void SetCenterPos();
   
    void SetTile(vector<tTile> _tile);
    void SetTilemapAtlas(Ptr<CTexture> _atlas) { m_pAtlas = _atlas; }

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

    Ptr<CTexture>   GetAtlasTex() { return m_pAtlas; }
    vector<tTile>&  GetTile() { return m_vecTile; }
    int             GetTileCountX() { return (int)m_iTileCountX; }
    int             GetTileCountY() { return (int)m_iTileCountY; }
    Vec2            GetSliceSize() { return m_vSliceSize; }
    int             GetAtlasTileCountX() { return (int)m_iAtlasTileCountX; }
    int             GetAtlasTileCountY() { return (int)m_iAtlasTileCountY; }

    void Save(const wstring& _strRelativePath);
    void Load(const wstring& _strRelativePath);

    CLONE(CTileMap);
public:
    CTileMap();
    CTileMap(const CTileMap& _other);
    ~CTileMap();
};

