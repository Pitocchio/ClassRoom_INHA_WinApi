#include "Geometry_.h"
#include <ctime>
#include <cmath>

Geometry::Geometry() 
{ 
	m_Pos = { 0 }; 
	m_Force = 0; 
	m_IsCollision = 0;
};

Geometry::~Geometry()
{

}

Geometry::Geometry(POINT Pos, double Force)
{
	m_Pos = Pos;
	m_Force = Force;

	srand(time(NULL));
	m_Theta = rand() % 360;
};


void Geometry::Move()
{

	switch (Check_Collision_Wall())
	{
		case 0:
				m_Pos.x += cosf(m_Theta) * m_Force;
				m_Pos.y += sinf(m_Theta) * m_Force;
				break;

		case -1: 
				m_Pos.x += cosf(m_Theta) * m_Force * -1;
				m_Pos.y += sinf(m_Theta) * m_Force;
				cout << "왼쪽 충돌!\n\n";
				break;

		case 1:
				m_Pos.x += cosf(m_Theta) * m_Force * -1;
				m_Pos.y += sinf(m_Theta) * m_Force;
				cout << "오른쪽 충돌!\n\n";
				break;

		case -2:
				m_Pos.x += cosf(m_Theta) * m_Force;
				m_Pos.y += sinf(m_Theta) * m_Force * -1;
				cout << "위쪽 충돌!\n\n";
				break;

		case 2:
				m_Pos.x += cosf(m_Theta) * m_Force;
				m_Pos.y += sinf(m_Theta) * m_Force * -1;
				cout << "아래쪽 충돌!\n\n";
				break;
	}	
}
