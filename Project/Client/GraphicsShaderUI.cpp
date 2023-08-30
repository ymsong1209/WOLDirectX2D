#include "pch.h"
#include "GraphicsShaderUI.h"

#include <Engine/CGraphicsShader.h>
#include "TreeUI.h"

GraphicsShaderUI::GraphicsShaderUI()
    : ResUI(RES_TYPE::GRAPHICS_SHADER)
{
    SetName("GraphicsShader");
}

GraphicsShaderUI::~GraphicsShaderUI()
{
}

int GraphicsShaderUI::render_update()
{
    ResUI::render_update();

    // GraphicsShader �̸�
    ImGui::Text("Shader  ");
    ImGui::SameLine();


    Ptr<CGraphicsShader> pShader = (CGraphicsShader*)GetTargetRes().Get();
    if (nullptr != pShader)
    {
        string strKey = string(pShader->GetKey().begin(), pShader->GetKey().end());
        ImGui::InputText("##GraphicsShaderUIName", (char*)strKey.c_str(), strKey.length(), ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly);

    }
    else
    {
        char szEmtpy[10] = {};
        ImGui::InputText("##GraphicsShaderUIName", szEmtpy, 10, ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly);
       
        SetParameter();

        return 1;
    }

    return 0;
}

void GraphicsShaderUI::SetParameter()
{
    Ptr<CGraphicsShader> pShader = (CGraphicsShader*)GetTargetRes().Get();
   

    //// Shader ���� �䱸�ϴ� ScalarParameter �� UI �� ����
    //const vector<tScalarParam>& vecScalarParam = pShader->GetScalarParam();

    //for (size_t i = 0; i < vecScalarParam.size(); ++i)
    //{
    //    switch (vecScalarParam[i].eParam)
    //    {
    //        // Shader Parameter �� Int Ÿ���� ���
    //    case INT_0:
    //    case INT_1:
    //    case INT_2:
    //    case INT_3:
    //    case INT_4:
    //    case INT_5:
    //    case INT_6:
    //    case INT_7:
    //    {

    //        pShader->AddScalarParam(INT_1, "Test Int");

    //        // ���� ��Ƽ���� ���õ� ���� ����   
    //        int data = 0;
    //        pMtrl->GetScalarParam(vecScalarParam[i].eParam, &data);
    //        if (ParamUI::Param_Int(vecScalarParam[i].strDesc, &data))
    //        {
    //            // UI �ʿ��� ���� ����Ǿ�����, ���� ��Ƽ���� ���� ����
    //            pMtrl->SetScalarParam(vecScalarParam[i].eParam, &data);
    //        }
    //    }
    //    break;
    //    case FLOAT_0:
    //    case FLOAT_1:
    //    case FLOAT_2:
    //    case FLOAT_3:
    //    {
    //        // ���� ��Ƽ���� ���õ� ���� ����   
    //        float data = 0;
    //        pMtrl->GetScalarParam(vecScalarParam[i].eParam, &data);
    //        if (ParamUI::Param_Float(vecScalarParam[i].strDesc, &data))
    //        {
    //            // UI �ʿ��� ���� ����Ǿ�����, ���� ��Ƽ���� ���� ����
    //            pMtrl->SetScalarParam(vecScalarParam[i].eParam, &data);
    //        }
    //    }
    //    break;
    //    case VEC2_0:
    //    case VEC2_1:
    //    case VEC2_2:
    //    case VEC2_3:
    //    {
    //        // ���� ��Ƽ���� ���õ� ���� ����   
    //        Vec2 data;
    //        pMtrl->GetScalarParam(vecScalarParam[i].eParam, &data);
    //        if (ParamUI::Param_Vec2(vecScalarParam[i].strDesc, &data))
    //        {
    //            // UI �ʿ��� ���� ����Ǿ�����, ���� ��Ƽ���� ���� ����
    //            pMtrl->SetScalarParam(vecScalarParam[i].eParam, &data);
    //        }
    //    }
    //    break;
    //    case VEC4_0:
    //    case VEC4_1:
    //    case VEC4_2:
    //    case VEC4_3:
    //    {
    //        // ���� ��Ƽ���� ���õ� ���� ����   
    //        Vec4 data;
    //        pMtrl->GetScalarParam(vecScalarParam[i].eParam, &data);
    //        if (ParamUI::Param_Vec4(vecScalarParam[i].strDesc, &data))
    //        {
    //            // UI �ʿ��� ���� ����Ǿ�����, ���� ��Ƽ���� ���� ����
    //            pMtrl->SetScalarParam(vecScalarParam[i].eParam, &data);
    //        }
    //    }
    //    break;
    //    case MAT_0:
    //    case MAT_1:
    //    case MAT_2:
    //    case MAT_3:
    //        break;
    //    }
    //}

    //// Shader ���� �䱸�ϴ� Texture Parameter �� UI �� ����
    //const vector<tTexParam>& vecTexParam = pShader->GetTexParam();
    //for (size_t i = 0; i < vecTexParam.size(); ++i)
    //{
    //    ImGui::NewLine();
    //    Ptr<CTexture> pCurTex = pMtrl->GetTexParam(vecTexParam[i].eParam);
    //    if (ParamUI::Param_Tex(vecTexParam[i].strDesc, pCurTex, this, (UI_DELEGATE_1)&MaterialUI::SelectTexture))
    //    {
    //        m_eSelected = vecTexParam[i].eParam;
    //    }

    //    pMtrl->SetTexParam((TEX_PARAM)i, pCurTex);
    //}
}
