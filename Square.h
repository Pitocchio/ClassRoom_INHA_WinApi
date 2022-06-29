#pragma once
#include "Geometry_.h"

class Square : public Geometry
{
public:
	Square();
	~Square();
	Square(POINT Pos, double Force, double Height, double Width);

public: // Get
	double Get_Height() const { return m_Height; }
	double Get_Width() const { return m_Width; }
	//POINT Get_Point() const { return *m_Point; } 

public: // Set
	void Set_Height(double Height) { m_Height = Height; }
	void Set_Width(double Width) { m_Width = Width; }
	//void Set_Point(POINT* point[]) { copy(point, point + 3, m_Point); }

	//예를 들어 arr[10][10]을 arr_copy[10][10]에 옮긴다고 하자
	//그러면 copy(&arr[0][0], &arr[0][0] + 100, &arr_copy[0][0])를 사용하면 된다.

public:// Update
	virtual void Render(HDC hdc) override;
	virtual void Move() override;
	virtual void CheckCollisionWall(RECT rc) override;

private: // Variables
	
	double m_Height;
	double m_Width;
	POINT m_Point[4];
};