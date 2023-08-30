#pragma once
#include "CComponent.h"
#include "CMesh.h"
#include "CMaterial.h"
#include "ptr.h"

class CRenderComponent :
    public CComponent
{
private:
    //CMesh* m_pMesh => Ptr<CMesh>  m_pMesh�� ������ ���̴�. �̶� template�̱� ������ ���漱���� �ƴ� include�� �������
    Ptr<CMesh>              m_pMesh;
    //obj�� material�� ������ ���̰�, material�� shader�� �����Ѵ�.

    Ptr<CMaterial>          m_pSharedMtrl;  // ���� ���׸���
    Ptr<CMaterial>          m_pDynamicMtrl; // SharedMaterial ���纻
    Ptr<CMaterial>          m_pCurrentMtrl; // ���� ��� ���� ����

public:
    virtual void render() = 0;


public:
    void SetMesh(Ptr<CMesh> _Mesh) { m_pMesh = _Mesh; }
    void SetMaterial(Ptr<CMaterial> _Mtrl);

    Ptr<CMesh> GetMesh() { return m_pMesh; }
    Ptr<CMaterial> GetMaterial() { return m_pCurrentMtrl; }
    Ptr<CMaterial> GetSharedMaterial() { return m_pSharedMtrl; }
    Ptr<CMaterial> GetDynamicMaterial();

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

public:
    CRenderComponent(COMPONENT_TYPE _type);
    //ptr�� ���ҽ��������̹Ƿ� �Ѱ��� �����ؾ��ϴϱ� ��������ڸ� �ȸ����.
    //GameObject�� ���������->ptr�� ���������->addref()
    ~CRenderComponent();
};
