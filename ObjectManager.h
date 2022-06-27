#pragma once
#include "Geometry_.h"
#include "Circle_.h"
#include "CollisionManager.h"
#include <map>
#include <list>
using namespace std;

class ObjectManager
{
public: // Enum
	enum OBJECT_TYPE { CIRCLE, SQUARE, STAR, TYPEEND };

private: // SingleTone_Methods
	ObjectManager();
	~ObjectManager();

public: // SingleTone_Variables
	static ObjectManager* GetInstance();
	static void DestroyInstance();
	
public: // Update
	void Update(); 
	void LateUpdate(); 
	void FixedUpdate(); 
	void Render(HDC hdc);

public: // Method
	void Create_Circle(POINT pos); // 할당 포인터해제 필요

private: // Variables
	static ObjectManager* m_ObjMgr;
	list< Geometry*> m_CircleList;
	list< Geometry*> m_SquareList;
	list< Geometry*> m_StarList;
	map <OBJECT_TYPE, list< Geometry*>> m_ObjMap;
};
