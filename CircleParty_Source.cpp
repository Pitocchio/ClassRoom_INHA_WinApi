#include <iostream>
#include <cmath>
#include "CircleParty.h"


Circle2D::Circle2D() {}

Circle2D::~Circle2D() {}

Circle2D::Circle2D(POINT pos, double radius)
{
	m_pos = pos;
	m_radius = radius;
}

void Circle2D::PUSHBACK()
{
	VEC_Circle.push_back(this);
}