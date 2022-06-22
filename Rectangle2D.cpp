#include "Rectangle2D.h"
#include "Mypoint.h"
#include <iostream>
#include <cmath>

Rectangle2D::Rectangle2D()
{
	m_x = m_y = m_width = m_height = 0;
}

Rectangle2D::~Rectangle2D()
{

}

Rectangle2D::Rectangle2D(double x, double y, double width, double height)
{
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
}

double Rectangle2D::Get_X()
{
	return m_x;
}
double Rectangle2D::Get_Y()
{
	return m_y;
}
double Rectangle2D::Get_WIDTH()
{
	return m_width;
}
double Rectangle2D::GET_HEIGHT()
{
	return m_height;
}
void Rectangle2D::Set_X(double x)
{
	m_x = x;
}
void Rectangle2D::Set_Y(double y)
{
	m_y = y;
}
void Rectangle2D::Set_WIDHT(double width)
{
	m_width = width;
}
void Rectangle2D::Set_HEIGHT(double height)
{
	m_height = height;
}

double Rectangle2D::Get_Area()
{
	return m_width * m_height;
}

double Rectangle2D::GetPerimeter()
{
	return (m_width * 2) + (m_height * 2);
}

bool Rectangle2D::IsContains(double x, double y)
{
	double top_heightY1 = m_y + (m_height / 2);
	double bottom_heightY1 = m_y - (m_height / 2);
	double left_widthX1 = m_x - (m_width / 2);
	double right_widthX1 = m_x + (m_width / 2);

	return (((left_widthX1 < x) && (x < right_widthX1)) && ((bottom_heightY1 < y) && (y < top_heightY1)));

}
bool Rectangle2D::IsContains(const Rectangle2D& r)
{
	double top_heightY1 = m_y + (m_height / 2);
	double bottom_heightY1 = m_y - (m_height / 2);
	double left_widthX1 = m_x - (m_width / 2);
	double right_widthX1 = m_x + (m_width / 2);

	double top_heightY2 = r.m_y + (r.m_height / 2);
	double bottom_heightY2 = r.m_y - (r.m_height / 2);
	double left_widthX2 = r.m_x - (r.m_width / 2);
	double right_widthX2 = r.m_x + (r.m_width / 2);

	return (((left_widthX1 < left_widthX2) && (right_widthX2 < right_widthX1)) && ((bottom_heightY1 < bottom_heightY2) && (top_heightY2 < top_heightY1)));
}

bool Rectangle2D::IsOverlaps(const Rectangle2D& r)
{
	double top_heightY1 = m_y + (m_height / 2);
	double bottom_heightY1 = m_y - (m_height / 2);
	double left_widthX1 = m_x - (m_width / 2);
	double right_widthX1 = m_x + (m_width / 2);

	double top_heightY2 = r.m_y + (r.m_height / 2);
	double bottom_heightY2 = r.m_y - (r.m_height / 2);
	double left_widthX2 = r.m_x - (r.m_width / 2);
	double right_widthX2 = r.m_x + (r.m_width / 2);

	if (bottom_heightY1 < top_heightY2 && top_heightY1 > bottom_heightY2)
		return 1;

	else if (left_widthX1 > right_widthX2 && right_widthX1 < left_widthX2)
		return 1;

	else
		return 0;
}


bool Rectangle2D::IsContains(Mypoint& p)
{
	double top_heightY1 = m_y + (m_height / 2);
	double bottom_heightY1 = m_y - (m_height / 2);
	double left_widthX1 = m_x - (m_width / 2);
	double right_widthX1 = m_x + (m_width / 2);

	return (((left_widthX1 < p.Get_x()) && (p.Get_x() < right_widthX1)) && ((bottom_heightY1 < p.Get_y()) && (p.Get_y() < top_heightY1)));
}
