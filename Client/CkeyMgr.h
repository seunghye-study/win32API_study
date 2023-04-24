#pragma once
#include "pch.h"
#include "define.h"




// 1. ������ ����ȭ
//���� ������ ������ ���� Ű�� ����, ������ �̺�Ʈ ��������

// 2. Ű �Է� �̺�Ʈ ��üȭ
// tap, hold, up, down ��

enum class KEY_STATE
{
	TAP, // �� ���� ����
	HOLD, // �� ����
	AWAY, // �� �� ����
	NONE, // ������ �ʾҰ�, �������� ������ �ʾҰ�
};

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	Q,W,E,R,T,Y,U,I,O,P,A,S,D,F,G,Z,X,C,V,B,
	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,

	LAST,
};
struct tkeyInfo 
{
	KEY_STATE	eState; // Ű ���°�
	bool		bPrev; // ���� �����ӿ��� ���ȴ��� ����
};
class CkeyMgr
{
	SINGLE(CkeyMgr);
private:
	// vector�� �ε����� enum�� �ε������� ���⶧���� key���� ���� �� �ʿ� ����
	vector<tkeyInfo> m_veckey;
public:
	void init();
	void Update();

public:
	KEY_STATE GetKeyState(KEY _eKey) {return m_veckey[(int)_eKey].eState;}
};