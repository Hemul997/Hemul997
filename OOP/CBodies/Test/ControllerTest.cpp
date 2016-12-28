#include "stdafx.h"
#include "../CBodies/Controller.h"

using namespace std;
using boost::optional;
using boost::none;


struct ControllerDependencies
{
	vector<shared_ptr<CBody>> bodies;
	stringstream input;
	stringstream output;
};

struct ControllerFixture : ControllerDependencies
{
	CBodyController controller;

	ControllerFixture()
		:controller(bodies, input, output)
	{
	}

	void CheckCommandHandling(const string& command, const string& expectedOutput)
	{
		output = stringstream();
		input = stringstream();
		BOOST_CHECK(input << command);
		controller.HandleCommand();
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}
};

BOOST_FIXTURE_TEST_SUITE(Controller, ControllerFixture)

	BOOST_AUTO_TEST_CASE(can_handle_sphere_with_two_arguments)
	{
		const string expectedOutput = "Sphere:\n\tDensity: 10\n\tVolume: 0\n\tMass: 0\n\tRadius: 0\n";
		CheckCommandHandling("Sphere 10 0", "");
		BOOST_CHECK((*bodies.begin())->GetDensity() == 10);
		BOOST_CHECK((*bodies.begin())->ToString() == expectedOutput);
	}

	BOOST_AUTO_TEST_CASE(can_handle_invalid_inputs)
	{
		CheckCommandHandling("Sphere", "Invalid count of arguments\nUsage: Sphere <density> <radius>\n");
		CheckCommandHandling("Sphere 10", "Invalid count of arguments\nUsage: Sphere <density> <radius>\n");
		CheckCommandHandling("Sphere 10 10 10", "");
	}

	BOOST_AUTO_TEST_CASE(can_handle_negative_arguments)
	{
		CheckCommandHandling("Sphere 5 -10", "Radius must not be negative\n");
		CheckCommandHandling("Sphere -5 10", "Density must not be negative\n");
		CheckCommandHandling("Sphere -5 -10", "Density must not be negative\n");
		BOOST_CHECK(bodies.empty());
	}

	BOOST_AUTO_TEST_CASE(can_handle_ivalid_commands)
	{
		CheckCommandHandling("Hello!", "> Invalid command!\n");
		BOOST_CHECK(bodies.size() == 0);
	}

BOOST_AUTO_TEST_SUITE_END()