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

	//���� ��� arr[10][10]�� arr_copy[10][10]�� �ű�ٰ� ����
	//�׷��� copy(&arr[0][0], &arr[0][0] + 100, &arr_copy[0][0])�� ����ϸ� �ȴ�.

public:// Update
	virtual void Render(HDC hdc) override;
	virtual void Move() override;
	virtual void CheckCollisionWall(RECT rc) override;

private: // Variables
	
	double m_Height;
	double m_Width;
	POINT m_Point[4];
};