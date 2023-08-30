#include "pch.h"
#include "WaveUI.h"
#include "TreeUI.h"
#include <Script/CMonsterSpawnPointScript.h>
#include <Engine/CResMgr.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CRay.h>
#include <Engine/CRenderMgr.h>
#include <Script/CSwordManScript.h>
#include <Script/CMageScript.h>
#include <Script/CGhoulScript.h>
#include <Script/CWaveWallHorScript.h>
#include <Script/CWaveWallVerScript.h>

WaveUI::WaveUI()
    :UI("##Wave")
    ,m_iWaveNum(0)
{
    SetName("Wave");
    m_CRay = new CRay();
}

WaveUI::~WaveUI()
{
    delete m_CRay;
}




void WaveUI::tick()
{
    if (!IsActive())
        return;

    //render_update();
}

int WaveUI::render_update()
{
    Vec2 pos = CKeyMgr::GetInst()->GetMousePos();
    Vec4 MousePos = Vec4(pos.x, pos.y, 1.f, 0.f);

    m_CRay->RayAtWorldSpace(MousePos.x, MousePos.y);

    Vec3 RayPos = m_CRay->GetDirection();
    m_vMousePos = Vec4(RayPos.x, RayPos.y, RayPos.z, 1.f);

	SelectMonster();
    SetWave();
    if (m_pWave) {
        ImGui::Text("Wave Num : ");
        ImGui::SameLine();
        if (ImGui::InputInt("##WaveNumWaveUI", &m_iWaveNum)) {
            CMonsterSpawnPointScript* Script = m_pWave->GetScript<CMonsterSpawnPointScript>();
            Script->SetWaveNum(m_iWaveNum);
        }
    }
    AddMonster();

    return 0;
}


void WaveUI::SelectMonster()
{
	const char* MonsterType[] = { "SwordMan","Wizard","Ghoul","HorizontalWall", "VerticalWall"};

	const char* lightinfo_preview_value = MonsterType[m_iMonsterType];
	static ImGuiComboFlags flags = 0;

    ImGui::Text("Monster Type");
	if (ImGui::BeginCombo("##MonsterType", lightinfo_preview_value, flags)) {
		for (int i = 0; i < IM_ARRAYSIZE(MonsterType); i++) {
			const bool is_selected = (m_iMonsterType == i);
            if (ImGui::Selectable(MonsterType[i], is_selected)) {
                m_iMonsterType = i;
            }
			

			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
}

void WaveUI::SetWave()
{
    // GraphicsShader 이름
    ImGui::Text("Wave : ");
    ImGui::SameLine();

    if (nullptr == m_pWave)
    {
        string strKey = "Empty Wave";
        ImGui::InputText("##WaveName", (char*)strKey.c_str(), strKey.length(), ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly);
    }
    else
    {
        string WaveName = string(m_pWave->GetName().begin(), m_pWave->GetName().end());
        char input_buffer[256]; // allocate a buffer for the input
        strcpy_s(input_buffer, WaveName.c_str());
        ImGui::InputText("##WaveName", input_buffer, 256, ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly);
    }
    // 드랍 체크
    if (ImGui::BeginDragDropTarget())
    {
        // 해당 노드에서 마우스 뗀 경우, 지정한 PayLoad 키값이 일치한 경우
        const ImGuiPayload* pPayLoad = ImGui::AcceptDragDropPayload("GameObject");
        if (pPayLoad)
        {
            CLayer* WaveLayer = CLevelMgr::GetInst()->GetCurLevel()->FindLayerByName(L"Wave");
            TreeNode* pNode = (TreeNode*)pPayLoad->Data;
            CGameObject* Wave = (CGameObject*)pNode->GetData();
            if (Wave->GetLayerIndex() == WaveLayer->GetLayerIndex()) {
                m_pWave = Wave;
                CMonsterSpawnPointScript* Script = m_pWave->GetScript<CMonsterSpawnPointScript>();
                m_iWaveNum = Script->GetWaveNum();
            }
        }
        ImGui::EndDragDropTarget();
    }
}



void WaveUI::AddMonster()
{
    if (m_pWave == nullptr) return;
    CMonsterSpawnPointScript* WaveScript = m_pWave->GetScript<CMonsterSpawnPointScript>();

    if (KEY_TAP(KEY::LBTN) && !ImGui::IsAnyItemHovered() && !ImGui::IsWindowHovered()) {
        //SwordMan
        if (m_iMonsterType == 0) {
            Ptr<CPrefab> SwordManPrefab = CResMgr::GetInst()->FindRes<CPrefab>(L"prefab\\SwordMan.prefab");
            CGameObject* SwordMan = SwordManPrefab->Instantiate();
            CSwordManScript* Script = SwordMan->GetScript<CSwordManScript>();
            Script->SetSwordManWaveNum(m_iWaveNum);
            Ptr<CTexture> SwordManPortrait = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\Enemy\\png\\SWORDMAN_PORTRAIT.png");
            SwordMan->MeshRender()->GetMaterial()->SetTexParam(TEX_0, SwordManPortrait);
            SwordMan->Transform()->SetRelativeScale(Vec3(200.f, 250.f, 1.f));
            SpawnGameObject(SwordMan, m_vMousePos, L"Monster");
        }
        else if (m_iMonsterType == 1) {
            Ptr<CPrefab> MagePrefab = CResMgr::GetInst()->FindRes<CPrefab>(L"prefab\\Mage.prefab");
            CGameObject* Mage = MagePrefab->Instantiate();
            CMageScript* Script = Mage->GetScript<CMageScript>();
            Script->SetMageWaveNum(m_iWaveNum);
            Ptr<CTexture> WizardPortrait = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\Enemy\\png\\WIZARD_PORTRAIT.png");
            Mage->MeshRender()->GetMaterial()->SetTexParam(TEX_0, WizardPortrait);
            SpawnGameObject(Mage, m_vMousePos, L"Monster");
        }
        else if (m_iMonsterType == 2) {
            Ptr<CPrefab> GhoulPrefab = CResMgr::GetInst()->FindRes<CPrefab>(L"prefab\\Ghoul.prefab");
            CGameObject* Ghoul = GhoulPrefab->Instantiate();
            CGhoulScript* Script = Ghoul->GetScript<CGhoulScript>();
            Script->SetGhoulWaveNum(m_iWaveNum);
            Ptr<CTexture> GhoulPortrait = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\Enemy\\png\\GHOUL_PORTRAIT.png");
            Ghoul->MeshRender()->GetMaterial()->SetTexParam(TEX_0, GhoulPortrait);
            SpawnGameObject(Ghoul, m_vMousePos, L"Monster");
        }
        else if (m_iMonsterType == 3) {
            Ptr<CPrefab> WallPrefab = CResMgr::GetInst()->FindRes<CPrefab>(L"prefab\\HorizontalWall.prefab");
            CGameObject* HorWall = WallPrefab->Instantiate();
            CWaveWallHorScript* Script = HorWall->GetScript<CWaveWallHorScript>();
            Script->SetWaveNum(m_iWaveNum);
            Ptr<CTexture> pri = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\Map\\PRISON_HOR.png");
            HorWall->MeshRender()->GetDynamicMaterial();
            HorWall->MeshRender()->GetMaterial()->SetTexParam(TEX_0, pri);
            SpawnGameObject(HorWall, m_vMousePos, L"Wall");
        }
        else if (m_iMonsterType == 4) {
            Ptr<CPrefab> WallPrefab = CResMgr::GetInst()->FindRes<CPrefab>(L"prefab\\VerticalWall.prefab");
            CGameObject* VerWall = WallPrefab->Instantiate();
            CWaveWallVerScript* Script = VerWall->GetScript<CWaveWallVerScript>();
            Script->SetWaveNum(m_iWaveNum);
            Ptr<CTexture> pri = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\WizardOfLegend\\Map\\PRISON_VER.png");
            VerWall->MeshRender()->GetDynamicMaterial();
            VerWall->MeshRender()->GetMaterial()->SetTexParam(TEX_0, pri);
            SpawnGameObject(VerWall, m_vMousePos, L"Wall");
        }
    }
}