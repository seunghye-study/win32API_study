#pragma once
#include "pch.h"
#include "define.h"

 // �ð� ����ȭ
// �ʴ� �̵��� * �����Ӻ��� 1 = 0 
// �����Ӻ���1 = 1�����Ӵ� �ɸ��� �ð�
class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llPrevCount;
	LARGE_INTEGER	m_llCurFreq;

	double			m_dDT; // delta time, �����Ӱ� ������ ������ �ð�
	double			m_dAcc; // 1�� üũ�� ���� ���� �ð�
	UINT			m_iCallCount; // �Լ� ȣ�� Ƚ��
	UINT			m_iFPS; // 1������
	// fps
	// 1������ �� �ð� : Delta time
public:
	void init();
	void Update();
	//QueryPerformanceCounter(); // �ʴ� ���� ������ �鸸����, ��ƽī��Ʈ���� ����
public:
	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }
};

