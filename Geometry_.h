#pragma once
#include "framework.h"
#include <iostream>
#define PI 3.1415926535
using namespace std;

class Geometry
{
public: 
	Geometry();
	~Geometry();
	Geometry (POINT Pos, double Speed);

public: // Get 
	POINT Get_Pos() const { return m_Pos; }
	double Get_Speed() const { return m_Force; }
	Geometry* Get_CollisionObj() const { return m_CollisionObj; }
	double Get_Theta() const { return m_Theta; }

public: // Set
	void Set_Pos(POINT pos) { m_Pos = pos; }
	void Set_Pos(int x, int y) { m_Pos.x = x, m_Pos.y =y; }
	void Set_Theta(double theta) { m_Theta = theta; }


public: // Collision
	void Set_IsCollisionObj(bool b);
	void Set_CollisionObj(Geometry* obj);
	bool Peak_IsCollision();
	void Reset_CollisionObj();


	
public: // Method
	virtual void Render(HDC hdc) = 0;
	virtual void Move() = 0;
	virtual void CheckCollisionWall(RECT rc) = 0; // 프레임워크 개념에서의 수리 대상 1

protected: // Variables
	POINT m_Pos;
	double m_Force;
	double m_Theta;
	//int m_IsCollisionWall;
	int m_IsCollisionObj;
	Geometry* m_CollisionObj;
};