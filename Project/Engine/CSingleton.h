#pragma once
/*
* 싱글톤을 데이터 영역에 올리면 프로그램이 종료될때 저절로 삭제되지만, 중간에 해제시킬 수가 없다.
* =>특정 manager들을 해제시킬 수가 없다, 소멸자들을 내 마음대로 호출을 할 수가 없다.
* 싱글톤을 힙 영역에 올리면 내가 마음대로 소멸자들을 호출시킬 수가 있지만, 매니저를 만들때마다 내가 일일이 삭제를 해줘야한다.
* 이를 해결하기 위해 싱글톤을 힙 영역에 올리고 상속시키는 구조로 만들면 된다.
*/

typedef void (*EXIT)(void);

template<typename T>
class CSingleton
{
private:
	static T* m_Inst;
public:
	static T* GetInst();
	static void Destroy();
public:
	CSingleton() {};
	virtual ~CSingleton() {};
};

template<typename T>
T* CSingleton<T>::m_Inst = nullptr;

template<typename T>
inline T* CSingleton<T>::GetInst()
{
	if (nullptr == m_Inst) {
		//힙영역에 싱글톤 개체를 생성으니깐 내 마음대로 delete를 호출 가능하다.
		//하지만 프로그램이 종료될때 자동으로 delete를 해주게 하고 싶다!
		m_Inst = new T;
		/*
		atexit: 프로그램이 종료될때 실행되는 함수, 형식은 int atexit(void (*func)(void));
		atexit은 스택구조 이므로 마지막으로 getinst()호출된 애가 먼저 지워지기 때문에
		manager를 상속받는 새로운 manager를 만들때, 종속성 문제를 방지시킬 수가 있다.
		EXIT : 멤버변수라서 강제캐스팅이 필요함, 함수포인터는 괄호를 열면 안됨. func() X, func O
		*/
		atexit((EXIT)&CSingleton<T>::Destroy);
	}
	return m_Inst;
}

template<typename T>
inline void CSingleton<T>::Destroy()
{
	if (nullptr != m_Inst) {
		delete m_Inst;
		m_Inst = nullptr;
	}
}
