#include "pch.h"
#include "CkeyMgr.h"
#include "CCore.h"
// WINDOW Ű���̶� �����ϱ� ���� �迭
int g_arrVK[(int)KEY::LAST] =
{
	VK_LEFT,//LEFT,
	VK_RIGHT,//RIGHT,
	VK_UP,//UP,
	VK_DOWN,//DOWN,
	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',
	'A',
	'S',
	'D',
	'F',
	'G',
	'Z',
	'X',
	'C',
	'V',
	'B',
	VK_MENU, //ALT,
	VK_CONTROL,//CTRL,
	VK_LSHIFT,//LSHIFT,
	VK_SPACE,//SPACE,
	VK_RETURN,//ENTER,
	VK_ESCAPE//ESC,
	//LAST,
};

CkeyMgr::CkeyMgr() {

}
CkeyMgr::~CkeyMgr() {

}

void CkeyMgr::init()
{
	for (int i = 0; i<(int)KEY::LAST; i++)
	{
		m_veckey.push_back(tkeyInfo{ KEY_STATE::NONE, false });
	}
	// m_veckey[0] == LEFT

	//m_veckey[(int)KEY::LEFT].bPrev -> ������ left�� ���ȴ���
	//m_veckey[(int)KEY::LEFT].eState -> ���� left�� ����
}

// Ű�Է� �帧
// TAP -> AWAY -> NONE
// HOLD -> AWAY -> NONE
// AWAY -> NONE
// NONE -> NONE


void CkeyMgr::Update()
{
	//������ ��Ŀ�� �˾Ƴ���
	//HWND hMainWnd = CCore::GetInst()->GetMainHwnd();
	HWND hWnd = GetFocus(); // ��Ŀ�� �˾Ƴ��� ������ api
	// ������ ��Ŀ�� ���� ��
	if (nullptr != hWnd) 
	{
		for (int i = 0; i < (int)KEY::LAST; i++)
		{
			//  Ű�� �����ִ�.
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000) {
				if (m_veckey[i].bPrev) {
					// �������� �����־���.
					m_veckey[i].eState = KEY_STATE::HOLD;
				}
				else
				{
					// ������ �������� �ʾҴ�.
					m_veckey[i].eState = KEY_STATE::TAP;
				}
				m_veckey[i].bPrev = true;
			}
			// Ű�� �ȴ����ִ�.
			else {
				if (m_veckey[i].bPrev) {
					// ������ �����־���.
					m_veckey[i].eState = KEY_STATE::AWAY;
				}
				else
				{
					// ������ �ȴ����־���.
					m_veckey[i].eState = KEY_STATE::NONE;
				}
				m_veckey[i].bPrev = false;
			}
		}
	}
	// ������ ��Ŀ�� x
	else
	{
		for (int i = 0; i < (int)KEY::LAST; i++)
		{
			m_veckey[i].bPrev = false;
			if (KEY_STATE::TAP == m_veckey[i].eState || KEY_STATE::HOLD == m_veckey[i].eState)
			{
				m_veckey[i].eState = KEY_STATE::AWAY;
			}
			else if (KEY_STATE::AWAY == m_veckey[i].eState)
			{
				m_veckey[i].eState = KEY_STATE::NONE;
			}
			else
			{
				m_veckey[i].eState = KEY_STATE::NONE;
			}
		}
	}
}
