#pragma once
#include "pch.h"
#include "define.h"




// 1. 프레임 동기화
//동일 프레임 내에서 같은 키에 대해, 동일한 이벤트 가져간다

// 2. 키 입력 이벤트 구체화
// tap, hold, up, down 등

enum class KEY_STATE
{
	TAP, // 막 누른 시점
	HOLD, // 꾹 누름
	AWAY, // 막 뗀 시점
	NONE, // 눌리지 않았고, 이전에도 눌리지 않았고
};

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	Q,W,E,R,T,Y,U,I,O,P,A,S,D,F,G,Z,X,C,V,B,
	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,

	LAST,
};
struct tkeyInfo 
{
	KEY_STATE	eState; // 키 상태값
	bool		bPrev; // 이전 프레임에서 눌렸는지 여부
};
class CkeyMgr
{
	SINGLE(CkeyMgr);
private:
	// vector의 인덱스가 enum의 인덱스값과 같기때문에 key값이 뭔지 알 필요 없음
	vector<tkeyInfo> m_veckey;
public:
	void init();
	void Update();

public:
	KEY_STATE GetKeyState(KEY _eKey) {return m_veckey[(int)_eKey].eState;}
};