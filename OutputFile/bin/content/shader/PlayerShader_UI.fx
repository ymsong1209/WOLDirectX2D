#ifndef _PLAYERSHADERUI
#define _PLAYERSHADERUI

#include "value.fx"
#include "func.fx"


// ======================================
// PlayerShader_UI
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
// g_float_0            : Dissolve Range
// g_float_1            : Dissolve Thickness


// g_tex_0              : Output Texture
// g_tex_1              : Nomal Texture

// g_tex_7              : SimpleNoise Texture

// g_vec4_0             : Dissolve Color
// g_vec4_1             : CapeColor
// ======================================

struct VS_Player_IN
{
    float3 vLocalPos : POSITION;
    float2 vUV : TEXCOORD;
};

struct VS_Player_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
    float3 vWorldPos : POSITION;
};



VS_Player_OUT VS_Player(VS_Player_IN _in)
{
    VS_Player_OUT output = (VS_Player_OUT) 0.f;
    
    output.vPosition = mul(float4(_in.vLocalPos, 1.f), g_matWVP);
    output.vUV = _in.vUV;
    output.vWorldPos = mul(float4(_in.vLocalPos, 1.f), g_matWorld).xyz;
    
        
    return output;
}


float4 PS_Player(VS_Player_OUT _in) : SV_Target
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
        vOutColor = float4(1.f, 0.f, 1.f, 1.f);
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
        if (0.f < vOutColor.r && vOutColor.r <= (10.f / 255.0f))
        {
            
        }
        else
        {
            vOutColor.r *= g_vec4_1.r;
            vOutColor.g *= g_vec4_1.g;
            vOutColor.b *= g_vec4_1.b;
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
    

    
    // Dissolve ó��
    if (g_int_1)
    {
        float4 vNoiseColor = (float4) 0.f;
        
   
        
        vNoiseColor = g_tex_7.Sample(g_sam_0, _in.vUV);
        if (vNoiseColor.r < g_float_0 + g_float_1)
        {
            vOutColor.rgb = g_vec4_0.xyz;
        }
        if (vNoiseColor.r < g_float_0)
            discard;
    }
   
    
    
    return vOutColor;
}

#endif