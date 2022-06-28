#include "Geometry_.h"
#include <ctime>
#include <cmath>

Geometry::Geometry() 
{ 
	m_Pos = { 0 }; 
	m_Force = 0; 
	//m_IsCollisionWall = 0;
	m_IsCollisionObj = 0;
	m_CollisionObj = NULL;
	srand(time(NULL)); // 근데 왜 이거 여기다 두면 효과 있는 거야?
};

Geometry::~Geometry()
{

}

Geometry::Geometry(POINT Pos, double Force)
{
	m_Pos = Pos;
	m_Force = Force;
	m_Theta = rand() % 360;
}
void Geometry::Set_IsCollisionObj(bool b)
{
	m_IsCollisionObj = b;
}
void Geometry::Set_CollisionObj(Geometry* obj)
{
	m_CollisionObj = obj;
}
bool Geometry::Peak_IsCollision()
{
	if (m_CollisionObj != NULL)
		return true;
	else
		return false;
}
void Geometry::Reset_CollisionObj()
{
	m_CollisionObj = NULL;
}

