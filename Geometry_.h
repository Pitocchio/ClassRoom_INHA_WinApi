#pragma once
#include "framework.h"
#include <iostream>
using namespace std;

class Geometry
{
public: 
	Geometry();
	~Geometry();
	Geometry (POINT Pos, double Speed);

public:// Get 
	POINT Get_Pos() const { return m_Pos; }
	double Get_Speed() const { return m_Force; }

	
public: // Method
	virtual void Render(HDC hdc) = 0;
	//virtual int Check_Collision_Wall() = 0;
	virtual void Move() = 0;



protected: // Variables
	POINT m_Pos;
	double m_Force;
	double m_Theta;
	int m_IsCollision;
};