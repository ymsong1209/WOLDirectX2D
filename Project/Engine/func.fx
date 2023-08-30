#ifndef _FUNC
#define _FUNC

#include "value.fx"

//inout : ��������
//Normal Texture���� ���
void CalcLight2D(float3 _vWorldPos, inout tLightColor _Light)
{
    for (int i = 0; i < g_Light2DCount; ++i)
    {
        
        //Directional Light
        if (g_Light2DBuffer[i].LightType == 0)
        {
            _Light.vDiffuse.rgb += g_Light2DBuffer[i].Color.vDiffuse.rgb;
            _Light.vAmbient.rgb += g_Light2DBuffer[i].Color.vAmbient.rgb;
            
        }
        //Point Light
        else if (g_Light2DBuffer[i].LightType == 1)
        {
            float3 vLightWorldPos = float3(g_Light2DBuffer[i].vWorldPos.xy, 0.f);
            float3 vWorldPos = float3(_vWorldPos.xy, 0.f);

            float fDistance = abs(distance(vWorldPos, vLightWorldPos));
            float fPow = saturate(1.f - (fDistance / g_Light2DBuffer[i].Radius));
        
            _Light.vDiffuse.rgb += g_Light2DBuffer[i].Color.vDiffuse.rgb * fPow;
        }
        //func.fx ������
        //void CalcLight2D(float3 _vWorldPos, inout tLightColor _Light)�� �߰��Ұ�
        // CLight2D.cpp �� finaltick�� ù��°�� �� �ι��� �־��ֱ�
        //m_LightInfo.vWorldPos = Transform() - > GetWorldPos();
        //m_LightInfo.vWorldDir = Transform() - > GetWorldDir(DIR_TYPE::RIGHT);
        else if (g_Light2DBuffer[i].LightType == 2)
        {
            //������ x������ Ÿ���� ���� �߻��Ѵ�.
            float3 vLightDir = float3(g_Light2DBuffer[i].vWorldDir.xy, 0.f);
            //������ �߽��� WorldPosition
            float3 vLightWorldPos = float3(g_Light2DBuffer[i].vWorldPos.xy, 0.f);
            //������ ���� �޴� ��ü�� Position
            float3 vWorldPos = float3(_vWorldPos.xy, 0.f);
            
           // ���� �߽ɿ��� ��ü�� ���ϴ� ����
            float3 vLight = normalize(vWorldPos - vLightWorldPos);
            
            
            if (acos(dot(vLight, vLightDir)) < g_Light2DBuffer[i].Angle/ 2.f)
            {
                float fDistance = abs(distance(vWorldPos, vLightWorldPos));
                //�������� �ָ� �ִ� ��ü�� ������� ��
                float fPow = saturate(1.f - (fDistance / g_Light2DBuffer[i].Radius));
                //�翷���� ������ ������� ��
                float fAnglePow = saturate(1.f - acos(dot(vLight, vLightDir)) / (g_Light2DBuffer[i].Angle / 2.f));
        
                _Light.vDiffuse.rgb += g_Light2DBuffer[i].Color.vDiffuse.rgb * fPow*fAnglePow;
            }
            else
            {
                _Light.vDiffuse.rgb = float3(0.f, 0.f, 0.f);
            }
        }
        
        
        
    }
}

//Normal Texture ������ ���
void CalcLight2D(float3 _vWorldPos, float3 _vWorldDir, inout tLightColor _Light)
{
    for (int i = 0; i < g_Light2DCount; ++i)
    {
        if (g_Light2DBuffer[i].LightType == 0)
        {
            //����Ʈ �ڻ��� ��Ģ
            float fDiffusePow = saturate(dot(-g_Light2DBuffer[i].vWorldDir.xyz, _vWorldDir));
            _Light.vDiffuse.rgb += g_Light2DBuffer[i].Color.vDiffuse.rgb * fDiffusePow;
            _Light.vAmbient.rgb += g_Light2DBuffer[i].Color.vAmbient.rgb;
        }
        else if (g_Light2DBuffer[i].LightType == 1)
        {
            float3 vLightWorldPos = float3(g_Light2DBuffer[i].vWorldPos.xy, 0.f);
            float3 vWorldPos = float3(_vWorldPos.xy, 0.f);

            // ���� �߽ɿ��� ��ü�� ���ϴ� ����
            float3 vLight = normalize(vWorldPos - vLightWorldPos);
            float fDiffusePow = saturate(dot(-vLight, _vWorldDir));
            
            float fDistance = abs(distance(vWorldPos, vLightWorldPos));
            float fDistPow = saturate(1.f - (fDistance / g_Light2DBuffer[i].Radius));
        
            _Light.vDiffuse.rgb += g_Light2DBuffer[i].Color.vDiffuse.rgb * fDiffusePow * fDistPow;
        }
        else if (g_Light2DBuffer[i].LightType == 2)
        {
            
        }
    }
}

float3 CalcPortal(float3 _vWorldPos, float4 _vPortalPos, float4 _vGameObjectPos, float _fPortalMaxRadius, float _fPortalRange)
{
    
    float3 Vertex2Hole = (_vPortalPos.x - _vWorldPos.x, _vPortalPos.y - _vWorldPos.y, _vPortalPos.z - _vWorldPos.z);
    float HoleRadius = lerp(0.f, _fPortalMaxRadius, _fPortalRange/_fPortalMaxRadius);
    float3 hole2Object = (_vPortalPos.x - _vGameObjectPos.x, _vPortalPos.y - _vGameObjectPos.y, _vPortalPos.z - _vGameObjectPos.z);
    float Hole2ObjectLength = length(hole2Object);
    float result = lerp(float3(0.f, 0.f, 0.f), Vertex2Hole, clamp(HoleRadius - Hole2ObjectLength, 0.f, 1.f));
  
    return result;
}

static float GaussianFilter[5][5] =
{
    0.003f, 0.0133f, 0.0219f, 0.0133f, 0.003f,
    0.0133f, 0.0596f, 0.0983f, 0.0596f, 0.0133f,
    0.0219f, 0.0983f, 0.1621f, 0.0983f, 0.0219f,
    0.0133f, 0.0596f, 0.0983f, 0.0596f, 0.0133f,
    0.003f, 0.0133f, 0.0219f, 0.0133f, 0.003f,
};


void GaussianSample(in Texture2D _NoiseTex, float2 _vResolution, float _NomalizedThreadID, out float3 _vOut)
{
    float2 vUV = float2(_NomalizedThreadID, 0.5f);
    
    vUV.x += g_AccTime * 0.5f;
    
    // sin �׷����� �ؽ����� ���ø� ��ġ UV �� ���
    vUV.y -= (sin((_NomalizedThreadID - (g_AccTime /*�׷��� ���� �̵� �ӵ�*/)) * 2.f * 3.1415926535f * 10.f /*�ݺ��ֱ�*/) / 2.f);
    
    if (1.f < vUV.x)
        vUV.x = frac(vUV.x);
    else if (vUV.x < 0.f)
        vUV.x = 1.f + frac(vUV.x);
    
    if (1.f < vUV.y)
        vUV.y = frac(vUV.y);
    else if (vUV.y < 0.f)
        vUV.y = 1.f + frac(vUV.y);
        
    int2 pixel = vUV * _vResolution;
    int2 offset = int2(-2, -2);
    float3 vOut = (float3) 0.f;
    
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            vOut += _NoiseTex[pixel + offset + int2(j, i)] * GaussianFilter[i][j];
        }
    }
    
    _vOut = vOut;
}


float4 Outline(float3 vWorldPos, float2 UVInput)
{
    float4 vOutLineColorLeft = (float4) 0.f;
    if (g_btex_0)
    {
        if (g_int_0)
        {
            float2 vUV = g_vec2_0 + (g_vec2_3 * UVInput); //LeftTop�»������ BackSize�̵�
            vUV -= ((g_vec2_3 - g_vec2_1) / 2.f); //Animation�߾����� BackSize �̵�
            vUV -= g_vec2_2; // Offset�� ����� ���� ���ؼ� �޹���� ������ ������
            
            
            if (g_vec2_0.x < vUV.x && vUV.x < g_vec2_0.x + g_vec2_1.x
                && g_vec2_0.y < vUV.y && vUV.y < g_vec2_0.y + g_vec2_1.y)
            {
                              
                if (g_int_7 == 0)
                {
                    vOutLineColorLeft = g_tex_0.Sample(g_sam_0, vUV);
                }
                else
                {
                    vOutLineColorLeft = g_tex_0.Sample(g_sam_1, vUV);
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
                vOutLineColorLeft = g_tex_0.Sample(g_sam_0, UVInput);
            }
            else
            {
                vOutLineColorLeft = g_tex_0.Sample(g_sam_1, UVInput);
            }
        }
    }
    else
    {
        vOutLineColorLeft = float4(1.f, 0.f, 1.f, 1.f);
    }
        
    float3 vNormal = (float3) 0.f;
    if (g_btex_1)
    {
        // Normal �� ����
        vNormal = g_tex_1.Sample(g_sam_0, UVInput);
        
        // 0 ~ 1 ������ -1 ~ 1 �� ����
        vNormal = (vNormal * 2.f) - 1.f;
        
        // NormalTexture ��ǥ��� y��� z ���� �ݴ�� �Ǿ��ִ�.
        float f = vNormal.y;
        vNormal.y = vNormal.z;
        vNormal.z = f;
        
        // Texture ���� ������ Normal ������ ����� ��ȯ��Ų��.
        vNormal = normalize(mul(float4(vNormal, 0.f), g_matWorld)).xyz;
    }
   
    return vOutLineColorLeft;
}

#endif