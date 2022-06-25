#pragma once
#include "framework.h"
#include <iostream>
using namespace std;

class Geometry
{
	private:
		POINT m_Pos;
		double m_Force;
		double m_Theta;

	public:
		// Ctor, Dtor
		Geometry() { m_Pos = { 0 }; m_Force = 0; };
		~Geometry() {};
		Geometry (POINT Pos, double Speed);

		// Get 
		POINT Get_Pos() const { return m_Pos; }
		double Get_Speed() const { return m_Force; }

		// Update
		virtual void Render(HDC hdc) = 0;

		virtual int Check_Collision_Wall() = 0;

		void Move();

		//virtual void Move() = 0;
};