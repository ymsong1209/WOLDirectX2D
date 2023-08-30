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

	//기존에 값을 가지고 있었는데 다른 것이 들어올 경우
	void operator = (T* _Res)
	{
		//기존에 가지고 있던거에 release해야함.
		if (nullptr != m_Res)
			m_Res->Release();

		m_Res = _Res;

		if (nullptr != m_Res)
			m_Res->AddRef();
	}

	//스마트포인터가 입력으로 들어온 경우
	void operator = (const Ptr<T>& _Res)
	{
		if (nullptr != m_Res)
			m_Res->Release();

		m_Res = _Res.m_Res;

		if (nullptr != m_Res)
			m_Res->AddRef();
	}

	//후위연산자
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

//Ptr은 클래스이기 때문에 연산자 오버로딩으로 전위연산자를 만들 수가 없다.
//이렇게 전역함수로 만들어야한다.
//인자로 void* _Res대신 T* res를 넣으면 nullptr를 인식못한다.
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
