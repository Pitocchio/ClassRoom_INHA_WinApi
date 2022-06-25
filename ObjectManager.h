#pragma once
#include "Geometry_.h"
#include "Circle_.h"
#include <vector>
#include <list>

class ObjectManager
{
private: // SingleTone 
	ObjectManager() {}
	~ObjectManager() {}
	
public: // Update
	void Update(); 
	void LateUpdate(); 
	void FixedUpdate(); 
	void Render(HDC hdc);

public: // SingleTone
	static ObjectManager* GetInstance();
	static void DestroyInstance();

public: // Function
	void Create_Circle(POINT pos); // 할당 포인터해제 필요
	
private: // Variables
	static ObjectManager* m_ObjMgr;
	list< Geometry*> m_CircleList;
	list< Geometry*> m_SquareList;
	list< Geometry*> m_StarList;
};



//ector<Geometry*> m_arrvecObj[(UINT)GROUP_TYPE::END];
