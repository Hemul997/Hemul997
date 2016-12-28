#include "stdafx.h"
#include "../CBodies/Cone.h"

struct Cone_
{
	const double expectedBaseRadius = 8;
	const double expectedHeight = 5;
	const double expectedDensity = 20;
	const double expectedVolume = (pow(expectedBaseRadius, 2) * M_PI) * expectedHeight / 3;
	const CCone cone;
	Cone_()
		:cone(expectedDensity, expectedBaseRadius, expectedHeight)
	{}
};

BOOST_FIXTURE_TEST_SUITE(Cone_test, Cone_)

	BOOST_AUTO_TEST_CASE(is_a_body)
	{
		BOOST_CHECK(static_cast<const CBody*>(&cone));
	}

	BOOST_AUTO_TEST_CASE(has_a_base_radius)
	{
		BOOST_CHECK_EQUAL(cone.GetBaseRadius(), expectedBaseRadius);
	}

	BOOST_AUTO_TEST_CASE(has_a_height)
	{
		BOOST_CHECK_EQUAL(cone.GetHeight(), expectedHeight);
	}

	BOOST_AUTO_TEST_CASE(has_a_density)
	{
		BOOST_CHECK_EQUAL(cone.GetDensity(), expectedDensity);
	}

	BOOST_AUTO_TEST_CASE(has_a_volume)
	{
		BOOST_CHECK_CLOSE_FRACTION(static_cast<const CBody &>(cone).GetVolume(), expectedVolume, 1e-7);
	}

	BOOST_AUTO_TEST_CASE(has_a_mass)
	{
		BOOST_CHECK_CLOSE_FRACTION(static_cast<const CBody &>(cone).GetMass(), expectedVolume * expectedDensity, 1e-7);
	}
	BOOST_AUTO_TEST_CASE(can_handle_negative_values)
	{
		BOOST_REQUIRE_THROW(CCone(-5, 2, 3), std::invalid_argument);
		BOOST_REQUIRE_THROW(CCone(5, -2, 3), std::invalid_argument);
		BOOST_REQUIRE_THROW(CCone(5, 2, -3), std::invalid_argument);
	}

BOOST_AUTO_TEST_SUITE_END()