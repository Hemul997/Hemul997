#include "stdafx.h"
#include "Compound.h"

CCompound::CCompound()
	: CBody("Compound")
{
}

bool CCompound::AddBody(std::shared_ptr<CBody> const& element)
{
	bool isAdded = true;
	if (this == element.get())
	{
		isAdded = false;
	}

	if (isAdded)
	{
		m_elements.push_back(element);
		SetDensity();
	}
	return isAdded;
}

double CCompound::GetMass() const
{
	double mass = 0;
	for (auto element : m_elements)
	{
		mass += element->GetMass();
	}
	return mass;
}

double CCompound::GetVolume() const
{
	double volume = 0;
	for (auto element : m_elements)
	{
		volume += element->GetVolume();
	}
	return volume;
}

size_t CCompound::GetCompoundSize() const
{
	return m_elements.size();
}

void CCompound::AddProperties(std::ostream& strm) const
{
	strm << "> Compound body have " << std::to_string(GetCompoundSize()) << " elements:\n";
	for (auto element : m_elements)
	{
		strm << "\t" << element->ToString() << "\n";
	}
}

void CCompound::SetDensity()
{
	if (GetVolume() == 0)
	{
		m_density = 0;
	}
	else
	{
		m_density = GetMass() / GetVolume();
	}
}