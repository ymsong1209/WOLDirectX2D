#pragma once
#include "CEntity.h"

class CStructuredBuffer :
    public CEntity
{
private:
    ComPtr<ID3D11Buffer>                m_SB; //register binding ; main buffer

    //view는 gpu에서 셰이더로 데이터를 전달하기 위해 필요하다.
    ComPtr<ID3D11ShaderResourceView>    m_SRV; //구조화버퍼는 텍스쳐취급을 하기 때문에 texture처럼 view가 필요하다.
    ComPtr<ID3D11UnorderedAccessView>   m_UAV;

    ComPtr<ID3D11Buffer>                m_SB_CPU_Read;  // GPU -> Sys
    ComPtr<ID3D11Buffer>                m_SB_CPU_Write; // Sys -> GPU

    D3D11_BUFFER_DESC                   m_tDesc;

    UINT                                m_iElementSize;
    UINT                                m_iElementCount;

    SB_TYPE                             m_Type;
    bool                                m_bSysAccess;

    UINT                                m_iRecentRegisterNum;



public:
    void Create(UINT _iElementSize, UINT _iElementCount, SB_TYPE _Type, bool _bUseSysAccess, void* _pSysMem = nullptr);
    void SetData(void* _pSrc, UINT _iSize = 0);
    void GetData(void* _pDst);

    void Clear();
    void Clear_CS(bool _IsShaderRes);

    // PIPELINE_STAGE
    void UpdateData(UINT _iRegisterNum, UINT _iPipeLineStage);
    void UpdateData_CS(UINT _iRegisterNum, bool _IsShaderRes);

    UINT GetElementSize() { return m_iElementSize; }
    UINT GetElementCount() { return m_iElementCount; }
    UINT GetBufferSize() { return m_iElementSize * m_iElementCount; }

    const SB_TYPE& GetSBType() { return m_Type; }
    const bool& GetSysSAccess() { return m_bSysAccess; }



    CLONE_DISABLE(CStructuredBuffer);

public:
    CStructuredBuffer();
    ~CStructuredBuffer();
};
