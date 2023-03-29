
#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CkeyMgr.h"

CObject g_obj;

CCore::CCore() : m_hWnd(0), m_ptResolution{}, m_hDC(0), m_hBit(0), m_memDC(0)
{
	
}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);
	DeleteDC(m_memDC);
	DeleteObject(m_hBit);
}
int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	RECT rt = { 0,0, m_ptResolution.x, m_ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPED, true);
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right-rt.left, rt.bottom-rt.top, 0);


	m_hDC = GetDC(m_hWnd);

	// 이중 버퍼링 용도의 비트맵과 DC 생성
	// bitmap 만들기
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	// 비트맵 핸들(비트맵을 목적지로 하는 dc 생성), 디폴트 비트맵 생성
	m_memDC = CreateCompatibleDC(m_hDC);
	// 그림을그릴 타겟 목적지를 바꿔주는 것
	// 디폴트 비트맵 삭제하고 새 비트맵 전달
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBit);

	CTimeMgr::GetInst()->init();
	CkeyMgr::GetInst()->init();
	g_obj.SetPos(Vec2((float)(m_ptResolution.x / 2), (float)(m_ptResolution.y / 2)));
	g_obj.SetScale(Vec2(100, 100));

	return S_OK;
}

void CCore::progress()
{
	//Manager Update;
	CTimeMgr::GetInst()->Update();
	update();
	render();

}

void CCore::update()
{
	Vec2 vPos = g_obj.GetPos();

	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		vPos.x -= 100.f * fDT;
		// 이동량은 고정값이면 안됨
		// 컴퓨터 성능에 따라 가변값이어야 같은 시간동안 같은 이동수가 보장될 수 있음
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		vPos.x += 100.f * fDT;
	}
	g_obj.SetPos(vPos);
}

void CCore::render()
{
	// 화면청소
	Rectangle(m_memDC, -1, -1, m_ptResolution.x+1, m_ptResolution.y+1);


	// 그리기
	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();
	Rectangle(m_memDC, int(vPos.x - vScale.x/2.f),
		int(vPos.y - vScale.y / 2.f),
		int(vPos.x + vScale.x / 2.f),
		int(vPos.y + vScale.y / 2.f));

	// 비트맵을 원래 윈도우에 복사해주기
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_memDC, 0, 0, SRCCOPY);

	// 프레임이 굉장히 떨어짐
	// FOR문이 너무 많고 반복적인 작업의 반복의 반복이라 비효율적
	// 그래서 나온 장치 : GPU 
	// RENDERING을 GPU에게 넘김 :: 굉장히 빠르게 끝냄
}
