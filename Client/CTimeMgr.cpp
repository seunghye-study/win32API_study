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
	QueryPerformanceCounter(&m_llPrevCount);
	QueryPerformanceFrequency(&m_llCurFreq);
}

void CTimeMgr::Update()
{
	QueryPerformanceCounter(&m_llCurCount);
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart)/(double)m_llCurFreq.QuadPart;
	m_llPrevCount = m_llCurCount;
	m_dAcc += m_dDT;
	++m_iCallCount;
	if (m_dAcc >= 1.) 
	{
		m_iFPS = m_iCallCount;
		m_dAcc = 0.;
		m_iCallCount = 0;
	}
}
