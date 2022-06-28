#include "Geometry_.h"
#include <ctime>
#include <cmath>

Geometry::Geometry() 
{ 
	//m_Pos = { 0 }; 
	m_Distance = 0;
	//m_IsCollisionWall = 0;
	m_IsCollisionObj = 0;
	m_CollisionObj = NULL;
	srand(time(NULL)); // 근데 왜 이거 여기다 두면 효과 있는 거야?
};

Geometry::~Geometry()
{

}

Geometry::Geometry(POINT pos, double dis)
{
	m_Pos.x = pos.x;
	m_Pos.y = pos.y;
	m_Distance = dis;
	m_Angle = rand() % 360;



	m_lookVec.x = cosf(PI / 180 * m_Angle);
	m_lookVec.y = sinf(PI / 180 * m_Angle);

	double distemp = (double)sqrt(pow(m_lookVec.x, 2) + pow(m_lookVec.y, 2));
	
	m_lookVec.x = m_lookVec.x / distemp;
	m_lookVec.y = m_lookVec.y / distemp;


	
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

