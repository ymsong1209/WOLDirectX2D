#include "pch.h"
#include "CChildScript.h"
#include <Engine/CResMgr.h>
#include <Engine/CTexture.h>

CChildScript::CChildScript()
	: CScript((UINT)SCRIPT_TYPE::CHILDSCRIPT)
{
	//m_pTex = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\Fighter.bmp");
	AddScriptTexParam(m_pTex, "Texture");
}

CChildScript::~CChildScript()
{
}

void CChildScript::begin()
{
	MeshRender()->GetDynamicMaterial();
	
	//m_pTex = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\Fighter.bmp");
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, m_pTex);

}

void CChildScript::tick()
{
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, m_pTex);
}

void CChildScript::BeginOverlap(CCollider2D* _Other)
{
	if (L"Parent Object" == _Other->GetOwner()->GetName())
	{
		//Destroy();	

		//SetLifeSpan(2.f);
	}
}
