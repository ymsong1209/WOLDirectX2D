#pragma once
#include "ComponentUI.h"
#include <Engine/CRigidBody.h>

class RigidBodyUI :
    public ComponentUI
{
private:
    Vec2    m_vAddForce;

public:
    virtual int render_update() override;



public:
    RigidBodyUI();
    ~RigidBodyUI();
};
