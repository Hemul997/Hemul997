#include "stdafx.h"
#include "Sphere.h"

CSphere::CSphere(double density, double radius)
	:CBody("Sphere", density)
{
	if (radius < 0)
	{
		throw std::invalid_argument("Radius must not be negative\n");
	}
	m_radius = radius;
}

double CSphere::GetRadius() const
{
	return m_radius;
}

double CSphere::GetVolume() const
{
	return (pow(m_radius, 3) * M_PI) * 4 / 3;
}

void CSphere::AddProperties(std::ostream & strm) const
{
	strm << "\tRadius: " << GetRadius() << std::endl;
}