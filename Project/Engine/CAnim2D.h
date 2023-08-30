#pragma once
#include "CEntity.h"

#include "ptr.h"
#include "CTexture.h"

class CAnimator2D;

class CAnim2D :
    public CEntity
{
private:
    CAnimator2D*        m_pOwner;
    vector<tAnim2DFrm>  m_vecFrm;
    Vec2                m_vBackSize;
    Ptr<CTexture>       m_AtlasTex;

    int                 m_iCurFrm;
    float               m_fTime;

    bool                m_bFinish;
    bool                m_bPause;
    
    wstring             m_RelativePath;
    
public:
    void finaltick();
    void Create(const wstring& _strAnimName, Ptr<CTexture> _AtlasTex, Vec2 _vLeftTop, Vec2 _vSlice, Vec2 _BackSize, int _FrameCount, int _FPS);
    void Save(const wstring& _strRelativePath);
    void Load(const wstring& _strRelativePath);


    vector<tAnim2DFrm> GetFrmList() { return m_vecFrm; }
    vector<tAnim2DFrm>& GetFrmListRef() { return m_vecFrm; }
    const tAnim2DFrm& GetCurFrame() { return m_vecFrm[m_iCurFrm]; }
    int GetCurFrameNum() { return m_iCurFrm; }
    Vec2 GetBackSize() { return m_vBackSize; }
    void SetBackSize(Vec2 _backsize) { m_vBackSize = _backsize; }
    Ptr<CTexture> GetAtlasTex() { return m_AtlasTex; }
    void SetAtlasTex(Ptr<CTexture> _atlas) { m_AtlasTex = _atlas; }

    wstring GetAnimRelativePath() { return m_RelativePath; }

    bool IsFinish() { return m_bFinish; }
    bool IsPause() { return m_bPause; }
    void Reset()
    {
        m_iCurFrm = 0;
        m_fTime = 0.f;
        m_bFinish = false;
    }
    
    void Pause() { m_bPause = !m_bPause; }

    CLONE(CAnim2D);
public:
    CAnim2D();
    CAnim2D(const CAnim2D& _other);
    ~CAnim2D();

    friend class CAnimator2D;
};

