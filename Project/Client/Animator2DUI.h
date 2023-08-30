#pragma once
#include "ComponentUI.h"

class Animator2DUI :
    public ComponentUI
{
private:
    vector<string>      m_vAnimList;
    int                 m_iAnimNum;
   
    bool                m_bLoop;



public:
    virtual int render_update() override;


    void LoadAnim();
    void AddItem(const string& _strItem) { m_vAnimList.push_back(_strItem); }
    vector<string> GetTexData() { return m_vAnimList; }
    void RemoveAnim();
    void Clear() { m_vAnimList.clear(); }


    void ChooseSamplerState();
public:
    Animator2DUI();
    ~Animator2DUI();
};
