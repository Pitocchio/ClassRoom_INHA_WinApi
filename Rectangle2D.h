#pragma once

class Mypoint;

class Rectangle2D
{
private: double m_x, m_y, m_width, m_height;

public:

	Rectangle2D();
	~Rectangle2D();
	Rectangle2D(double x, double y, double width, double height);

	double Get_X();
	double Get_Y();
	double Get_WIDTH();
	double GET_HEIGHT();

	void Set_X(double x);
	void Set_Y(double y);
	void Set_WIDHT(double width);
	void Set_HEIGHT(double height);

	double Get_Area();
	double GetPerimeter();

	bool IsContains(double x, double y);
	bool IsContains(const Rectangle2D& r);
	bool IsOverlaps(const Rectangle2D& r);

	bool IsContains(Mypoint& p);

};