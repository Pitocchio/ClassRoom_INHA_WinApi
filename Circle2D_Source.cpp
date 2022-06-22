#include <iostream>
#include <cmath>
#include "Circle2D.h"
#include "Mypoint.h"
#define PI 3.141592

Circle2D::Circle2D()
{
	m_x = m_y = 0;
}


Circle2D::~Circle2D()
{

}

Circle2D::Circle2D(double x, double y, double radius)
{
	m_x = x;
	m_y = y;
	m_radius = radius;
}
double Circle2D::Get_X()
{
	return m_x;
}

double Circle2D::Get_Y()
{
	return m_y;
}

double Circle2D::Get_Radius()
{
	return m_radius;
}

double Circle2D::Get_Area() 
{
	return m_radius * m_radius * PI;
}

double Circle2D::Get_Perimeter() 
{
	return m_radius * 2 * PI;
}

bool Circle2D::IsContains(double x, double y) 
{
	if ((m_radius * m_radius) > ((m_x - x) * (m_x - x)) + ((m_y - y) * (m_y - y)))
		return 1;
	else
		return 0;
}

bool Circle2D::IsContains(const Circle2D& circle) 
{
	double dis = sqrt(pow((m_x - circle.m_x), 2) + pow((m_y - circle.m_y), 2));

	if (dis < (m_radius - circle.m_radius))
		return 1;
	else
		return 0;
}

bool Circle2D::Overlaps(const Circle2D& circle) 
{

	double dis = sqrt(pow((m_x - m_x), 2) + pow((m_y - m_y), 2));

	if (((m_radius - circle.m_radius) < dis) && (dis < (m_radius + circle.m_radius)))
		return 1;
	else
		return 0;
	
}

bool Circle2D::IsContains(Mypoint& p)
{
	if ((m_radius * m_radius) > ((m_x - p.Get_x()) * (m_x - p.Get_x())) + ((m_y - p.Get_y()) * (m_y - p.Get_y())))
		return 1;
	else
		return 0;
}
