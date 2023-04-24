#include "pch.h"
#include "CkeyMgr.h"
#include "CCore.h"
// WINDOW 키값이랑 대응하기 위한 배열
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

	//m_veckey[(int)KEY::LEFT].bPrev -> 이전에 left가 눌렸는지
	//m_veckey[(int)KEY::LEFT].eState -> 지금 left의 상태
}

// 키입력 흐름
// TAP -> AWAY -> NONE
// HOLD -> AWAY -> NONE
// AWAY -> NONE
// NONE -> NONE


void CkeyMgr::Update()
{
	//윈도우 포커싱 알아내기
	//HWND hMainWnd = CCore::GetInst()->GetMainHwnd();
	HWND hWnd = GetFocus(); // 포커싱 알아내는 윈도우 api
	// 윈도우 포커싱 중일 때
	if (nullptr != hWnd) 
	{
		for (int i = 0; i < (int)KEY::LAST; i++)
		{
			//  키가 눌려있다.
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000) {
				if (m_veckey[i].bPrev) {
					// 이전에도 눌려있었다.
					m_veckey[i].eState = KEY_STATE::HOLD;
				}
				else
				{
					// 이전에 눌려있지 않았다.
					m_veckey[i].eState = KEY_STATE::TAP;
				}
				m_veckey[i].bPrev = true;
			}
			// 키가 안눌려있다.
			else {
				if (m_veckey[i].bPrev) {
					// 이전에 눌려있었다.
					m_veckey[i].eState = KEY_STATE::AWAY;
				}
				else
				{
					// 이전에 안눌려있었다.
					m_veckey[i].eState = KEY_STATE::NONE;
				}
				m_veckey[i].bPrev = false;
			}
		}
	}
	// 윈도우 포커싱 x
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
