#include "pch.h"
#include "MenuUI.h"

#include "CLevelSaveLoad.h"
#include <Engine\CEventMgr.h>
#include <Engine\CGameObject.h>
#include <Engine\components.h>

#include <Engine\CScript.h>
#include <Script\CScriptMgr.h>

#include <Engine/CResMgr.h>
#include <Engine/CMaterial.h>

#include "ImGuiMgr.h"
#include "OutlinerUI.h"
#include "InspectorUI.h"
#include "ContentUI.h"
#include "AnimEditorUI.h"
#include "TileMapEditorUI.h"
#include "LevelUI.h"
#include "WaveUI.h"

#include <Engine/CTimeMgr.h>

MenuUI::MenuUI()
    : UI("##Menu")
{
    SetName("Menu");
}

MenuUI::~MenuUI()
{
}

void MenuUI::finaltick()
{
    if (!IsActive())
        return;

    render_update();
}

int MenuUI::render_update()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Save Level"))
            {
                SaveLevel();
            }

            if (ImGui::MenuItem("Load Level"))
            {
                LoadLevel();
                //�ε��ɶ��� Stop���¿��� DT�� 0�̿�����.
                //CTimeMgr::GetInst()->SetTimeScale(0.f);
            }

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("GameObject"))
        {
            // ���� ������ ���ӿ�����Ʈ ����
            if (ImGui::MenuItem("Create Empty Object"))
            {
                CreateEmptyObject();
            }
            ImGui::Separator();


            if (ImGui::BeginMenu("Add Component"))
            {
                for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
                {
                    if (ImGui::MenuItem(ToString((COMPONENT_TYPE)i)))
                    {
                        AddComponent(COMPONENT_TYPE(i));
                    }
                }
                ImGui::EndMenu();
            }

            ImGui::Separator();

            if (ImGui::BeginMenu("Add Script"))
            {
                vector<wstring> vecScripts;
                CScriptMgr::GetScriptInfo(vecScripts);

                for (size_t i = 0; i < vecScripts.size(); ++i)
                {
                    string strScriptName = string(vecScripts[i].begin(), vecScripts[i].end());
                    if (ImGui::MenuItem(strScriptName.c_str()))
                    {
                        AddScript(vecScripts[i]);
                    }
                }

                ImGui::EndMenu();
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Content")) {
            // ���� ������ Material����
            if (ImGui::MenuItem("Create Material"))
            {
                CreateMaterial();
            }
            ImGui::Separator();
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Editor")) {
            if (ImGui::MenuItem("AnimEditor"))
            {
                AnimEditorUI* AnimEditor = (AnimEditorUI*)ImGuiMgr::GetInst()->FindUI("##AnimEditorUI");
                AnimEditor->SetActive(true);
            }
            if (ImGui::MenuItem("TileMapEditor")) {
                TileMapEditorUI* tileMapEditor = (TileMapEditorUI*)ImGuiMgr::GetInst()->FindUI("##TileMapEditorUI");
                tileMapEditor->SetActive(true);
            }
            if (ImGui::MenuItem("LevelEditor")) {
                LevelUI* levelEditor = (LevelUI*)ImGuiMgr::GetInst()->FindUI("##Level");
                levelEditor->SetActive(true);
            }
            if (ImGui::MenuItem("WaveEditor")) {
                WaveUI* WaveEditor = (WaveUI*)ImGuiMgr::GetInst()->FindUI("##Wave");
                WaveEditor->SetActive(true);
                WaveEditor->ResetWave();
            }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    return 0;
}

void MenuUI::SaveLevel()
{
    // open a file name
    OPENFILENAME ofn = {};

    wstring strFolderPath = CPathMgr::GetInst()->GetContentPath();
    strFolderPath += L"level\\";

    wchar_t szFilePath[256] = {};

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFilePath;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = 256;
    ofn.lpstrFilter = L"lv\0*.lv\0ALL\0*.*";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = strFolderPath.c_str();
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (false == GetSaveFileName(&ofn))
        return;


    wstring filePath = wstring(szFilePath);
    int length = filePath.length();
    if (length < 2 || filePath.substr(length - 3) != L".lv") {
        filePath.append(L".lv");
    }

    wstring path = CPathMgr::GetInst()->GetContentPath();
    int prefixLength = path.length();
    wstring subpath = wstring(filePath).substr(prefixLength);

    // Level ����
    CLevelSaveLoad::SaveLevel(subpath, CLevelMgr::GetInst()->GetCurLevel());

}

void MenuUI::LoadLevel()
{
    // open a file name
    OPENFILENAME ofn = {};

    wstring strFolderPath = CPathMgr::GetInst()->GetContentPath();
    strFolderPath += L"level\\";

    wchar_t szFilePath[256] = {};

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFilePath;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = 256;
    ofn.lpstrFilter = L"lv\0*.lv\0ALL\0*.*";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = strFolderPath.c_str();
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (false == GetOpenFileName(&ofn))
        return;

    wstring path = CPathMgr::GetInst()->GetContentPath();
    int prefixLength = path.length();
    wstring subpath = wstring(szFilePath).substr(prefixLength);

    // Level �ҷ�����
    CLevel* pLoadedLevel = CLevelSaveLoad::LoadLevel(subpath);

    tEvent evn = {};
    evn.Type = EVENT_TYPE::LEVEL_CHANGE;
    evn.wParam = (DWORD_PTR)pLoadedLevel;

    CEventMgr::GetInst()->AddEvent(evn);
}

void MenuUI::CreateEmptyObject()
{
    CGameObject* pNewObject = new CGameObject;
    pNewObject->AddComponent(new CTransform);
    pNewObject->SetName(L"New Object");
    SpawnGameObject(pNewObject, Vec3(0.f, 0.f, 0.f), 0);

    // Outliner �� �����´�.
    OutlinerUI* outliner = (OutlinerUI*)ImGuiMgr::GetInst()->FindUI("##Outliner");

    // �����߰��� ������Ʈ�� �����ͷ� �ϴ� ��尡 �߰��Ǹ�, ���û��·� �ΰ� �Ѵ�.
    outliner->SetSelectedNodeData(DWORD_PTR(pNewObject));
}

void MenuUI::AddComponent(COMPONENT_TYPE _type)
{
    // Outliner �� Inspector �� �����´�.
    OutlinerUI* outliner = (OutlinerUI*)ImGuiMgr::GetInst()->FindUI("##Outliner");
    InspectorUI* inspector = (InspectorUI*)ImGuiMgr::GetInst()->FindUI("##Inspector");

    // ���õ� ������Ʈ�� �����ͼ� ComponentType �� �´� ������Ʈ�� �����ؼ� �߰��Ѵ�.
    CGameObject* pSelectedObject = outliner->GetSelectedObject();

    if (nullptr == pSelectedObject) {
        wchar_t szStr[256] = {};
        wsprintf(szStr, L"���� Inspector�� ���õ� Object�� �����ϴ�. Outliner���� Object�� �����ʽÿ�.");
        MessageBox(nullptr, szStr, L"Component�߰� ����.", MB_OK);
        return;
    }
        

   

    switch (_type)
    {
    case COMPONENT_TYPE::TRANSFORM:
        pSelectedObject->AddComponent(new CTransform);
        break;
    case COMPONENT_TYPE::COLLIDER2D:
        pSelectedObject->AddComponent(new CCollider2D);
        break;
    case COMPONENT_TYPE::COLLIDER3D:
        //pSelectedObject->AddComponent(new CCollider3D);
        break;
    case COMPONENT_TYPE::ANIMATOR2D:
        pSelectedObject->AddComponent(new CAnimator2D);
        break;
    case COMPONENT_TYPE::ANIMATOR3D:
        //pSelectedObject->AddComponent(new CAnimator3D);
        break;
    case COMPONENT_TYPE::LIGHT2D:
        pSelectedObject->AddComponent(new CLight2D);
        break;
    case COMPONENT_TYPE::LIGHT3D:
        //pSelectedObject->AddComponent(new CLight3D);
        break;
    case COMPONENT_TYPE::CAMERA:
        pSelectedObject->AddComponent(new CCamera);
        break;
    case COMPONENT_TYPE::MESHRENDER:
        pSelectedObject->AddComponent(new CMeshRender);
        break;
    case COMPONENT_TYPE::PARTICLESYSTEM:
        pSelectedObject->AddComponent(new CParticleSystem);
        break;
    case COMPONENT_TYPE::TILEMAP:
        pSelectedObject->AddComponent(new CTileMap);
        break;
    case COMPONENT_TYPE::RIGIDBODY:
        pSelectedObject->AddComponent(new CRigidBody);
        break;
    case COMPONENT_TYPE::FSMCOM:
        pSelectedObject->AddComponent(new CFSM);
        break;
    case COMPONENT_TYPE::LANDSCAPE:
        //pSelectedObject->AddComponent(new CLandScape);
        break;
    case COMPONENT_TYPE::DECAL:
        //pSelectedObject->AddComponent(new CDecal);
        break;
    }

    // Inspector �� ���Ӱ� �߰��� ������Ʈ�� �˸��� ���ؼ� Ÿ���� �ٽ� �˷��ش�.
    inspector->SetTargetObject(pSelectedObject);

}

void MenuUI::AddScript(const wstring& _strScriptName)
{
    // Outliner �� Inspector �� �����´�.
    OutlinerUI* outliner = (OutlinerUI*)ImGuiMgr::GetInst()->FindUI("##Outliner");
    InspectorUI* inspector = (InspectorUI*)ImGuiMgr::GetInst()->FindUI("##Inspector");

    // ���õ� ������Ʈ�� �����ͼ� ComponentType �� �´� ������Ʈ�� �����ؼ� �߰��Ѵ�.
    CGameObject* pSelectedObject = outliner->GetSelectedObject();

    if (nullptr == pSelectedObject)
        return;

    CScript* pScript = CScriptMgr::GetScript(_strScriptName);

    pSelectedObject->AddComponent(pScript);
    inspector->SetTargetObject(pSelectedObject);
}

void MenuUI::CreateMaterial()
{
    Ptr<CMaterial> pMtrl = nullptr;
    pMtrl = new CMaterial();
    //pMtrl->SetShader(FindRes<CGraphicsShader>(L"Std2DShader"));
    CResMgr::GetInst()->AddRes(L"New Material", pMtrl);
    ContentUI* content = (ContentUI*)ImGuiMgr::GetInst()->FindUI("##Content");
    content->ResetContent();

}