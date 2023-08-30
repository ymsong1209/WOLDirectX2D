#ifndef _FUNC
#define _FUNC

#include "value.fx"

//inout : 참조변수
//Normal Texture없을 경우
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
        //func.fx 파일의
        //void CalcLight2D(float3 _vWorldPos, inout tLightColor _Light)에 추가할것
        // CLight2D.cpp 의 finaltick맨 첫번째에 이 두문장 넣어주기
        //m_LightInfo.vWorldPos = Transform() - > GetWorldPos();
        //m_LightInfo.vWorldDir = Transform() - > GetWorldDir(DIR_TYPE::RIGHT);
        else if (g_Light2DBuffer[i].LightType == 2)
        {
            //광원의 x축으로 타원형 빛을 발사한다.
            float3 vLightDir = float3(g_Light2DBuffer[i].vWorldDir.xy, 0.f);
            //광원의 중심의 WorldPosition
            float3 vLightWorldPos = float3(g_Light2DBuffer[i].vWorldPos.xy, 0.f);
            //광원의 빛을 받는 물체의 Position
            float3 vWorldPos = float3(_vWorldPos.xy, 0.f);
            
           // 광원 중심에서 물체를 향하는 방향
            float3 vLight = normalize(vWorldPos - vLightWorldPos);
            
            
            if (acos(dot(vLight, vLightDir)) < g_Light2DBuffer[i].Angle/ 2.f)
            {
                float fDistance = abs(distance(vWorldPos, vLightWorldPos));
                //광원에서 멀리 있는 물체는 흐려지게 함
                float fPow = saturate(1.f - (fDistance / g_Light2DBuffer[i].Radius));
                //양옆으로 갈수록 흐려지게 함
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

//Normal Texture 존재할 경우
void CalcLight2D(float3 _vWorldPos, float3 _vWorldDir, inout tLightColor _Light)
{
    for (int i = 0; i < g_Light2DCount; ++i)
    {
        if (g_Light2DBuffer[i].LightType == 0)
        {
            //램버트 코사인 법칙
            float fDiffusePow = saturate(dot(-g_Light2DBuffer[i].vWorldDir.xyz, _vWorldDir));
            _Light.vDiffuse.rgb += g_Light2DBuffer[i].Color.vDiffuse.rgb * fDiffusePow;
            _Light.vAmbient.rgb += g_Light2DBuffer[i].Color.vAmbient.rgb;
        }
        else if (g_Light2DBuffer[i].LightType == 1)
        {
            float3 vLightWorldPos = float3(g_Light2DBuffer[i].vWorldPos.xy, 0.f);
            float3 vWorldPos = float3(_vWorldPos.xy, 0.f);

            // 광원 중심에서 물체를 향하는 방향
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
    
    // sin 그래프로 텍스쳐의 샘플링 위치 UV 를 계산
    vUV.y -= (sin((_NomalizedThreadID - (g_AccTime /*그래프 우측 이동 속도*/)) * 2.f * 3.1415926535f * 10.f /*반복주기*/) / 2.f);
    
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
            float2 vUV = g_vec2_0 + (g_vec2_3 * UVInput); //LeftTop좌상단으로 BackSize이동
            vUV -= ((g_vec2_3 - g_vec2_1) / 2.f); //Animation중앙으로 BackSize 이동
            vUV -= g_vec2_2; // Offset을 양수로 가기 위해선 뒷배경이 음수로 가야함
            
            
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
                //늘어난 background에 들어간 다른 애니메이션 파츠 제거
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
        // Normal 값 추출
        vNormal = g_tex_1.Sample(g_sam_0, UVInput);
        
        // 0 ~ 1 범위를 -1 ~ 1 로 변경
        vNormal = (vNormal * 2.f) - 1.f;
        
        // NormalTexture 좌표계는 y축과 z 축이 반대로 되어있다.
        float f = vNormal.y;
        vNormal.y = vNormal.z;
        vNormal.z = f;
        
        // Texture 에서 추출한 Normal 방향을 월드로 변환시킨다.
        vNormal = normalize(mul(float4(vNormal, 0.f), g_matWorld)).xyz;
    }
   
    return vOutLineColorLeft;
}

#endif