#ifndef _TEST
#define _TEST
#include "value.fx"


// VS 입력 구조체
struct VS_IN {
	//Vec3와 유사함
	float3 vPos : POSITION; //semantic/ 정점구조체안에서 내가 원하는걸 짚는 layout정보체(키값같은거임)
	float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
};
struct VS_OUT
{
	float4 vPosition : SV_Position;//SV : system value, 요런게 가리키는건 특수하게 작동함.
    float4 vOutColor : COLOR;
    float2 vOutUV : TEXCOORD;
};

//vertex shader
// LocalSpace 물체를 NDC 좌표계로 이동
VS_OUT VS_Test(VS_IN _in)
{ 
	//선언하자마자 0로 초기화하는걸 반환
    VS_OUT output = (VS_OUT) 0.f;
        
    //상수버퍼의 값을 행렬의 곱셈으로 추가한다.
    float4 vWorldPos = mul(float4(_in.vPos, 1.f), g_matWorld);
    float4 vViewPos = mul(vWorldPos, g_matView);
    float4 vProjPos = mul(vViewPos, g_matProj);
    //투영행렬을 곱해도 마지막에 z로 나누어줘야한다. 이것은 rasterizer에서 자동으로 해줌.
       
    output.vPosition = vProjPos;
    output.vOutColor = _in.vColor;
    output.vOutUV = _in.vUV;
    
    return output;
}

//pixel shader

//vertex shader에서 return시킨값이 pixel shader의 input으로 들어감
//Sv_target : 디바이스에서 Omsetrendertarget의 m_srv, 렌더타겟에서 찍힐 색상
float4 PS_Test(VS_OUT _in) : SV_Target
{
    float4 vColor = (float4) 0.f;
    
  
    //Sampling을 하면 Texture 내에서 UV 위치 지점이 색을 가져와 픽셀에 세팅할 수가 있다.
    if (g_int_0 == 0)
        vColor = g_tex_0.Sample(g_sam_0, _in.vOutUV);
    else if (g_int_0 == 1)
        vColor = g_tex_0.Sample(g_sam_1, _in.vOutUV);
    
    //vColor = float4(1.f, 1.f, 1.f, 0.f);
    
    return vColor;
}


//두번째 방법
//struct PS_OUT
//{
//	float vColor : SV_Target;
//};

//PS_OUT PS_Test(VS_OUT _in)
//{
//	PS_OUT output = (PS_OUT)0.f;
//	output.vColor = float4(1.f, 0.f, 0.f, 1.f);
//	return output;
//}



// ===============
// SetColor Shader
// mesh : RectMesh
// ===============
VS_OUT VS_SetColor(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.vPosition = float4(_in.vPos.xy * 2.f, 0.5f, 1.f);
    output.vOutUV = _in.vUV;
    
    return output;
}

float4 PS_SetColor(VS_OUT _in) : SV_Target
{
    float4 vColor = (float4) 0.f;
    
    float fDist = abs(distance(_in.vOutUV, float2(0.5f, 0.5f)));
    
    if (0.5f < fDist)
        discard;
    
    vColor = float4(0.f, 1.f, 0.f, 1.f);
    
    return vColor;
}

#endif