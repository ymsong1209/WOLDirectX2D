#include "pch.h"
#include "CAnimator2D.h"

#include "CAnim2D.h"
#include "CMeshRender.h"
#include "CParticleSystem.h"

#include "ptr.h"
#include "CMaterial.h"


CAnimator2D::CAnimator2D()
	: CComponent(COMPONENT_TYPE::ANIMATOR2D)
	, m_pCurAnim(nullptr)
	, m_bRepeat(false)
	
{
}

CAnimator2D::CAnimator2D(const CAnimator2D& _other)
	: CComponent(_other)
	, m_bRepeat(_other.m_bRepeat)
	, m_iSampleState(_other.m_iSampleState)
{

	for (const auto& pair : _other.m_mapAnim)
	{
		CAnim2D* Animation = new CAnim2D(*pair.second);

		m_mapAnim.insert(make_pair(Animation->GetName(), Animation));
	}

	if (_other.m_pCurAnim) {
		map<wstring, CAnim2D*>::iterator iter = m_mapAnim.find(_other.m_pCurAnim->GetName());
		m_pCurAnim = iter->second;
	}
	

}

CAnimator2D::~CAnimator2D()
{
	Safe_Del_Map(m_mapAnim);
}

void CAnimator2D::finaltick()
{
	if (nullptr != m_pCurAnim)
	{
		if (m_bRepeat && m_pCurAnim->IsFinish())
		{
			m_pCurAnim->Reset();
		}

		m_pCurAnim->finaltick();
	}
}

void CAnimator2D::UpdateData()
{
	Ptr<CMaterial> pMtrl = MeshRender()->GetMaterial();

	if (m_pCurAnim) {
		const tAnim2DFrm& frm = m_pCurAnim->GetCurFrame();
		Vec2 vBackSize = m_pCurAnim->GetBackSize();

		int SampleState = GetSamplerState();
		int iAnimUse = 1;
		pMtrl->SetScalarParam(INT_0,  &iAnimUse);
		pMtrl->SetScalarParam(VEC2_0, &frm.LeftTopUV);
		pMtrl->SetScalarParam(VEC2_1, &frm.SliceUV);
		pMtrl->SetScalarParam(VEC2_2, &frm.Offset);
		pMtrl->SetScalarParam(VEC2_3, &vBackSize);
		pMtrl->SetScalarParam(INT_7,  &SampleState);

		pMtrl->SetTexParam(TEX_0, m_pCurAnim->GetAtlasTex());
	}
	
}

void CAnimator2D::Clear()
{
	Ptr<CMaterial> pMtrl = MeshRender()->GetMaterial();
	

	int iAnimUse = 0;
	pMtrl->SetScalarParam(INT_0, &iAnimUse);

	Ptr<CTexture> pTex = nullptr;
	pMtrl->SetTexParam(TEX_0, pTex);

	int SampleState = 0;
	pMtrl->SetScalarParam(INT_7, &SampleState);

}


void CAnimator2D::Play(const wstring& _strName, bool _bRepeat)
{
	CAnim2D* pAnim = FindAnim(_strName);
	assert(pAnim);

	m_pCurAnim = pAnim;
	m_bRepeat = _bRepeat;
}

void CAnimator2D::Pause()
{
	assert(m_pCurAnim);
	m_pCurAnim->Pause();
}

void CAnimator2D::Reset()
{
	assert(m_pCurAnim);
	m_pCurAnim->Reset();
}

CAnim2D* CAnimator2D::FindAnim(const wstring& _strName)
{
	map<wstring, CAnim2D*>::iterator iter = m_mapAnim.find(_strName);

	if (iter == m_mapAnim.end())
	{
		return nullptr;
	}

	return iter->second;
}

CAnim2D* CAnimator2D::LoadAnim(const wstring& _strRelativePath)
{
	//Find Animation Name from Filepath
	size_t pos = _strRelativePath.find_last_of(L"\\");
	wstring filename = (pos == std::wstring::npos) ? _strRelativePath : _strRelativePath.substr(pos + 1);
	size_t dot_pos = filename.find_last_of(L".");
	wstring filename_without_extension = (dot_pos == wstring::npos) ? filename : filename.substr(0, dot_pos);
	//현재 Map에 애니메이션 있으면 return
	CAnim2D* pAnim = FindAnim(filename_without_extension);
	if (pAnim == nullptr) {
		pAnim = new CAnim2D;
	}
	else
	{
		return nullptr;
	}

	pAnim->Load(_strRelativePath);

	m_mapAnim.insert(make_pair(pAnim->GetName(), pAnim));
	pAnim->m_pOwner = this;

	return pAnim;
}

void CAnimator2D::CreateAnimation(const wstring& _strAnimName
	, Ptr<CTexture> _AtlasTex, Vec2 _vLeftTop, Vec2 _vSlice, Vec2 _vBackSize
	, int _FrameCount, int _FPS)
{
	CAnim2D* pAnim = new CAnim2D;
	pAnim->Create(_strAnimName, _AtlasTex, _vLeftTop, _vSlice, _vBackSize, _FrameCount, _FPS);

	pAnim->m_pOwner = this;
	m_mapAnim.insert(make_pair(_strAnimName, pAnim));
}


void CAnimator2D::SaveToLevelFile(FILE* _File)
{

	fwrite(&m_bRepeat, sizeof(bool), 1, _File);

	fwrite(&m_iSampleState, sizeof(int), 1, _File);

	size_t AnimCount = m_mapAnim.size();
	fwrite(&AnimCount, sizeof(size_t), 1, _File);

	for (const auto& pair : m_mapAnim)
	{
		wstring path = pair.second->GetAnimRelativePath();
		SaveWString(path, _File);
	}

	wstring strCurAnimName;
	if (nullptr != m_pCurAnim)
	{
		strCurAnimName = m_pCurAnim->GetName();
	}
	SaveWString(strCurAnimName, _File);
}

void CAnimator2D::LoadFromLevelFile(FILE* _File)
{
	fread(&m_bRepeat, sizeof(bool), 1, _File);

	fread(&m_iSampleState, sizeof(int), 1, _File);

	size_t AnimCount = 0;
	fread(&AnimCount, sizeof(size_t), 1, _File);

	for (size_t i = 0; i < AnimCount; ++i)
	{
		CAnim2D* pNewAnim = new CAnim2D;

		wstring AnimPath;
		LoadWString(AnimPath, _File);
		pNewAnim->Load(AnimPath);

		m_mapAnim.insert(make_pair(pNewAnim->GetName(), pNewAnim));
		pNewAnim->m_pOwner = this;
	}

	wstring strCurAnimName;
	LoadWString(strCurAnimName, _File);

	m_pCurAnim = FindAnim(strCurAnimName);
}
