#pragma once
#include <iostream>

class cVector3
{
private:
	double m_x, m_y, m_z;

public:
	cVector3();
	~cVector3();
	cVector3(double x, double y, double z);

	bool operator==(cVector3& vec);
	bool operator!=(cVector3& vec);

	cVector3 operator+(cVector3& vec);
	cVector3 operator-(cVector3& vec);
	cVector3 operator*(double d);
	cVector3 operator/(double d);

	friend std::ostream& operator<<(std::ostream& os, const cVector3& vec);

	double Length();
	cVector3 Normalize();

	static double Dot(cVector3& v1, cVector3& v2);
	static cVector3 Cross(cVector3& v1, cVector3& v2);
	static double Angle(cVector3& v1, cVector3& v2);

};