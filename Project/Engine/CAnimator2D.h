#pragma once
#include "CComponent.h"

#include "ptr.h"
#include "CTexture.h"

class CAnim2D;

class CAnimator2D :
    public CComponent
{
private:
    map<wstring, CAnim2D*>  m_mapAnim;  // Animation 목록
    CAnim2D*                m_pCurAnim; // 현재 재생중인 Animation
    bool                    m_bRepeat;  // 반복
    int                     m_iSampleState; //0:이방성, 1:픽셀로


public:
    virtual void finaltick() override;
    void UpdateData();
    void Clear();

public:
    void Play(const wstring& _strName, bool _bRepeat);
    void Pause();
    void Reset();
    void SetRepeat(bool _bRepeat) { m_bRepeat = _bRepeat; }

    CAnim2D* FindAnim(const wstring& _strName);
    CAnim2D* LoadAnim(const wstring& _strRelativePath);
    void CreateAnimation(const wstring& _strAnimName, Ptr<CTexture> _AtlasTex, Vec2 _vLeftTop, Vec2 _vSlice, Vec2 _vBackSize, int _FrameCount, int _FPS);

    map<wstring, CAnim2D*>& GetMapAnim() { return m_mapAnim; }
    
    CAnim2D* GetCurAnim() { return m_pCurAnim; }
    bool     GetRepeat() { return m_bRepeat; }
    void     SetCurAnim(CAnim2D* _anim) { m_pCurAnim = _anim; }
    
    void     SetSamplerState(int _state) { m_iSampleState = _state; }
    const int& GetSamplerState() { return m_iSampleState; }

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;
    
    CLONE(CAnimator2D);
public:
    CAnimator2D();
    CAnimator2D(const CAnimator2D& _other);
    ~CAnimator2D();
};



