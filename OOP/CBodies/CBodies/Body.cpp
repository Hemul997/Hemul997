#include "stdafx.h"
#include "Body.h"
#include <iomanip>

CBody::CBody(const std::string& type)
	:m_type(type)
	, m_density(0)
{
}
CBody::CBody(const std::string & type, double density) :
	m_type(type)
{
	if (density <= 0)
	{
		throw std::invalid_argument("Density must not be negative\n");
	}
	m_density = density;
}

double CBody::GetMass()const
{
	return GetDensity() * GetVolume();
}

std::string CBody::ToString()const
{
	std::ostringstream strm;
	strm << m_type << ":\n" 
		<< "\tDensity: " << GetDensity() << std::endl
		<< "\tVolume: " << GetVolume() << std::endl
		<< "\tMass: " << GetMass() << std::endl;
	AddProperties(strm);
	return strm.str();
}



double CBody::GetDensity()const
{
	return m_density;
}