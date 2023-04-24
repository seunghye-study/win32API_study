#pragma once


// 전방선언
class CObject;
// 클래스 타입 자체는 쓸 수 없다 : 무슨 타입인지 모름, 링크로 넘기는것
// 포인터 타입만 쓸 수 있음 : 포인터 사이즈는 알고 있음(고정사이즈)
// 컴파일 속도에 영향을 주지 않기 위해
// object를 include 하면 object 파일이 바뀔 때 마다 컴파일러가 확인해줘야함
// 서로 참조를 최소화

// virtual 클래스와 상속에 대해
// 씬의 활용 : 전역선언된 오브젝트를 씬에 넣어서 관리

class CScene
{
// protected 의 활용 : 변수 protected는 디버깅할 때 힘들다 == 함수를 protected로 제공하기

private:
	// 오프젝트를 저장 및 관리할 벡터를 그룹 개수만큼 선언
	vector<CObject*>	m_arrObj[(UINT)GROUP_TYPE::END];
	wstring				m_strName; // scene 이름

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }
	virtual void Enter() = 0; // 해당 씬 진입
	virtual void Exit() = 0; // 해당 씬 탈출
	// 순수 가상 함수
	// 이 함수만큼은 상속받은 애들이 이 함수를 만들게 강제
	// 부모 클래스는 이 클래스로 객체를 만들 수 없음(??)

	void Update();
	void Render(HDC _dc);
protected:
	// 인라인 함수(함수호출비용X)
	void AddObject(CObject* _pObj, GROUP_TYPE _eType)
	{
		m_arrObj[(UINT)_eType].push_back(_pObj);
	}

public:
	CScene();
	virtual ~CScene();
};

