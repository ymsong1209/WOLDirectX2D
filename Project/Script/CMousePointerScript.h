#pragma once

#include <Engine/CScript.h>
class CRay;


class CMousePointerScript :
    public CScript
{
private:
    Vec4        m_vMousePos;
    Vec4        m_vConvertedMousePos;
    CRay*       m_CRay;
  
public:

    Vec4        GetMousePos() { return m_vConvertedMousePos; }

    virtual void begin() override;
    virtual void tick() override;



private:

    CLONE(CMousePointerScript);
   
public:
    CMousePointerScript();
    ~CMousePointerScript();
};