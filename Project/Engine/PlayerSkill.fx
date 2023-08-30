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
    
    
    
    // Skill Percentage Check
    
    float2 vYPos = float2(0.5f, 0.f);
    float2 vCenterUV = float2(0.5, 0.5);
        //���� �˻��ؾ��ϴ� ��ü�� UV
    float2 vCurUV = _in.vUV;
        // �̹����� �߽ɿ��� ��ü�� ���ϴ� ����
    float2 vDir = normalize(vCurUV - vCenterUV);
    float2 vYDir = normalize(vYPos - vCenterUV);
    float angle = 360.f * g_float_0;
    
    if (g_float_0 != 1.f)
    {
        if (acos(dot(vDir, vYDir)) < radians(angle))
        {
          //acos�� 0~180���� ��ȯ��. ����ó���� �ʿ���.
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
    

    
    
    
    return vOutColor;
}

#endif