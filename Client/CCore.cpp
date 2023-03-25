
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
	// Ŀ�� ������Ʈ�ϱ� ��������
}
int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution; // Ÿ��Ʋ, �޴��ٸ� ������ �۾����ɿ���
	
	// ���� �۾��� �� �ִ� ������ �۾� ����
	RECT rt = { 0,0, m_ptResolution.x, m_ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPED, true);
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right-rt.left, rt.bottom-rt.top, 0);
	// �������� ��ġ�� ũ�⸦ �������ִ� �Լ�
	// 1. ������ �ڵ� : ������ ������ ������
	// 2. setWindowPos : Ÿ��Ʋ, �޴��ٸ� ������ ��� ����
	//  --> _ptResolution�� setWindowPos�� �°� ����
	//  --> AdjustWindowRect 
	//		-->> Rect ����ü �����͸� ù��° ���ڷ� �޾ƿ�
	//		-->> RECT ����ü�� �簢�� �� �������� ������ ����
	//		-->> �ι�° ���ڴ� WS �ɼ�(�����쿡�� ����, ��Ʈ����)
	//		-->> ����° ���ڴ� �޴��ٰ� �ִ��� ������
	//		-->> �۾������� �ػ󵵸� ����Ͽ� ù��° ���ڸ� ������Ʈ (�׷��� ù��° ���ڿ� _InOut_�̶�� �ּ��� �پ�����)
	//			-->> ��ǲ �ƿ�ǲ�� ��� �ǹ��ִٴ� �� ( return ������ �ǵ����ִ°� �ƴ϶�, rt�� ���� �ϴ� ��)
	//			-->> �̷� ����� ȿ�����ΰ� : ��ȯ���� �ʹ� Ŭ �� �������ϰ� ����� ������ return ������ ���� �ʰ� ���ڷ� �ּҸ� �޾� �ٽ� �ű⿡ ����ִ� ����
	// 
	//�ػ󵵿� �°� ������ ũ�� ����

	g_obj.m_ptPos = POINT{ m_ptResolution.x/2, m_ptResolution.y/2 };
	g_obj.m_ptScale = POINT{ 100, 100 };

	m_hDC = GetDC(m_hWnd);


	return S_OK;
}


// 1�ʿ� 4���� ȣ��
void CCore::progress()
{
	update();
	render();

}

void CCore::update()
{
	// �񵿱� Ű ����� �Լ�
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		// ����Ű�� ���� ��
		g_obj.m_ptPos.x -= 1;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		g_obj.m_ptPos.x += 1;
	}
}

void CCore::render()
{
	// �׸���
	// begin paint, end paint �� �޼��� ���ο����� ��밡��
	Rectangle(m_hDC, g_obj.m_ptPos.x - g_obj.m_ptScale.x/2, 
		g_obj.m_ptPos.y - g_obj.m_ptScale.y / 2,
		g_obj.m_ptPos.x + g_obj.m_ptScale.x / 2,
		g_obj.m_ptPos.y + g_obj.m_ptScale.y / 2);
	// �簢���� ���ȼ��� �����̴°� �ƴ϶� ���ڱ� �� ������
	// -->> ���� : 1�ʿ� 4���� �����ϱ� ������
	// -->> �ذ�? : 
}
