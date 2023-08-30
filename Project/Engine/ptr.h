#pragma once

template<typename T>
class Ptr
{
private:
	T* m_Res;


public:
	T* Get() const { return m_Res; }

	T* operator -> () const
	{
		return m_Res;
	}

	//������ ���� ������ �־��µ� �ٸ� ���� ���� ���
	void operator = (T* _Res)
	{
		//������ ������ �ִ��ſ� release�ؾ���.
		if (nullptr != m_Res)
			m_Res->Release();

		m_Res = _Res;

		if (nullptr != m_Res)
			m_Res->AddRef();
	}

	//����Ʈ�����Ͱ� �Է����� ���� ���
	void operator = (const Ptr<T>& _Res)
	{
		if (nullptr != m_Res)
			m_Res->Release();

		m_Res = _Res.m_Res;

		if (nullptr != m_Res)
			m_Res->AddRef();
	}

	//����������
	bool operator == (T* _Other)
	{
		return m_Res == _Other;
	}

	bool operator != (T* _Other)
	{
		return m_Res != _Other;
	}

	bool operator == (const Ptr<T>& _Other)
	{
		return m_Res == _Other.m_Res;
	}

	bool operator != (const Ptr<T>& _Other)
	{
		return m_Res != _Other.m_Res;
	}

public:
	Ptr()
		: m_Res(nullptr)
	{

	}

	Ptr(T* _Res)
		: m_Res(_Res)
	{
		if (nullptr != m_Res)
			m_Res->AddRef();
	}

	Ptr(const Ptr<T>& _Res)
		: m_Res(_Res.m_Res)
	{
		if (nullptr != m_Res)
			m_Res->AddRef();
	}

	~Ptr()
	{
		if (nullptr != m_Res)
		{
			m_Res->Release();
		}
	}
};

//Ptr�� Ŭ�����̱� ������ ������ �����ε����� ���������ڸ� ���� ���� ����.
//�̷��� �����Լ��� �������Ѵ�.
//���ڷ� void* _Res��� T* res�� ������ nullptr�� �νĸ��Ѵ�.
template<typename T>
bool operator == (void* _Res, const Ptr<T>& _Ptr)
{
	return _Res == _Ptr.Get();
}

template<typename T>
bool operator != (void* _Res, const Ptr<T>& _Ptr)
{
	return _Res != _Ptr.Get();
}
