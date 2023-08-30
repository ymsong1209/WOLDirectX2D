#include "pch.h"
#include "TextureUI.h"
#include <Engine/CTexture.h>

TextureUI::TextureUI()
    : ResUI(RES_TYPE::TEXTURE)
{
    SetName("Texture");
}

TextureUI::~TextureUI()
{
}

int TextureUI::render_update()
{
    ResUI::render_update();

    // Material ¿Ã∏ß
    ImGui::Text("Texture");
    ImGui::SameLine();

    Ptr<CTexture> pTex = (CTexture*)GetTargetRes().Get();
    string strKey = string(pTex->GetKey().begin(), pTex->GetKey().end());
    ImGui::InputText("##TEXUIName", (char*)strKey.c_str(), ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly);

    ID3D11ShaderResourceView* Atlas = (pTex->GetSRV()).Get();
    float AtlasWidth = pTex->Width();
    float AtlasHeight = pTex->Height();
    static float MaterialUIzoom = 0.5f;

    if (ImGui::BeginChild("TextureUIimage", ImVec2(500.f, 500.f), false, ImGuiWindowFlags_HorizontalScrollbar))
    {
        ImVec2 uv_min = ImVec2(0.0f, 0.0f);                 // Top-left
        ImVec2 uv_max = ImVec2(1.0f, 1.0f);                 // Lower-right
        ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
        ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f); // 50% opaque white
        ImGui::Image((void*)Atlas, ImVec2(AtlasWidth * MaterialUIzoom, AtlasHeight * MaterialUIzoom), uv_min, uv_max, tint_col, border_col);
        ImGui::EndChild();
    }
  

    
    if (ImGui::InputFloat("zoom", &MaterialUIzoom, 0.5f, 1.0f))
    {
        if (MaterialUIzoom < 1.0f)
            MaterialUIzoom = 1.0f;
      
    }

    if (ImGui::SliderFloat("zoom2", &MaterialUIzoom, 0.5f, 20.f)) {

    };

    return 0;
}
