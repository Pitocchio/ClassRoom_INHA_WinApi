#pragma once
#include "framework.h"
#include <cmath>
#include <vector>
using namespace std;

class Object;
class Geometry;
class Circle;
class Rectangle;
class Star;

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
		Geometry(POINT Pos, double Speed);

		// Get 
		POINT Get_Pos() const { return m_Pos; }
		double Get_Speed() const { return m_Force; }

		bool Check_Collision_Wall();
		void Set_Pos();
};

class Circle : public Geometry
{
	private: 
		double m_Radius;

	public: 
		// Ctor, Dtor
		Circle() { m_Radius = 0; };
		~Circle() {};
		Circle(POINT Pos, double Force, double radius);

		// �������� ����� ���� �����Լ��� �����, �ڽ� Ŭ�������� �޾Ƽ� ���� �� ��� 


		// Get
		double Get_Radius() const { return m_Radius; }
};
class ObjectManager
{
	private:
		vector<Geometry*> m_vecpArr;

		vector<Circle*> m_vecpCircle;
		

		vector<Geometry*>m_vpGeometry;
		vector<Circle*> m_vpCircle;
		vector<Square*> m_vpSquare;
		vector<Star*> m_vpStar;

		
		//ector<Geometry*> m_arrvecObj[(UINT)GROUP_TYPE::END];

	public :
		ObjectManager() {}
	
		~ObjectManager() {}
		// ����
		/*void Render()
		{
			for (vector<Geometry*>::iterator iter = m_vecpArr.begin(); iter != m_vecpArr.end(); ++iter)
				(*iter).render();
		}*/
		void circle_test(POINT pos) { Circle* t = new Circle(pos, 10, 30);  std::cout << "new!\n";  m_vecpArr.push_back(t); } // �Լ����� ��ü�� ����
		
		// �Ҵ� ���������� ��!!!!
};

class CircleManager : public ObjectManager
{
	private:
		vector<Circle> m_Vector;
		//RECT m_Rc;

	public:
		// Ctor, Dtor
		CircleManager(){}
		~CircleManager() {}

		// Get
		vector<Circle> Get_Vector() const { return m_Vector; }


		void PushBack(Circle c) { m_Vector.push_back(c); }
		void Update();

};

class Square : public Geometry
{

};

class Star : public Geometry
{

};

