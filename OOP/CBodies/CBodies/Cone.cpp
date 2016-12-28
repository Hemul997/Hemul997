#include "stdafx.h"
#include "Cone.h"


CCone::CCone(double density, double radius, double height) :
	CBody("Cone", density)
{
	if (radius <= 0 || height <= 0)
	{
		throw std::invalid_argument("Height or radius must not be negative\n");
	}
	m_radius = radius;
	m_height = height;
}

double CCone::GetBaseRadius() const
{
	return m_radius;
}

double CCone::GetHeight() const
{
	return m_height;
}

double CCone::GetVolume() const
{
	return (pow(m_radius, 2) * M_PI) * m_height / 3;
}


void CCone::AddProperties(std::ostream & strm) const
{
	strm << "\tHeight = " << GetHeight() << std::endl
		<< "\tRadius = " << GetBaseRadius() << std::endl;
}