#include "pch.h"
#include "RigidBodyUI.h"

#include <Engine/CRigidBody.h>

RigidBodyUI::RigidBodyUI()
	: ComponentUI("##RigidBody", COMPONENT_TYPE::RIGIDBODY)
	, m_vAddForce(Vec2(0.f,0.f))
{
	SetName("RigidBody");
}

RigidBodyUI::~RigidBodyUI()
{
}

int RigidBodyUI::render_update() {

	if (FALSE == ComponentUI::render_update())
		return FALSE;


	CRigidBody* RigidBody = GetTarget()->RigidBody();

	//Force-----------//
	Vec2 Force = Vec2(RigidBody->m_vForce.x, RigidBody->m_vForce.y);
	ImGui::Text("Force : ");
	ImGui::SameLine();
	if (ImGui::InputFloat2("##Force", Force)) {
		RigidBody->m_vForce = Force;
	}

	if (ImGui::InputFloat2("##AddForce", m_vAddForce)) {

	}
	ImGui::SameLine();
	if (ImGui::Button("AddForce")) {
		RigidBody->AddForce(m_vAddForce);
	}

	//Mass------------//

	float Mass = RigidBody->m_fMass;
	ImGui::Text("Mass : ");
	ImGui::SameLine();
	if (ImGui::InputFloat("##Mass", &Mass)) {
		RigidBody->SetMass(Mass);
	}
	//Velocity---------//
	Vec2 Velocity = RigidBody->GetVelocity();
	ImGui::Text("Velocity : ");
	ImGui::SameLine();
	if (ImGui::InputFloat2("##Velocity", Velocity)) {
		RigidBody->SetVelocity(Velocity);
	}

	float VelocityLimit = RigidBody->m_fVelocityLimit;
	ImGui::Text("VelocityLimit : ");
	ImGui::SameLine();
	if (ImGui::InputFloat("##VelocityLimit", &VelocityLimit)) {
		RigidBody->SetVelocityLimit(VelocityLimit);
	}

	
	//Friction-----//

	float Friction = RigidBody->m_fFriction;
	ImGui::Text("Friction : ");
	ImGui::SameLine();
	if (ImGui::InputFloat("##Friction", &Friction)) {
		RigidBody->SetFriction(Friction);
	}

	float FrictionScale = RigidBody->m_fFrictionScale;
	ImGui::Text("FrictionScale : ");
	ImGui::SameLine();
	if (ImGui::InputFloat("##FrictionScale", &FrictionScale)) {
		RigidBody->SetFrictionScale(FrictionScale);
	}
	//Ground-----//


	bool IsGround = RigidBody->GetGround();
	string IsGroundBool;
	if (IsGround) {
		IsGroundBool = "True##IsGround";
	}
	else {
		IsGroundBool = "False##IsGround";
	}

	ImGui::Text("IsGround : ");
	ImGui::SameLine();
	if (ImGui::Button(IsGroundBool.c_str())) {
		IsGround = !IsGround;
		RigidBody->SetGround(IsGround);
	}


	//Gravity------//
	bool GravityUse = RigidBody->GetGravityUse();
	string GravityBool;
	

	if (GravityUse) {
		GravityBool = "True##Gravity";
	}
	else {
		GravityBool = "False##Gravity";
	}
	ImGui::Text("Gravity Use : ");
	ImGui::SameLine();
	if (ImGui::Button(GravityBool.c_str())) {
		GravityUse = !GravityUse;
		RigidBody->SetGravity(GravityUse);
	}

	if (GravityUse) {
		float GravityAccel = RigidBody->m_fGravityAccel;
		ImGui::Text("GravityAccel : ");
		ImGui::SameLine();
		if (ImGui::InputFloat("##GravityAccel", &GravityAccel)) {
			RigidBody->SetGravityAccel(GravityAccel);
		}

		float GravityLimit = RigidBody->m_fGravityLimit;
		ImGui::Text("GravityLimit : ");
		ImGui::SameLine();
		if (ImGui::InputFloat("##GravityLimit", &GravityLimit)) {
			RigidBody->SetGravityVelocityLimit(GravityLimit);
		}
	}


	return TRUE;
}


