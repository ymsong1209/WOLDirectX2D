#pragma once
#include "CComponent.h"
#include "CMesh.h"
#include "CMaterial.h"
#include "ptr.h"

class CRenderComponent :
    public CComponent
{
private:
    //CMesh* m_pMesh => Ptr<CMesh>  m_pMesh로 관리할 것이다. 이때 template이기 때문에 전방선언이 아닌 include를 해줘야함
    Ptr<CMesh>              m_pMesh;
    //obj는 material을 참조할 것이고, material이 shader를 참조한다.

    Ptr<CMaterial>          m_pSharedMtrl;  // 원본 메테리얼
    Ptr<CMaterial>          m_pDynamicMtrl; // SharedMaterial 복사본
    Ptr<CMaterial>          m_pCurrentMtrl; // 현재 사용 중인 재질

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
    //ptr는 리소스포인터이므로 한개만 존재해야하니깐 복사생성자를 안만든다.
    //GameObject의 복사생성자->ptr의 복사생성자->addref()
    ~CRenderComponent();
};

