#pragma once
#include "Body.h"
class CSphere final :
	public CBody
{
public:
	CSphere(double density, double radius);
	double GetRadius()const;
	double GetVolume() const override;

protected:
	void AddProperties(std::ostream & strm) const override;

private:
	double m_radius;
};