#pragma once
#include "Geometry_.h"

class Circle : public Geometry
{
public:
	Circle() { m_Radius = 0; };
	~Circle() {};
	Circle(POINT Pos, double Force, double radius);

public: // Get
	double Get_Radius() const { return m_Radius; }

public:// Update
	virtual void Render(HDC hdc) override;
	//virtual int Check_Collision_Wall() override;
	virtual void Move() override;

private: // Variables
	double m_Radius;
};