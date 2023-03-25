
#include "pch.h"
#include "CCore.h"
#include "CObject.h"

CObject g_obj;

CCore::CCore() : m_hWnd(0), m_ptResolution{}, m_hDC(0)
{
	
}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);
	// 커널 오브젝트니까 해제해줌
}
int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution; // 타이틀, 메뉴바를 제외한 작업가능영역
	
	// 실제 작업할 수 있는 윈도우 작업 영역
	RECT rt = { 0,0, m_ptResolution.x, m_ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPED, true);
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right-rt.left, rt.bottom-rt.top, 0);
	// 윈도우의 위치와 크기를 변경해주는 함수
	// 1. 윈도우 핸들 : 변경을 실행할 윈도우
	// 2. setWindowPos : 타이틀, 메뉴바를 포함한 모든 영역
	//  --> _ptResolution을 setWindowPos에 맞게 변경
	//  --> AdjustWindowRect 
	//		-->> Rect 구조체 포인터를 첫번째 인자로 받아옴
	//		-->> RECT 구조체는 사각형 네 꼭짓점의 정보를 받음
	//		-->> 두번째 인자는 WS 옵션(윈도우에서 제공, 비트연산)
	//		-->> 세번째 인자는 메뉴바가 있는지 없는지
	//		-->> 작업영역의 해상도를 계산하여 첫번째 인자를 업데이트 (그래서 첫번째 인자에 _InOut_이라는 주석이 붙어있음)
	//			-->> 인풋 아웃풋이 모두 의미있다는 말 ( return 값으로 되돌려주는게 아니라, rt에 적용 하는 것)
	//			-->> 이런 방법이 효율적인곳 : 반환값이 너무 클 때 성능저하가 생기기 때문에 return 값으로 주지 않고 인자로 주소를 받아 다시 거기에 담아주는 형식
	// 
	//해상도에 맞게 윈도우 크기 조정

	g_obj.m_ptPos = POINT{ m_ptResolution.x/2, m_ptResolution.y/2 };
	g_obj.m_ptScale = POINT{ 100, 100 };

	m_hDC = GetDC(m_hWnd);


	return S_OK;
}


// 1초에 4만번 호출
void CCore::progress()
{
	update();
	render();

}

void CCore::update()
{
	// 비동기 키 입출력 함수
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		// 왼쪽키가 눌린 것
		g_obj.m_ptPos.x -= 1;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		g_obj.m_ptPos.x += 1;
	}
}

void CCore::render()
{
	// 그리기
	// begin paint, end paint 는 메세지 내부에서만 사용가능
	Rectangle(m_hDC, g_obj.m_ptPos.x - g_obj.m_ptScale.x/2, 
		g_obj.m_ptPos.y - g_obj.m_ptScale.y / 2,
		g_obj.m_ptPos.x + g_obj.m_ptScale.x / 2,
		g_obj.m_ptPos.y + g_obj.m_ptScale.y / 2);
	// 사각형이 한픽셀씩 움직이는게 아니라 갑자기 쭊 끄어짐
	// -->> 이유 : 1초에 4만번 실행하기 때문에
	// -->> 해결? : 
}
