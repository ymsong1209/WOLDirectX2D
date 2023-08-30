#ifndef _SETCOLOR
#define _SETCOLOR

#include "value.fx"

RWTexture2D<float4> g_Output : register(u0);
#define Color       g_vec4_0 

// ComputeShader �Է� Sematic
// SV_GroupThreadID      : �׷� �������� �ε���(3����)
// SV_GroupID            : �׷� �ε���
// SV_GroupIndex         : �׷� �������� �ε���(1����)
// SV_DispatchThreadID   : ��ü �׷� ����, �������� �ε���(3����)
[numthreads(32, 32, 1)]
// ������ �׷� ����(HLSL 5.0 ���� 1024 ����)

void CS_SetColor(int3 _ID : SV_DispatchThreadID)
{
  
    g_Output[_ID.xy] = float4(Color.xyz, 1.f);
}

#endif