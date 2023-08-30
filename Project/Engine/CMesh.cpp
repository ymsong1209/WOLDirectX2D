#include "pch.h"
#include "CMesh.h"
#include "CDevice.h"


CMesh::CMesh(bool _bEngine)
	: CRes(RES_TYPE::MESH, _bEngine)
	, m_tVBDesc{}
	, m_VtxCount(0)
	, m_tIBDesc{}
	, m_IdxCount(0)
	, m_pVtxSys(nullptr)
	, m_pIdxSys(nullptr)
{
}

CMesh::~CMesh()
{
	if (nullptr != m_pVtxSys)
		delete m_pVtxSys;

	if (nullptr != m_pIdxSys)
		delete m_pIdxSys;
}


void CMesh::Create(void* _VtxSysMem, UINT _iVtxCount, void* _IdxSysMem, UINT _IdxCount)
{
	m_VtxCount = _iVtxCount;
	m_IdxCount = _IdxCount;

	// SystemMem 데이터 복사
	m_pVtxSys = new Vtx[m_VtxCount];
	memcpy(m_pVtxSys, _VtxSysMem, sizeof(Vtx) * m_VtxCount);

	m_pIdxSys = new UINT[m_IdxCount];
	memcpy(m_pIdxSys, _IdxSysMem, sizeof(UINT) * m_IdxCount);


	// Vertex 버퍼 생성
	m_tVBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER; //버퍼의 용도, 정해진 용도에 따라 전달이 될수도 있고 안될수도 있다.
	m_tVBDesc.CPUAccessFlags = 0;
	m_tVBDesc.Usage = D3D11_USAGE_DEFAULT; //정점버퍼는 이동하지 않는다.
	m_tVBDesc.ByteWidth = sizeof(Vtx) * m_VtxCount;//버퍼의 크기,direct에서는 패딩바이트를 없애준다.

	D3D11_SUBRESOURCE_DATA tSub = {};
	tSub.pSysMem = _VtxSysMem;
	if (FAILED(DEVICE->CreateBuffer(&m_tVBDesc, &tSub, m_VB.GetAddressOf())))
	{
		assert(nullptr);
	}

	// Index 버퍼 생성
	m_tIBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
	m_tIBDesc.CPUAccessFlags = 0;
	m_tIBDesc.Usage = D3D11_USAGE_DEFAULT;
	m_tIBDesc.ByteWidth = sizeof(UINT) * m_IdxCount;

	tSub.pSysMem = _IdxSysMem;
	if (FAILED(DEVICE->CreateBuffer(&m_tIBDesc, &tSub, m_IB.GetAddressOf())))
	{
		assert(nullptr);
	}
}

void CMesh::UpdateData()
{
	//stride : 정점 하나의 간격, 원본 크기
	UINT iStride = sizeof(Vtx);
	//offset 버퍼 내에서 시작 위치, 근데 그럴 필요 없음, 버텍스 버퍼가 1개이기 때문
	UINT iOffset = 0;

	CONTEXT->IASetVertexBuffers(0, 1, m_VB.GetAddressOf(), &iStride, &iOffset);
	CONTEXT->IASetIndexBuffer(m_IB.Get(), DXGI_FORMAT_R32_UINT, 0); //DXGI_FORMAT_R32_UINT:4byte
}

void CMesh::render()
{
	UpdateData();

	CONTEXT->DrawIndexed(m_IdxCount, 0, 0);
}

void CMesh::render_particle(UINT _iParticleCount)
{
	UpdateData();

	// 인스턴싱
	CONTEXT->DrawIndexedInstanced(m_IdxCount, _iParticleCount, 0, 0, 0);
}
