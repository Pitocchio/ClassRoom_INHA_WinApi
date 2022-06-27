#pragma once
#include "ObjectManager.h"

class CollisionManager
{
private: // SingleTone_Methods
	CollisionManager();
	~CollisionManager();

public: // SingleTone_Variables
	static CollisionManager* GetInstance();
	static void DestroyInstance();

public: // method 
	void Detect_Collision(); // 전체 리스트 돌면서 충돌검사하고, 만약 충돌이 감지 되었다면 해당 객체의 충돌 플래그를 true로 세팅
							 // 충돌검사함수(충돌종류, 객체타입1, 객체타입2) => 객체 타입 1과 2의 충돌종류 값을 갖고 충돌을 검사함 

	void Process_Collision(); // 전체 돌면서 충돌 플래그 ture인 것을 처리하고 다시 false로 초기화


private: //Variables
	static CollisionManager* m_ColMgr;


};


/*
Update / LateUpdate / FixedUpdate 에서 CollisionManager의 충돌 관련 함수를 호출

그리고 호출시 오브젝트 매니저를 인자로 넘겨줌


1. 무브 

2. 충돌 감지
	if (두 원의 중점 사이의 거리 <= 두 원의 반지름의 합)
		충돌 발생

3. 충돌 처리

*/