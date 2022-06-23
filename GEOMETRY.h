#pragma once
#include "framework.h"

class Geometry
{
	private: 
		POINT m_Pos;
		double m_Speed;
		double m_Look;

	/*protected:
		std::vector<Circle> vCircle;*/

	public:
		Geometry() { m_Pos = { 0 }; m_Speed = m_Look = 0; };
		~Geometry() {};
		Geometry(POINT Pos, double Speed, double Look);

		POINT Get_Pos() const { return m_Pos; }
		double Get_Speed() const { return m_Speed; }
		double Get_Look() const { return m_Look; }
		

};

class Circle : public Geometry
{
	private: 
		double m_Radius;

	public: 
		Circle() { m_Radius = 0; };
		~Circle() {};
		Circle(POINT Pos, double Speed, double Look, double radius);

		double Get_Radius() const { return m_Radius; }


		//void PushBack() { vCircle.push_back(*this); }
		
};

class Square : public Geometry
{

};

class Star : public Geometry
{

};