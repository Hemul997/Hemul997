#pragma once
#pragma once
#include "Body.h"

class CCompound : public CBody
{
public:
	CCompound();
	bool AddBody(std::shared_ptr<CBody> const& element);
	double GetMass() const override;
	double GetVolume() const override;
	size_t GetCompoundSize() const;

protected:
	void AddProperties(std::ostream& strm) const override;

private:
	std::vector<std::shared_ptr<CBody>> m_elements;
	void SetDensity();
};