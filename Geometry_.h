#pragma once
#include "framework.h"
#include <iostream>
#define PI 3.1415926535
using namespace std;

struct Vector2
{
	double x, y;
};

class Geometry
{
public: 
	Geometry();
	~Geometry();
	Geometry (POINT Pos, double Speed);

public: // Get 
	//POINT Get_Pos() const { return m_Pos; }
	Vector2 Get_Pos() const { return m_Pos; }
	Geometry* Get_CollisionObj() const { return m_CollisionObj; }
	double Get_Angle() const { return m_Angle; }
	Vector2 Get_LookVec() const { return m_lookVec; }

public: // Set
	//void Set_Pos(Vector2 pos) { m_Pos = pos; }
	void Set_Pos(double x, double y) { m_Pos.x = x, m_Pos.y = y; }
	void Set_Angle(double angle) { m_Angle = angle; }
	void Set_Lookvec(Vector2 lookvec) { m_lookVec = lookvec; }


public: // Collision
	void Set_IsCollisionObj(bool b);
	void Set_CollisionObj(Geometry* obj);
	bool Peak_IsCollision();
	void Reset_CollisionObj();


	
public: // Method
	virtual void Render(HDC hdc) = 0;
	virtual void Move() = 0;
	virtual void CheckCollisionWall(RECT rc) = 0;

protected: // Variables
	//POINT m_Pos;
	double m_Angle;
	//int m_IsCollisionWall;
	int m_IsCollisionObj;
	Geometry* m_CollisionObj;

	

	// 방향벡터 수정중
	Vector2 m_lookVec;
	double m_Distance;

	Vector2 m_Pos;

	
};