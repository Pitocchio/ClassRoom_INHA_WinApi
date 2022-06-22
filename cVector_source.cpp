#include "cVector.h"
#include <cmath>

#define PI 3.141592

cVector3::cVector3()
{
	m_x = m_y = m_z = 0;
}

cVector3::~cVector3()
{

}

cVector3::cVector3(double x, double y, double z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

double cVector3::Length()
{
	double size;

	size = abs(sqrt(pow(m_x, 2) + pow(m_y, 2) + pow(m_z, 2)));
	return size;
}

cVector3 cVector3::Normalize()
{
	double size = abs(Length());

	cVector3 temp(m_x / size, m_y / size, m_z / size);
	return temp;
}

std::ostream& operator<<(std::ostream& os, const cVector3& vec)
{
	os << "(x, y, z) = " << vec.m_x << " " << vec.m_y << " " << vec.m_z << "\n";

	return os;
}

bool cVector3::operator==(cVector3& vec)
{
	if (((m_x == vec.m_x) && (m_y == vec.m_y)) && (m_z == vec.m_z))
		return true;
	else return false;
}

bool cVector3::operator!=(cVector3& vec)
{
	if (((m_x != vec.m_x) || (m_y != vec.m_y)) || (m_z != vec.m_z))
		return true;
	else return false;
}

cVector3 cVector3::operator+(cVector3& vec)
{
	cVector3 temp(m_x + vec.m_x, m_y + vec.m_y, m_z + vec.m_z);
	return temp;
}

cVector3 cVector3::operator-(cVector3& vec)
{
	cVector3 temp(m_x - vec.m_x, m_y - vec.m_y, m_z - vec.m_z);
	return temp;
}

cVector3 cVector3::operator*(double d)
{
	cVector3 temp(m_x * d, m_y * d, m_z * d);
	return temp;
}

cVector3 cVector3::operator/(double d)
{
	cVector3 temp(m_x / d, m_y / d, m_z / d);
	return temp;
}

double cVector3::Dot(cVector3& v1, cVector3& v2)
{
	return (v1.m_x * v2.m_x) + (v1.m_y * v2.m_y) + (v1.m_z * v2.m_z);
}

cVector3 cVector3::Cross(cVector3& v1, cVector3& v2)
{
	cVector3 temp((v1.m_y * v2.m_z) - (v1.m_z * v2.m_y), (v1.m_z * v2.m_x) - (v1.m_x * v2.m_z), (v1.m_x * v2.m_y) - (v1.m_y * v2.m_x));
	return temp;
}

double cVector3::Angle(cVector3& v1, cVector3& v2)
{
	double theta = acos(Dot(v1, v2) / (v1.Length() * v2.Length())) * (180 / PI);

	return theta;
}