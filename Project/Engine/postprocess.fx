#ifndef _POSTPROCESS
#define _POSTPROCESS

#include "value.fx"

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
// GrayShader
// mesh : RectMesh
// Domain : DOMAIN_POSTPROCESS
// g_tex_0 : RederTarget Copy Texture
// ============================
VS_OUT VS_GrayShader(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;

    output.vPosition = float4(_in.vLocalPos * 2.f, 1.f);
    output.vUV = _in.vUV;

    return output;
}

float4 PS_GrayShader(VS_OUT _in) : SV_Target
{
    float4 vColor = g_tex_0.Sample(g_sam_0, _in.vUV);

    float vAver = (vColor.r + vColor.g + vColor.b) / 3.f;

    vColor = float4(vAver, vAver, vAver, 1.f);

    return vColor;
}


// ============================
// Distortion Shader
// mesh : RectMesh
// Domain : DOMAIN_POSTPROCESS
// g_tex_0 : RederTarget Copy Texture
// g_tex_1 : Noise Texture
// ============================
VS_OUT VS_Distortion(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;

    output.vPosition = mul(float4(_in.vLocalPos, 1.f), g_matWVP);
    output.vUV = _in.vUV;

    return output;
}

//float4 PS_Distortion(VS_OUT _in) : SV_Target
//{
//	float2 vUV = _in.vPosition.xy / g_Resolution;
//		
//	
//	float fChange = cos(( (vUV.x - g_AccTime * 0.05f) / 0.15f) * 2 * 3.1415926535f) * 0.05f;
//
//	vUV.y += fChange;
//
//	float4 vColor = g_tex_0.Sample(g_sam_0, vUV);
//	//vColor.r *= 2.f;
//
//	return vColor;
//}

float4 PS_Distortion(VS_OUT _in) : SV_Target
{
    float2 vUV = _in.vPosition.xy / g_Resolution;
	
	// Noise Texture 가 세팅이 되어 있다면
    if (g_btex_1)
    {
        float2 vNoiseUV = float2(_in.vUV.x - (g_AccTime * 0.2f), _in.vUV.y);
        float4 vNoise = g_tex_1.Sample(g_sam_0, vNoiseUV);

        vNoise = (vNoise - 0.5f) * 0.02f;

        vUV += vNoise.r;
    }

    float4 vColor = g_tex_0.Sample(g_sam_0, vUV);

    return vColor;
}




// ============================
// BlackHole Shader
// mesh : RectMesh
// Domain : DOMAIN_POSTPROCESS
// g_tex_0 : RederTarget Copy Texture
// g_tex_1 : Noise Texture
// g_vec2_0 : CenterPos
// g_float_0 : effectradius
// g_float_1 : effectangle
// ============================
VS_OUT VS_BlackHole(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.vPosition = mul(float4(_in.vLocalPos, 1.f), g_matWVP);
    output.vUV = _in.vUV;

    return output;
}


float4 PS_BlackHole(VS_OUT _in) : SV_Target
{
    float effectRadius = g_float_0;
    float effectAngle = g_float_1 * 3.141592;

    float2 center = float2(g_vec2_0.x, g_vec2_0.y) / float2(g_Resolution.x, g_Resolution.y);
    if (center.x == 0.0 && center.y == 0.0)
    {
        center = float2(0.5, 0.5);
    }

    
    float2 uv = _in.vPosition.xy / float2(g_Resolution.x, g_Resolution.y) - center;
    
    float len = length(uv * float2(g_Resolution.x / g_Resolution.y, 1.0));
    float angle = atan2(uv.y, uv.x) + effectAngle * smoothstep(effectRadius, 0.0, len);
    float radius = length(uv);

    float2 texCoords = float2(radius * cos(angle), radius * sin(angle)) + center;
    float4 texSample = g_tex_0.Sample(g_sam_0, texCoords);
    return texSample;
}






#endif