#pragma once

enum ERaySpace
{
    NONE,
    VIEW,
    WORLD,
    LOCAL,
};

class CRay
{
private:
    Vec3        m_vOriginal;
    Vec3        m_vDirection;
    ERaySpace   m_ESpace;

public:
    /*static CRay*    RayAtWorldSpace(int _ScreenX, int _ScreenY);
    static CRay*    RayAtViewSpace(int _ScreenX, int _ScreenY);*/

    void            RayAtWorldSpace(int _ScreenX, int _ScreenY);
    void            RayAtViewSpace(int _ScreenX, int _ScreenY);
public:
    Vec3 GetOriginal() { return m_vOriginal; }
    Vec3 GetDirection() { return m_vDirection; }
    ERaySpace& GetSpace() { return m_ESpace; }

    void SetOriginal(Vec3 _original) { m_vOriginal = _original; }
    void SetDirection(Vec3 _direction) { m_vDirection = _direction; }
    void SetSpace(ERaySpace _space) { m_ESpace = _space; }
public:
    CRay();
    ~CRay();
};

