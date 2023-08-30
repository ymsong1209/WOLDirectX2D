#pragma once
#include <Engine/CScript.h>

class CMageBallAfterImageScript :
    public CScript
{
private:
    Vec4        m_vOutlineColor;
    Vec4        m_vCapeColor;
    float       m_fAlphaPerLife;
    float       m_fLifeTime;
public:

    virtual void begin() override;
    virtual void tick() override;

public:
    Vec4 GetOutlineColor() { return m_vOutlineColor; }
    void SetOutlineColor(Vec4 _Color) { m_vOutlineColor = _Color; }

    Vec4 GetCapeColor() { return m_vCapeColor; }
    void SetCapeColor(Vec4 _Color) { m_vCapeColor = _Color; }

    CLONE(CMageBallAfterImageScript);
public:
    CMageBallAfterImageScript();
    ~CMageBallAfterImageScript();

};