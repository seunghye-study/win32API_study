#pragma once
#include "define.h"
#include "pch.h"
class CCore 
{
	SINGLE(CCore);
private:
	HWND	m_hWnd; // ���� ������
	POINT   m_ptResolution; // �ػ�
	HDC		m_hDC; // DC
	// ���� ���۸�
	HBITMAP m_hBit; // ��Ʈ�� �ڵ�
	HDC		m_memDC; // ��Ʈ�� DC
public:
	int init(HWND _hWnd, POINT _ptResolution);
	void progress();

private:
	void update();
	void render();
};