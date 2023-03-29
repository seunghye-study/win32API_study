#pragma once
#include "pch.h"
#include "define.h"

class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llPrevCount;
	LARGE_INTEGER	m_llCurFreq;
	double			m_dDT;
	double			m_dAcc;
	UINT			m_iCallCount;
	UINT			m_iFPS;
public:
	void init();
	void Update();
public:
	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }
};