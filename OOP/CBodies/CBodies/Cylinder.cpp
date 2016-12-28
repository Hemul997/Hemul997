#include "stdafx.h"
#include "Cylinder.h"


CCylinder::CCylinder(double density, double radius, double height) :
	CBody("Cylinder", density)
{
	if (radius <= 0 || height <= 0)
	{
		throw std::invalid_argument("Height or radius must not be negative\n");
	}
	m_height = height;
	m_radius = radius;
}

double CCylinder::GetBaseRadius() const
{
	return m_radius;
}

double CCylinder::GetHeight() const
{
	return m_height;
}

double CCylinder::GetVolume() const
{
	return (pow(m_radius, 2) * M_PI) * GetHeight();
}

void CCylinder::AddProperties(std::ostream & strm) const
{
	
		strm << "\tBaseRadius: " << GetBaseRadius() << std::endl
			<< "\tHeight: " << GetHeight() << std::endl;
}