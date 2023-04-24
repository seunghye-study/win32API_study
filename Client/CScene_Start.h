#pragma once
#include "CScene.h" // 부모클래스(상속)
class CScene_Start :
    public CScene
{
public:
    // 부모쪽에서 virtual이라고 선언 해두었지만
    // virtual 안붙여도 이미 오버라이딩 한 시점에서 virtual 함수
    // 명시적으로 더 확실하게
    virtual void Enter();
    virtual void Exit();
public:
    CScene_Start();
    ~CScene_Start();
};

