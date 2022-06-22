#pragma once
#include "framework.h"
#include <vector>

class Circles_manager
{
	public:
		Circles_manager();
		~Circles_manager();
		std::vector <Circle2D> VEC_Circle;
};

class Circle2D : public Circles_manager
{
	private: POINT m_pos;
			 double m_radius;

	public:
			Circle2D();
			~Circle2D();
			Circle2D(POINT pos, double radius);
			void PUSHBACK();
};