#pragma once


// ���漱��
class CObject;
// Ŭ���� Ÿ�� ��ü�� �� �� ���� : ���� Ÿ������ ��, ��ũ�� �ѱ�°�
// ������ Ÿ�Ը� �� �� ���� : ������ ������� �˰� ����(����������)
// ������ �ӵ��� ������ ���� �ʱ� ����
// object�� include �ϸ� object ������ �ٲ� �� ���� �����Ϸ��� Ȯ���������
// ���� ������ �ּ�ȭ

// virtual Ŭ������ ��ӿ� ����
// ���� Ȱ�� : ��������� ������Ʈ�� ���� �־ ����

class CScene
{
// protected �� Ȱ�� : ���� protected�� ������� �� ����� == �Լ��� protected�� �����ϱ�

private:
	// ������Ʈ�� ���� �� ������ ���͸� �׷� ������ŭ ����
	vector<CObject*>	m_arrObj[(UINT)GROUP_TYPE::END];
	wstring				m_strName; // scene �̸�

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }
	virtual void Enter() = 0; // �ش� �� ����
	virtual void Exit() = 0; // �ش� �� Ż��
	// ���� ���� �Լ�
	// �� �Լ���ŭ�� ��ӹ��� �ֵ��� �� �Լ��� ����� ����
	// �θ� Ŭ������ �� Ŭ������ ��ü�� ���� �� ����(??)

	void Update();
	void Render(HDC _dc);
protected:
	// �ζ��� �Լ�(�Լ�ȣ����X)
	void AddObject(CObject* _pObj, GROUP_TYPE _eType)
	{
		m_arrObj[(UINT)_eType].push_back(_pObj);
	}

public:
	CScene();
	virtual ~CScene();
};

