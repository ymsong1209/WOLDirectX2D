//#pragma once는 fx에서 안먹힘
#ifndef _VALUE
#define _VALUE

#include "struct.fx"

//buffer에는 16의 배수로 들어와야함.
cbuffer TRANSFORM : register(b0)
{
    //gpu는 matrix메모리를 읽을때 열 기준으로 읽는다. row_major를 붙혀서 행기준으로 하자.
    row_major matrix g_matWorld; //월드행렬
    row_major matrix g_matView; //월드에 있는 물체를 카메라에 옮긴다.
    row_major matrix g_matProj; //카메라에 있는 물체를 NDC좌표계에 맞게 투영
    
    row_major matrix g_matWV;
    row_major matrix g_matWVP;
};


cbuffer MATERIAL : register(b1)
{
    int g_int_0;
    int g_int_1;
    int g_int_2;
    int g_int_3;
    int g_int_4;
    int g_int_5;
    int g_int_6;
    int g_int_7;
    
    float g_float_0;
    float g_float_1;
    float g_float_2;
    float g_float_3;
    
    float2 g_vec2_0;
    float2 g_vec2_1;
    float2 g_vec2_2;
    float2 g_vec2_3;

    float4 g_vec4_0;
    float4 g_vec4_1;
    float4 g_vec4_2;
    float4 g_vec4_3;
    
    matrix g_mat_0;
    matrix g_mat_1;
    matrix g_mat_2;
    matrix g_mat_3;
    
    int g_btex_0;
    int g_btex_1;
    int g_btex_2;
    int g_btex_3;
    int g_btex_4;
    int g_btex_5;
    int g_btex_6;
    int g_btex_7;
};

cbuffer GLOBAL : register(b2)
{
    float2 g_Resolution;
    float g_DT;
    float g_AccTime; //프로그램이 켜진 후 흘러간 시간
    uint g_Light2DCount;
    uint g_Light3DCount;
    int2 g_globalpadding;
}


Texture2D g_tex_0 : register(t0);
Texture2D g_tex_1 : register(t1);
Texture2D g_tex_2 : register(t2);
Texture2D g_tex_3 : register(t3);
Texture2D g_tex_4 : register(t4);
Texture2D g_tex_5 : register(t5);
Texture2D g_tex_6 : register(t6);
Texture2D g_tex_7 : register(t7);

TextureCube g_cube_0 : register(t8);
TextureCube g_cube_1 : register(t9);

Texture2DArray g_arrtex_0 : register(t10);
Texture2DArray g_arrtex_1 : register(t11);

StructuredBuffer<tLightInfo> g_Light2DBuffer : register(t12);
StructuredBuffer<tLightInfo> g_Light3DBuffer : register(t13);

SamplerState g_sam_0 : register(s0); //이방성 필터링
SamplerState g_sam_1 : register(s1); //샘플 그대로 가져옴


#endif