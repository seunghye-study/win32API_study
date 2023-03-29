#include "pch.h"
#include "CTimeMgr.h"


CTimeMgr::CTimeMgr() 
	: m_llCurCount{}
	, m_llCurFreq{}
	, m_llPrevCount{}
	, m_dDT(0.)
	, m_iCallCount(0)
	, m_dAcc(0. )
	, m_iFPS(0){

}

CTimeMgr::~CTimeMgr() {

}

void CTimeMgr::init()
{
	//현재 카운트
	QueryPerformanceCounter(&m_llPrevCount);
	// 초당 카운트
	QueryPerformanceFrequency(&m_llCurFreq);//1초간 얼마나?
}

void CTimeMgr::Update()
{
	QueryPerformanceCounter(&m_llCurCount);
	// 이전 프레임의 카운팅과 현재 프레임 카운팅값의 차이를 구한다
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart)/(double)m_llCurFreq.QuadPart;
	//
	
	//frequency : 초당 카운트

	//이전 카운트 값을 현재값으로 갱신(다음번에 계산을 위해)
	m_llPrevCount = m_llCurCount;
	m_dAcc += m_dDT; // DT 누적(흐른 시간)
	++m_iCallCount;
	if (m_dAcc >= 1.) 
	{
		m_iFPS = m_iCallCount;
		m_dAcc = 0.;
		m_iCallCount = 0;
	}
}
