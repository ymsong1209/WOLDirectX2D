#include "pch.h"
#include "MaterialUI.h"

#include "ParamUI.h"

#include <Engine\CResMgr.h>
#include <Engine\CMaterial.h>

#include "TreeUI.h"


MaterialUI::MaterialUI()
    : ResUI(RES_TYPE::MATERIAL)
{
    SetName("Material");
}

MaterialUI::~MaterialUI()
{
}

int MaterialUI::render_update()
{
    ResUI::render_update();


    // Material 이름
    ImGui::Text("Material");
    ImGui::SameLine();

    Ptr<CMaterial> pMtrl = (CMaterial*)GetTargetRes().Get();
    string strKey = string(pMtrl->GetKey().begin(), pMtrl->GetKey().end());
    ImGui::InputText("##MtrlUIName", (char*)strKey.c_str(), ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly);

    

    // GraphicsShader 이름
    ImGui::Text("Shader  ");
    ImGui::SameLine();

    Ptr<CGraphicsShader> pShader = pMtrl->GetShader();
    if (nullptr != pShader)
    {
        string strKey = string(pShader->GetKey().begin(), pShader->GetKey().end());
        ImGui::InputText("##ShaderUIName", (char*)strKey.c_str(), strKey.length(), ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly);
       
    }
    else
    {
        char szEmtpy[10] = {};
        ImGui::InputText("##ShaderUIName", szEmtpy, 10, ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly);
        // 드랍 체크
        if (ImGui::BeginDragDropTarget())
        {
            // 해당 노드에서 마우스 뗀 경우, 지정한 PayLoad 키값이 일치한 경우
            const ImGuiPayload* pPayLoad = ImGui::AcceptDragDropPayload("Resource");
            if (pPayLoad)
            {
                TreeNode* pNode = (TreeNode*)pPayLoad->Data;
                CRes* pRes = (CRes*)pNode->GetData();
                if (RES_TYPE::GRAPHICS_SHADER == pRes->GetType())
                {
                    pMtrl->SetShader((CGraphicsShader*)pRes);
                }
            }

            ImGui::EndDragDropTarget();

            return 0;
        }

        return 1;
    }

    // Save Material
    if (ImGui::Button("Save Material")) {

        // open a file name
        OPENFILENAME ofn = {};

        wstring strAnimationFolderPath = CPathMgr::GetInst()->GetContentPath();
        strAnimationFolderPath += L"material\\";

        wchar_t szFilePath[256] = {};

        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = NULL;
        ofn.lpstrFile = szFilePath;
        ofn.lpstrFile[0] = '\0';
        ofn.nMaxFile = 256;
        ofn.lpstrFilter = L"mtrl\0*.mtrl\0ALL\0*.*";
        ofn.nFilterIndex = 1;
        ofn.lpstrFileTitle = NULL;
        ofn.nMaxFileTitle = 0;
        ofn.lpstrInitialDir = strAnimationFolderPath.c_str();
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

        if (GetSaveFileName(&ofn))
        {
            wstring filePath = wstring(szFilePath);

            wstring strContentPath = CPathMgr::GetInst()->GetContentPath();
            filePath = filePath.substr(strContentPath.length(), filePath.length() - strContentPath.length());

            pMtrl->Save(filePath.c_str());
        }
          
    }
    ImGui::NewLine();
    ImGui::Text("Parameter");


    // Shader 에서 요구하는 ScalarParameter 를 UI 에 노출
    const vector<tScalarParam>& vecScalarParam = pShader->GetScalarParam();

    for (size_t i = 0; i < vecScalarParam.size(); ++i)
    {
        switch (vecScalarParam[i].eParam)
        {
            // Shader Parameter 가 Int 타입인 경우
        case INT_0:
        case INT_1:
        case INT_2:
        case INT_3:
        case INT_4:
        case INT_5:
        case INT_6:
        case INT_7:
        {
            // 현재 머티리얼에 세팅된 값을 전달   
            int data = 0;
            pMtrl->GetScalarParam(vecScalarParam[i].eParam, &data);
            if (ParamUI::Param_Int(vecScalarParam[i].strDesc, &data))
            {
                // UI 쪽에서 값이 변경되었으면, 실제 머티리얼 에도 적용
                pMtrl->SetScalarParam(vecScalarParam[i].eParam, &data);
            }
        }
        break;
        case FLOAT_0:
        case FLOAT_1:
        case FLOAT_2:
        case FLOAT_3:
        {
            // 현재 머티리얼에 세팅된 값을 전달   
            float data = 0;
            pMtrl->GetScalarParam(vecScalarParam[i].eParam, &data);
            if (ParamUI::Param_Float(vecScalarParam[i].strDesc, &data))
            {
                // UI 쪽에서 값이 변경되었으면, 실제 머티리얼 에도 적용
                pMtrl->SetScalarParam(vecScalarParam[i].eParam, &data);
            }
        }
        break;
        case VEC2_0:
        case VEC2_1:
        case VEC2_2:
        case VEC2_3:
        {
            // 현재 머티리얼에 세팅된 값을 전달   
            Vec2 data;
            pMtrl->GetScalarParam(vecScalarParam[i].eParam, &data);
            if (ParamUI::Param_Vec2(vecScalarParam[i].strDesc, &data))
            {
                // UI 쪽에서 값이 변경되었으면, 실제 머티리얼 에도 적용
                pMtrl->SetScalarParam(vecScalarParam[i].eParam, &data);
            }
        }
        break;
        case VEC4_0:
        case VEC4_1:
        case VEC4_2:
        case VEC4_3:
        {
            // 현재 머티리얼에 세팅된 값을 전달   
            Vec4 data;
            pMtrl->GetScalarParam(vecScalarParam[i].eParam, &data);
            if (ParamUI::Param_Vec4(vecScalarParam[i].strDesc, &data))
            {
                // UI 쪽에서 값이 변경되었으면, 실제 머티리얼 에도 적용
                pMtrl->SetScalarParam(vecScalarParam[i].eParam, &data);
            }
        }
        break;
        case MAT_0:
        case MAT_1:
        case MAT_2:
        case MAT_3:
            break;
        }
    }

    // Shader 에서 요구하는 Texture Parameter 를 UI 에 노출
    const vector<tTexParam>& vecTexParam = pShader->GetTexParam();
    for (size_t i = 0; i < vecTexParam.size(); ++i)
    {
        ImGui::NewLine();
        Ptr<CTexture> pCurTex = pMtrl->GetTexParam(vecTexParam[i].eParam);
        if (ParamUI::Param_Tex(vecTexParam[i].strDesc, pCurTex, this, (UI_DELEGATE_1)&MaterialUI::SelectTexture))
        {
            m_eSelected = vecTexParam[i].eParam;
        }

        pMtrl->SetTexParam((TEX_PARAM)i, pCurTex);
    }

    return 0;
}


void MaterialUI::SelectTexture(DWORD_PTR _Key)
{
    string strKey = (char*)_Key;
    Ptr<CTexture> pTex = CResMgr::GetInst()->FindRes<CTexture>(wstring(strKey.begin(), strKey.end()));

    Ptr<CMaterial> pMtrl = (CMaterial*)GetTargetRes().Get();
    pMtrl->SetTexParam(m_eSelected, pTex);
}