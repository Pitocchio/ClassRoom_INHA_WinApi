#include "Mypoint.h"
#include <cmath>
Mypoint::Mypoint()
{
	m_x = m_y = 0;
}
Mypoint::~Mypoint()
{

}

Mypoint::Mypoint(double x, double y)
{
	m_x = x;
	m_y = y;
}

double Mypoint::Get_x()
{
	return m_x;
}

double Mypoint::Get_y()
{
	return m_y;
}

double Mypoint::Cal_Distance(Mypoint& p)
{
	return sqrt(pow((m_x - p.Get_x()), 2) + pow((m_y - p.Get_y()), 2));
}



