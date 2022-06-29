#include "Square.h"
#include <ctime>
#include <cmath>


Square::Square()
{

}

Square::~Square()
{
}

Square::Square(POINT Pos, double Force, double Height, double Width)
	: Geometry(Pos, Force)
{
	m_Height = Height;
	m_Width = Width;

	// LEFT TOP
	m_Point[0].x = m_Pos.x - (m_Width / 2);
	m_Point[0].y = m_Pos.y - (m_Height / 2);

	// RIGHT TOP
	m_Point[1].x = m_Pos.x + (m_Width / 2);
	m_Point[1].y = m_Pos.y - (m_Height / 2);


	// RIGHT BOTTOM
	m_Point[2].x = m_Pos.x + (m_Width / 2);
	m_Point[2].y = m_Pos.y + (m_Height / 2);

	// LEFT BOTTOM
	m_Point[3].x = m_Pos.x - (m_Width / 2);
	m_Point[3].y = m_Pos.y + (m_Height / 2);
}

void Square::Render(HDC hdc)
{
	Polygon(hdc, m_Point, 4);
}

void Square::Move()
{
	m_Pos.x += m_lookVec.x * m_Distance;
	m_Pos.y += m_lookVec.y * m_Distance;

	// LEFT TOP
	m_Point[0].x = m_Pos.x - (m_Width / 2);
	m_Point[0].y = m_Pos.y - (m_Height / 2);

	// RIGHT TOP
	m_Point[1].x = m_Pos.x + (m_Width / 2);
	m_Point[1].y = m_Pos.y - (m_Height / 2);


	// RIGHT BOTTOM
	m_Point[2].x = m_Pos.x + (m_Width / 2);
	m_Point[2].y = m_Pos.y + (m_Height / 2);

	// LEFT BOTTOM
	m_Point[3].x = m_Pos.x - (m_Width / 2);
	m_Point[3].y = m_Pos.y + (m_Height / 2);

}


void Square::CheckCollisionWall(RECT rc)
{
	if (m_Pos.x < (rc.left + (m_Width / 2))) // Left
	{
		m_Pos.x = m_Pos.x - (m_Pos.x - (m_Width / 2) - rc.left);
		//m_Theta = 180 - m_Theta;
		m_lookVec.x *= -1;
	}

	else if (m_Pos.x > (rc.right - (m_Width / 2))) // Right
	{
		m_Pos.x = m_Pos.x - (m_Pos.x + (m_Width / 2) - rc.right);
		//m_Theta = 180 - m_Theta;
		m_lookVec.x *= -1;

	}

	else if (m_Pos.y < (rc.top + (m_Height / 2))) // Top
	{
		m_Pos.y = m_Pos.y + (m_Height / 2) - rc.top;
		//m_Theta *= -1;
		m_lookVec.y *= -1;

	}
	else if (m_Pos.y > (rc.bottom - (m_Height / 2))) // Bottom
	{
		m_Pos.y = m_Pos.y + (rc.bottom - (m_Pos.y + (m_Height / 2)));
		//m_Theta *= -1;
		m_lookVec.y *= -1;

	}
}