#include <iostream>
#include "GEOMETRY.h"

Geometry::Geometry(POINT Pos, double Speed, double Look)
{
	m_Pos = Pos;
	m_Speed = Speed;
	m_Look = Look;
};



Circle::Circle(POINT Pos, double Speed, double Look, double radius)
	: Geometry(Pos, Speed, Look)
{
	m_Radius = radius;

	//this->PushBack(); // 생성과 동시에 벡터에 넣어줌 
}


