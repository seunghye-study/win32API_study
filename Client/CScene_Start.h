#pragma once
#include "CScene.h" // �θ�Ŭ����(���)
class CScene_Start :
    public CScene
{
public:
    // �θ��ʿ��� virtual�̶�� ���� �صξ�����
    // virtual �Ⱥٿ��� �̹� �������̵� �� �������� virtual �Լ�
    // ��������� �� Ȯ���ϰ�
    virtual void Enter();
    virtual void Exit();
public:
    CScene_Start();
    ~CScene_Start();
};

