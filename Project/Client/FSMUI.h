#pragma once

#include "ComponentUI.h"
#include <Engine\CScript.h>

class FSMUI :
    public ComponentUI
{
private:
    string      m_strScriptName;

public:
    virtual int render_update() override;

public:
    
public:
    FSMUI();
    ~FSMUI();
};
