#include "pch.h"
#include "FSMUI.h"
#include <Engine/CScript.h>
#include <Script/CScriptMgr.h>

FSMUI::FSMUI()
	: ComponentUI("##FSM", COMPONENT_TYPE::FSMCOM)
{
	SetName("FSM");
}

FSMUI::~FSMUI()
{
}

int FSMUI::render_update()
{
	if (FALSE == ComponentUI::render_update())
		return FALSE;


	CScript* script = GetTarget()->FSM()->GetScript();
	if (script == nullptr) {
		ImGui::Text("Current State Script Name : None");
		return 0;
	}

	const wstring name = CScriptMgr::GetScriptName(script);
	m_strScriptName = string(name.begin(), name.end());
	ImGui::Text("Current State Script Name : ");
	ImGui::SameLine();
	ImGui::Text(m_strScriptName.c_str());



	return 0;
}

