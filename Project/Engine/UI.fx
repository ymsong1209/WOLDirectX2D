#ifndef _UI2D
#define _UI2D

#include "value.fx"
#include "func.fx"

struct VS_IN
{
    float3 vLocalPos : POSITION;
    float2 vUV : TEXCOORD;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
};

// ============================
// UIShader
// RasterizerState      : None
// BlendState           : Mask
// DepthStencilState    : Less
//
// Parameter
// g_int_0              : AnimUse
// g_int_7              : SampleState
// g_vec2_0             : AnimAtlas LeftTop
// g_vec2_1             : AnimAtlas Slice
//

// g_tex_0              : Output Texture

// ============================
VS_OUT VS_UI2D(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.vPosition = mul(float4(_in.vLocalPos, 1.f), g_matWVP);
    output.vUV = _in.vUV;
        
    return output;
}


float4 PS_UI2D(VS_OUT _in) : SV_Target
{
    float4 vOutColor = (float4) 0.f;
            
        
    if (g_btex_0)
    {
        vOutColor = g_tex_0.Sample(g_sam_0, _in.vUV);
        //if (g_int_7 == 0)
        //{
        //    vOutColor = g_tex_0.Sample(g_sam_0, _in.vUV);
        //}
        //else
        //{
        //    vOutColor = g_tex_0.Sample(g_sam_1, _in.vUV);
        //}
       
    }
    else
    {
        //vOutColor = float4(1.f, 0.f, 1.f, 1.f);
    }
    
    if (0.f == vOutColor.a)
        discard;
 
    
    return vOutColor;
}
#endif