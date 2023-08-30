#ifndef _TEST
#define _TEST
#include "value.fx"


// VS �Է� ����ü
struct VS_IN {
	//Vec3�� ������
	float3 vPos : POSITION; //semantic/ ��������ü�ȿ��� ���� ���ϴ°� ¤�� layout����ü(Ű����������)
	float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
};
struct VS_OUT
{
	float4 vPosition : SV_Position;//SV : system value, �䷱�� ����Ű�°� Ư���ϰ� �۵���.
    float4 vOutColor : COLOR;
    float2 vOutUV : TEXCOORD;
};

//vertex shader
// LocalSpace ��ü�� NDC ��ǥ��� �̵�
VS_OUT VS_Test(VS_IN _in)
{ 
	//�������ڸ��� 0�� �ʱ�ȭ�ϴ°� ��ȯ
    VS_OUT output = (VS_OUT) 0.f;
        
    //��������� ���� ����� �������� �߰��Ѵ�.
    float4 vWorldPos = mul(float4(_in.vPos, 1.f), g_matWorld);
    float4 vViewPos = mul(vWorldPos, g_matView);
    float4 vProjPos = mul(vViewPos, g_matProj);
    //��������� ���ص� �������� z�� ����������Ѵ�. �̰��� rasterizer���� �ڵ����� ����.
       
    output.vPosition = vProjPos;
    output.vOutColor = _in.vColor;
    output.vOutUV = _in.vUV;
    
    return output;
}

//pixel shader

//vertex shader���� return��Ų���� pixel shader�� input���� ��
//Sv_target : ����̽����� Omsetrendertarget�� m_srv, ����Ÿ�ٿ��� ���� ����
float4 PS_Test(VS_OUT _in) : SV_Target
{
    float4 vColor = (float4) 0.f;
    
  
    //Sampling�� �ϸ� Texture ������ UV ��ġ ������ ���� ������ �ȼ��� ������ ���� �ִ�.
    if (g_int_0 == 0)
        vColor = g_tex_0.Sample(g_sam_0, _in.vOutUV);
    else if (g_int_0 == 1)
        vColor = g_tex_0.Sample(g_sam_1, _in.vOutUV);
    
    //vColor = float4(1.f, 1.f, 1.f, 0.f);
    
    return vColor;
}


//�ι�° ���
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