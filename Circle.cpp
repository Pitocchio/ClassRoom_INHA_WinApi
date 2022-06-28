#include "Circle_.h"
#include <ctime>
#include <cmath>



Circle::Circle(POINT Pos, double Force, double radius)
	: Geometry(Pos, Force)
{
	m_Radius = radius;
}

void Circle::Render(HDC hdc)
{
	Ellipse(hdc, Get_Pos().x - m_Radius, Get_Pos().y - m_Radius, Get_Pos().x + m_Radius, Get_Pos().y + m_Radius);
}


void Circle::Move()
{
	/*m_Pos.y += sinf(m_Theta) * m_Force;
	m_Pos.x += cosf(m_Theta) * m_Force;*/
	m_Pos.x += cosf(PI / 180 * m_Theta) * m_Force;
	m_Pos.y += sinf(PI / 180 * m_Theta) * m_Force;
}

void Circle::CheckCollisionWall(RECT rc)
{
	if (m_Pos.x < (rc.left + m_Radius)) // Left
	{
		m_Pos.x = m_Pos.x - (m_Pos.x - m_Radius - rc.left);
		m_Theta = 180 - m_Theta;
	}

	else if (m_Pos.x > (rc.right - m_Radius)) // Right
	{
		m_Pos.x = m_Pos.x - (m_Pos.x + m_Radius - rc.right);
		m_Theta = 180 - m_Theta;
	}

	else if (m_Pos.y < (rc.top + m_Radius)) // Top
	{
		m_Pos.y = m_Pos.y + m_Radius - rc.top;
		m_Theta *= -1;
	}
	else if (m_Pos.y > (rc.bottom - m_Radius)) // Bottom
	{
		m_Pos.y = m_Pos.y + (rc.bottom - (m_Pos.y + m_Radius));
		m_Theta *= -1;
	}


}
