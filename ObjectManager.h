#pragma once
#include "Geometry_.h"
#include "Circle_.h"
#include "CollisionManager.h"
#include <algorithm>
#include <map>
#include <list>
#include <cmath>
using namespace std;

class ObjectManager
{
public: // Enum
	enum OBJECT_TYPE { CIRCLE, SQUARE, STAR, OBJECT_TYPEEND };

private: // SingleTone_Methods
	ObjectManager();
	~ObjectManager();

public: // SingleTone_Variables
	static ObjectManager* GetInstance();
	static void DestroyInstance();
	
public: // Update
	void Initialize();
	void Update(); 
	void LateUpdate(RECT rc); 
	void FixedUpdate(); 
	void Render(HDC hdc);

public: // Method
	void Add_Object(int objtype, Geometry*); // 생성된 객체를 알맞은 리스트에 넣어줌

private: // Variables
	static ObjectManager* m_ObjMgr; // 싱글톤 오브젝트 매니저 스태틱 변수
	
	typedef list<Geometry*> LIST_GEO; // list<Geometry*> 자료형을 LIST_GEO라는 이름으로 재정의 (즉 자료형의 이름을 재정의, 자료형 이름이 기니까 짧게 편하게 줄임)
	typedef map <OBJECT_TYPE, LIST_GEO> OBJ_MAP; // 위와 마찬가지
	OBJ_MAP m_ObjMap;


	/*
	LIST_GEO = GEO_LIST
	OBJ_MAP = OBJ_LIST
	*/
};
