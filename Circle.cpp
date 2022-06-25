#include "Circle_.h"
#include <ctime>
#include <cmath>

Circle::Circle(POINT Pos, double Force, double radius)
	: Geometry(Pos, Force)
{
	m_Radius = radius;
	//cout << "x: " << Get_Pos().x << " y: " << Get_Pos().y << "\n\n";

}

void Circle::Render(HDC hdc)
{
	Ellipse(hdc, Get_Pos().x - m_Radius, Get_Pos().y - m_Radius, Get_Pos().x + m_Radius, Get_Pos().y + m_Radius);
}

int Circle::Check_Collision_Wall()
{
	
	if (Get_Pos().x < (0 + m_Radius))
		return -1;
	else if (Get_Pos().x > (1000 - m_Radius))
		return 1;
	else if (Get_Pos().y < (0 + m_Radius))
		return -2;
	else if (Get_Pos().y > (800 - m_Radius))
		return 2;
	else return 0;
}


//
//void Circle::Move()
//{
//	// 업 캐스팅 해서 지오메트리의 포지션을 받아오게
//
//	Geometry* temp = this;
//	
//	m_Pos.x += cosf(m_Theta) * m_Force;
//	//	m_Pos.y += sinf(m_Theta) * m_Force;
//}