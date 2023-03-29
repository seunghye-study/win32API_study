#pragma once
#include "pch.h"
#include "define.h"

 // 시간 동기화
// 초당 이동량 * 프레임분의 1 = 0 
// 프레임분의1 = 1프레임당 걸리는 시간
class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llPrevCount;
	LARGE_INTEGER	m_llCurFreq;

	double			m_dDT; // delta time, 프레임과 프레임 사이의 시간
	double			m_dAcc; // 1초 체크를 위한 누적 시간
	UINT			m_iCallCount; // 함수 호출 횟수
	UINT			m_iFPS; // 1프레임
	// fps
	// 1프레임 당 시간 : Delta time
public:
	void init();
	void Update();
	//QueryPerformanceCounter(); // 초당 세는 단위가 백만단위, 겟틱카운트보다 많음
public:
	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }
};

