#pragma once
#include "Circle2D.h"
#include "Rectangle2D.h"

class Circle2D;
class Rectangle2D;


class Mypoint
{
private:
	double m_x, m_y;

public:
	Mypoint();
	~Mypoint();
	Mypoint(double x, double y);

	double Get_x();
	double Get_y();

	double Cal_Distance(Mypoint& p);

	friend bool Circle2D::IsContains(Mypoint& p);

	friend bool Rectangle2D::IsContains(Mypoint& p);
};


