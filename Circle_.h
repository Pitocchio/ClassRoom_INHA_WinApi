#pragma once
#include "Geometry_.h"

class Circle : public Geometry
{
private:
	double m_Radius;

public:
	// Ctor, Dtor
	Circle() { m_Radius = 0; };
	~Circle() {};
	Circle(POINT Pos, double Force, double radius);

	// Get
	double Get_Radius() const { return m_Radius; }

	// Update
	virtual void Render(HDC hdc) override;
	virtual int Check_Collision_Wall() override;
	virtual void Move() override;

};