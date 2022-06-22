#pragma once

class Mypoint;

class Circle2D
{
private: double m_x, m_y, m_radius;

public:
	Circle2D();
	~Circle2D();
	Circle2D(double x, double y, double radius);

	double Get_X();
	double Get_Y();
	double Get_Radius();

	double Get_Area();
	double Get_Perimeter();
	bool IsContains(double x, double y);
	bool IsContains(const Circle2D& circle);
	bool Overlaps(const Circle2D& circle);

	bool IsContains(Mypoint& p);

};