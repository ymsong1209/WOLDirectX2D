#ifndef _OUTLINE
#define _OUTLINE

#include "value.fx"
#include "func.fx"

// ======================================
// OutlineShader
// RasterizerState      : None
// BlendState           : LESS
// DepthStencilState    : ALPHA_BLEND
//
// Parameter
#define bAnimUse        g_int_0
#define LeftTop         g_vec2_0
#define Slice           g_vec2_1
#define Offset          g_vec2_2
#define BackSize        g_vec2_3


// g_int_7              : SampleState

// g_tex_0              : Output Texture
// g_tex_1              : Normal Texture

// g_float_0            : AlphablendPercentage

// g_vec4_0             : OutlineColor
// g_vec4_1             : CapeColor
// ======================================

struct VS_Outline_IN
{
    float3 vLocalPos : POSITION;
    float2 vUV : TEXCOORD;
};

struct VS_Outline_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
    float3 vWorldPos : POSITION;
};



VS_Outline_OUT VS_Outline(VS_Outline_IN _in)
{
    VS_Outline_OUT output = (VS_Outline_OUT) 0.f;
    
    output.vPosition = mul(float4(_in.vLocalPos, 1.f), g_matWVP);
    output.vUV = _in.vUV;
    output.vWorldPos = mul(float4(_in.vLocalPos, 1.f), g_matWorld).xyz;
    
        
    return output;
}


float4 PS_Outline(VS_Outline_OUT _in) : SV_Target
{
    float4 vOutColor = (float4) 0.f;
    
    if (g_btex_0)
    {
        if (bAnimUse)
        {
            float2 vUV = LeftTop + (BackSize * _in.vUV); //LeftTop�»������ BackSize�̵�
            vUV -= ((BackSize - Slice) / 2.f); //Animation�߾����� BackSize �̵�
            vUV -= Offset; // Offset�� ����� ���� ���ؼ� �޹���� ������ ������
            
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
                //�þ background�� �� �ٸ� �ִϸ��̼� ���� ����
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
        vOutColor = float4(0.f, 0.f, 1.f, 1.f);
    }
        
    float3 vNormal = (float3) 0.f;
    if (g_btex_1)
    {
        // Normal �� ����
        vNormal = g_tex_1.Sample(g_sam_0, _in.vUV);
        
        // 0 ~ 1 ������ -1 ~ 1 �� ����
        vNormal = (vNormal * 2.f) - 1.f;
        
        // NormalTexture ��ǥ��� y��� z ���� �ݴ�� �Ǿ��ִ�.
        float f = vNormal.y;
        vNormal.y = vNormal.z;
        vNormal.z = f;
        
        // Texture ���� ������ Normal ������ ����� ��ȯ��Ų��.
        vNormal = normalize(mul(float4(vNormal, 0.f), g_matWorld)).xyz;
    }
    
    
    
    //if (0.f == vOutColor.a)
    //    discard;
    if (vOutColor.r == vOutColor.g && vOutColor.g == vOutColor.b)
    {
        if (0.f < vOutColor.r && vOutColor.r <= (10.f / 255.0f) || g_vec4_1.a == 0.f)
        {
            
        }
        else
        {
            vOutColor.r *= g_vec4_1.r;
            vOutColor.g *= g_vec4_1.g;
            vOutColor.b *= g_vec4_1.b;
        }
    }
        
    
    // Outlineó��
    if (g_vec4_0.a == 0.f)
    {
        
    }
    else
    {
        float2 OutlineUV = float2(_in.vUV.x, _in.vUV.y - 0.02f);
        float4 OutlineUp = Outline(_in.vWorldPos, OutlineUV);
        OutlineUp.rgb = float3(g_vec4_0.r, g_vec4_0.g, g_vec4_0.b);
        OutlineUp.a = OutlineUp.a - vOutColor.a;
        if (OutlineUp.a > 0)
        {
            vOutColor = float4(OutlineUp.r, OutlineUp.g, OutlineUp.b, OutlineUp.a);
        }
    
    
        OutlineUV = float2(_in.vUV.x, _in.vUV.y + 0.02f);
        float4 OutlineDown = Outline(_in.vWorldPos, OutlineUV);
        OutlineDown.rgb = float3(g_vec4_0.r, g_vec4_0.g, g_vec4_0.b);
        OutlineDown.a = OutlineDown.a - vOutColor.a;
        if (OutlineDown.a > 0.f)
        {
            vOutColor = float4(OutlineDown.r, OutlineDown.g, OutlineDown.b, OutlineDown.a);
        }
  
        OutlineUV = float2(_in.vUV.x + 0.02f, _in.vUV.y);
        float4 OutlineLeft = Outline(_in.vWorldPos, OutlineUV);
        OutlineLeft.rgb = float3(g_vec4_0.r, g_vec4_0.g, g_vec4_0.b);
        OutlineLeft.a = OutlineLeft.a - vOutColor.a;
        if (OutlineLeft.a > 0.f)
        {
            vOutColor = float4(OutlineLeft.r, OutlineLeft.g, OutlineLeft.b, OutlineLeft.a);
        }
    
        OutlineUV = float2(_in.vUV.x - 0.02f, _in.vUV.y);
        float4 OutlineRight = Outline(_in.vWorldPos, OutlineUV);
        OutlineRight.rgb = float3(g_vec4_0.r, g_vec4_0.g, g_vec4_0.b);
        OutlineRight.a = OutlineRight.a - vOutColor.a;
        if (OutlineRight.a > 0.f)
        {
            vOutColor = float4(OutlineRight.r, OutlineRight.g, OutlineRight.b, OutlineRight.a);
        }
    }
    
    
   
    // Lighting ó��
    tLightColor LightColor = (tLightColor) 0.f;
     // vNormal �� Zero Vector ���
    if (dot(vNormal, vNormal) == 0.f)
    {
        CalcLight2D(_in.vWorldPos, LightColor);
    }
    else
    {
        CalcLight2D(_in.vWorldPos, vNormal, LightColor);
    }
        
    vOutColor.rgb *= (LightColor.vDiffuse.rgb + LightColor.vAmbient.rgb);
    
    
    
  
    
    // alphablendó��
    if (0.f == vOutColor.a)
        discard;
    vOutColor.a = 1.0f - g_float_0;
    //vOutColor.a = 0.2f;
    
    
    //return OutlineLeft;
    return vOutColor;
}

#endif
