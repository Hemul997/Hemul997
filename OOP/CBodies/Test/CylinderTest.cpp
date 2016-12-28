#include "stdafx.h"
#include "../CBodies/Cylinder.h"

struct Cylinder_
{
	const double expectedBaseRadius = 7;
	const double expectedHeight = 20;
	const double expectedDensity = 3;
	const double expectedVolume = (pow(expectedBaseRadius, 2) * M_PI) * expectedHeight;
	const CCylinder cylinder;
	Cylinder_()
		:cylinder(expectedDensity, expectedBaseRadius, expectedHeight)
	{}
};

BOOST_FIXTURE_TEST_SUITE(Cylinder_test, Cylinder_)

	BOOST_AUTO_TEST_CASE(is_a_body)
	{
		BOOST_CHECK(static_cast<const CBody*>(&cylinder));
	}

	BOOST_AUTO_TEST_CASE(has_a_base_radius)
	{
		BOOST_CHECK_EQUAL(cylinder.GetBaseRadius(), expectedBaseRadius);
	}

	BOOST_AUTO_TEST_CASE(has_a_height)
	{
		BOOST_CHECK_EQUAL(cylinder.GetHeight(), expectedHeight);
	}

	BOOST_AUTO_TEST_CASE(has_a_density)
	{
		BOOST_CHECK_EQUAL(cylinder.GetDensity(), expectedDensity);
	}

	BOOST_AUTO_TEST_CASE(has_a_volume)
	{
		BOOST_CHECK_CLOSE_FRACTION(static_cast<const CBody &>(cylinder).GetVolume(), expectedVolume, 1e-7);
	}

	BOOST_AUTO_TEST_CASE(has_a_mass)
	{
		BOOST_CHECK_CLOSE_FRACTION(static_cast<const CBody &>(cylinder).GetMass(), expectedVolume * expectedDensity, 1e-7);
	}

	BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
	{
		std::ofstream file;
		file.open("output.txt");
		file << static_cast<const CBody &>(cylinder).ToString();
		const std::string expectedString = "Cylinder:\n\tDensity: 3\n\tVolume: 3078.76\n\tMass: 9236.28\n\tBaseRadius: 7\n\tHeight: 20\n";
		BOOST_CHECK_EQUAL(static_cast<const CBody &>(cylinder).ToString(), expectedString);
	}
	BOOST_AUTO_TEST_CASE(can_handle_negative_values)
	{
		BOOST_REQUIRE_THROW(CCylinder(-5, 2, 3), std::invalid_argument);
		BOOST_REQUIRE_THROW(CCylinder(5, -2, 3), std::invalid_argument);
		BOOST_REQUIRE_THROW(CCylinder(5, 2, -3), std::invalid_argument);
	}

BOOST_AUTO_TEST_SUITE_END()