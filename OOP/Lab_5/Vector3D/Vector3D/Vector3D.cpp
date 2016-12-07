#include "stdafx.h"
#include "Vector3D.h"
#include <math.h>
#include <float.h>

#define _USE_MATH_DEFINES

const CVector3D CVector3D::operator+() const
{
	return *this;
}
CVector3D const CVector3D::operator-()const
{
	return CVector3D(-x, -y, -z);
}
CVector3D const CVector3D::operator+(CVector3D const & vector)const
{
	return CVector3D(x + vector.x, y + vector.y, z + vector.z);
}
CVector3D const CVector3D::operator-(CVector3D const & vector) const
{
	
	//return CVector3D(x - vector3.x, y - vector3.y, z - vector3.z);
	return *this + (-vector);
}

CVector3D & CVector3D::operator+=(CVector3D const & vector)
{
	return *this = *this + vector;
}
CVector3D& CVector3D::operator-=(CVector3D const & vector)
{
	return *this = *this - vector;
}
bool CVector3D::operator==(CVector3D const & vector) const
{
	return (x == vector.x) && (y == vector.y) && (z == vector.z);
}
bool CVector3D::operator!=(CVector3D const &vector)const
{
	return !(*this == vector);
}
double CVector3D::GetLength()const
{
	return sqrt(x*x + y*y + z*z);
}
void CVector3D::Normalize()
{
	if (GetLength() != 0)
	{
		x = x / GetLength();

		y = y / GetLength();

		z = z / GetLength();
	}
}
const CVector3D CVector3D::operator*(double scalar)const
{
	return CVector3D(x * scalar, y * scalar, z *scalar);
}

CVector3D  const operator*(double scalar, const CVector3D & vector)
{
	return CVector3D(scalar * vector.x, scalar * vector.y, scalar * vector.z);
}
CVector3D const CVector3D::operator/(double scalar)const
{
	if (scalar != 0)
	{
		return *this * (1 / scalar);
		//return CVector3D(x / scalar, y / scalar, z / scalar);
	}
	return CVector3D(x, y, z);
}
CVector3D& CVector3D::operator*=(double scalar)
{
	return *this = *this * scalar;
}
CVector3D const CVector3D::operator/=(double scalar)
{
	if (scalar != 0)
	{
		return *this *= 1 / scalar;
	}
	return *this;
}