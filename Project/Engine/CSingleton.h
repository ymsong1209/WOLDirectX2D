#pragma once
/*
* �̱����� ������ ������ �ø��� ���α׷��� ����ɶ� ������ ����������, �߰��� ������ų ���� ����.
* =>Ư�� manager���� ������ų ���� ����, �Ҹ��ڵ��� �� ������� ȣ���� �� ���� ����.
* �̱����� �� ������ �ø��� ���� ������� �Ҹ��ڵ��� ȣ���ų ���� ������, �Ŵ����� ���鶧���� ���� ������ ������ ������Ѵ�.
* �̸� �ذ��ϱ� ���� �̱����� �� ������ �ø��� ��ӽ�Ű�� ������ ����� �ȴ�.
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
		//�������� �̱��� ��ü�� �������ϱ� �� ������� delete�� ȣ�� �����ϴ�.
		//������ ���α׷��� ����ɶ� �ڵ����� delete�� ���ְ� �ϰ� �ʹ�!
		m_Inst = new T;
		/*
		atexit: ���α׷��� ����ɶ� ����Ǵ� �Լ�, ������ int atexit(void (*func)(void));
		atexit�� ���ñ��� �̹Ƿ� ���������� getinst()ȣ��� �ְ� ���� �������� ������
		manager�� ��ӹ޴� ���ο� manager�� ���鶧, ���Ӽ� ������ ������ų ���� �ִ�.
		EXIT : ��������� ����ĳ������ �ʿ���, �Լ������ʹ� ��ȣ�� ���� �ȵ�. func() X, func O
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
