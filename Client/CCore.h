#pragma once
#include "define.h"
#include "pch.h"
class CCore 
{
	SINGLE(CCore);
private:
	HWND	m_hWnd; // 메인 윈도우
	POINT   m_ptResolution; // 해상도
	HDC		m_hDC; // DC
public:
	int init(HWND _hWnd, POINT _ptResolution);
	void progress();

private:
	void update();
	void render();
private:
	CCore();
	~CCore();
};