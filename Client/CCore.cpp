
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
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_memDC = CreateCompatibleDC(m_hDC);
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
	CTimeMgr::GetInst()->Update();
	CkeyMgr::GetInst()->Update();
	update();
	render();
}

void CCore::update()
{
	// 키매니저
	// 어떤 역할 ?? : 프레임 동기화 
	// 업데이트 돌때 특정 키가 지금 이순간에 눌렸냐 안눌렀냐 로 확인
	// 단점 : if문까지 가야 left, right가 어떤 상태인지 알 수 있음
	// 우리 프로그램은 매 순간 업데이트를 거치고 업데이트가 끝나면 화면에 렌더링
	// == 1 프레임의 과정 --> 1프레임 시간 = dt
	// dt라는 시간이 흐르는 과정 중에서 모든 물체는 동시에 이벤트 발생
	// 그러나 프로그램의 특성상 내부적으로는 1개씩 이벤트가 발생 (각각 발생)
	// 만약 left가 눌리는 분기가 두개가 있을 때 1번 left는 left가 눌린 상태, 하지만 2번 left는 안눌린 상태일 수 있음
	// 일괄적으로 키보드의 ㅅ상태를 fix 해놓고(키매니저를 통해) 이벤트를 fix한 상태를 이용해 반영
	// 
	Vec2 vPos = g_obj.GetPos();
	if (CkeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::HOLD) {
		vPos.x -= 200.f * fDT;
	}
	if (CkeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::HOLD) {
		vPos.x += 200.f * fDT;
	}
	g_obj.SetPos(vPos);
}
void CCore::render()
{
	Rectangle(m_memDC, -1, -1, m_ptResolution.x+1, m_ptResolution.y+1);

	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();
	Rectangle(m_memDC, int(vPos.x - vScale.x/2.f),
		int(vPos.y - vScale.y / 2.f),
		int(vPos.x + vScale.x / 2.f),
		int(vPos.y + vScale.y / 2.f));
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_memDC, 0, 0, SRCCOPY);
}
