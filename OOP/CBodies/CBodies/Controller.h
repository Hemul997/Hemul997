#pragma once
#include <boost/noncopyable.hpp>
#include <functional>
#include "Body.h"

class CBody;

class CBodyController : boost::noncopyable
{
public:
	CBodyController(std::vector<std::shared_ptr<CBody>> &bodies, std::istream & input, std::ostream & output);

	bool HandleCommand();
	bool Help();
	void PrintBodies(std::vector<std::shared_ptr<CBody>> const &bodies);
	void FindBodyWithMaxMass(std::vector<std::shared_ptr<CBody>> const &bodies);
	void FindBodyWithMinWeightInWater(std::vector<std::shared_ptr<CBody>> const &bodies);

private:
	bool CreateCylinder(std::istream &args);
	bool CreateCone(std::istream &args);
	bool CreateSphere(std::istream &args);
	bool CreateParallelepiped(std::istream &args);
	bool CreateCompoundBody();
	using ActionMap = std::map<std::string, std::function<bool(std::istream & args)>>;

	std::vector<std::shared_ptr<CBody>> &m_bodies;
	std::istream & m_input;
	std::ostream & m_output;

	const ActionMap m_actionMap;
};