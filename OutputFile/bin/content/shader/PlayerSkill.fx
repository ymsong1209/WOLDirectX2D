#ifndef _SKILLSHADER
#define _SKILLSHADER

#include "value.fx"
#include "func.fx"


// ======================================
// SkillShader
// RasterizerState      : None
// BlendState           : Mask
// DepthStencilState    : Less
//
// Parameter
#define bAnimUse        g_int_0
#define LeftTop         g_vec2_0
#define Slice           g_vec2_1
#define Offset          g_vec2_2
#define BackSize        g_vec2_3

// g_int_1              : NoiseTexture Use
// g_int_7              : SampleState


// g_tex_0              : Output Texture
// g_tex_1              : Nomal Texture

// float_0              : Show Percentage
// ======================================

struct VS_PlayerSkill_IN
{
    float3 vLocalPos : POSITION;
    float2 vUV : TEXCOORD;
};

struct VS_PlayerSkill_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
    float3 vWorldPos : POSITION;
};



VS_PlayerSkill_OUT VS_PlayerSkill(VS_PlayerSkill_IN _in)
{
    VS_PlayerSkill_OUT output = (VS_PlayerSkill_OUT) 0.f;
    
    output.vPosition = mul(float4(_in.vLocalPos, 1.f), g_matWVP);
    output.vUV = _in.vUV;
    output.vWorldPos = mul(float4(_in.vLocalPos, 1.f), g_matWorld).xyz;
    
        
    return output;
}


float4 PS_PlayerSkill(VS_PlayerSkill_OUT _in) : SV_Target
{
    float4 vOutColor = (float4) 0.f;
    
    if (g_btex_0)
    {
        if (bAnimUse)
        {
            float2 vUV = LeftTop + (BackSize * _in.vUV); //LeftTop좌상단으로 BackSize이동
            vUV -= ((BackSize - Slice) / 2.f); //Animation중앙으로 BackSize 이동
            vUV -= Offset; // Offset을 양수로 가기 위해선 뒷배경이 음수로 가야함
            
            if (LeftTop.x < vUV.x && vUV.x < LeftTop.x + Slice.x
                && LeftTop.y < vUV.y && vUV.y < LeftTop.y + Slice.y)
            {
                              
                if (g_int_7 == 0)
                {
                    vOutColor = g_tex_0.Sample(g_sam_0, vUV);
                }
                else
                {
                    vOutColor = g_tex_0.Sample(g_sam_1, vUV);
                }
            }
            else
            {
                //늘어난 background에 들어간 다른 애니메이션 파츠 제거
                //vOutColor = float4(1.f, 1.f, 0.f, 1.f);
                discard;
            }
        }
        else
        {
            if (g_int_7 == 0)
            {
                vOutColor = g_tex_0.Sample(g_sam_0, _in.vUV);
            }
            else
            {
                vOutColor = g_tex_0.Sample(g_sam_1, _in.vUV);
            }
        }
    }
    else
    {
        vOutColor = float4(1.f, 0.f, 1.f, 1.f);
    }
        
    float3 vNormal = (float3) 0.f;
    if (g_btex_1)
    {
        // Normal 값 추출
        vNormal = g_tex_1.Sample(g_sam_0, _in.vUV);
        
        // 0 ~ 1 범위를 -1 ~ 1 로 변경
        vNormal = (vNormal * 2.f) - 1.f;
        
        // NormalTexture 좌표계는 y축과 z 축이 반대로 되어있다.
        float f = vNormal.y;
        vNormal.y = vNormal.z;
        vNormal.z = f;
        
        // Texture 에서 추출한 Normal 방향을 월드로 변환시킨다.
        vNormal = normalize(mul(float4(vNormal, 0.f), g_matWorld)).xyz;
    }
    
    
    
    // Skill Percentage Check
    
    float2 vYPos = float2(0.5f, 0.f);
    float2 vCenterUV = float2(0.5, 0.5);
        //현재 검사해야하는 물체의 UV
    float2 vCurUV = _in.vUV;
        // 이미지의 중심에서 물체를 향하는 방향
    float2 vDir = normalize(vCurUV - vCenterUV);
    float2 vYDir = normalize(vYPos - vCenterUV);
    float angle = 360.f * g_float_0;
    
    if (g_float_0 != 1.f)
    {
        if (acos(dot(vDir, vYDir)) < radians(angle))
        {
          //acos는 0~180도를 반환함. 예외처리가 필요함.
            if (_in.vUV.x < 0.5)
            {
                if (radians(360.f) - acos(dot(vDir, vYDir)) < radians(angle))
                {
                    vOutColor = float4(vOutColor.r * 0.2, vOutColor.g * 0.2, vOutColor.b * 0.2, vOutColor.a);
                }
                else
                {
                    discard;
                }
            }
            else
            {
                vOutColor = float4(vOutColor.r * 0.2, vOutColor.g * 0.2, vOutColor.b * 0.2, vOutColor.a);
            }
        }
        else
        {
            discard;
        }
    }
   
    
    
    // Lighting 처리
    tLightColor LightColor = (tLightColor) 0.f;
     // vNormal 이 Zero Vector 라면
    if (dot(vNormal, vNormal) == 0.f)
    {
        CalcLight2D(_in.vWorldPos, LightColor);
    }
    else
    {
        CalcLight2D(_in.vWorldPos, vNormal, LightColor);
    }
        
    vOutColor.rgb *= (LightColor.vDiffuse.rgb + LightColor.vAmbient.rgb);
    

    
    
    
    return vOutColor;
}

#endif