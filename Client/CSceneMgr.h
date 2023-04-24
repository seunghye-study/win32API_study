#pragma once
class CScene;
class CSceneMgr
{
	SINGLE(CSceneMgr);

private:
	CScene*		m_arrScene[(UINT)SCENE_TYPE::END];
	CScene*		m_pCurScene; // ���� ��
public:
	void init();
	void Update();
	void Render(HDC _dc);
public:
	CSceneMgr();
	~CSceneMgr();
};

