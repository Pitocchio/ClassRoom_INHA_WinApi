#include <iostream>
#include "GEOMETRY.h"


Geometry::Geometry(POINT Pos, double Force)
{
	m_Pos = Pos;
	m_Force = Force;

	srand(time(NULL));
	m_Theta = rand() % 360;
};

void Geometry::Set_Pos()
{
	m_Pos.x += cosf(m_Theta) * m_Force;
	m_Pos.y += sinf(m_Theta) * m_Force;
}
//
//bool Geometry::Check_Collision_Wall()
//{
//
//}

Circle::Circle(POINT Pos, double Force, double radius)
	: Geometry(Pos, Force)
{
	m_Radius = radius;

	std::cout << "Create New Object\n\n";
}


void CircleManager::Update()
{
	// Position Update
	for (int i = 0; i < m_Vector.size(); ++i)
	{
		m_Vector[i].Set_Pos();
		
	}
}
