#include "stdafx.h"
#include "../CBodies/Parallelepiped.h"

struct Parallelepiped_
{
	const double expectedWidth = 8;
	const double expectedHeight = 5;
	const double expectedDepth = 2;
	const double expectedDensity = 20;
	const double expectedVolume = expectedWidth * expectedHeight * expectedDepth;
	const CParallelepiped sparallelepiped;
	Parallelepiped_()
		:sparallelepiped(expectedDensity, expectedWidth, expectedHeight, expectedDepth)
	{}
};

BOOST_FIXTURE_TEST_SUITE(Parallelepiped_test, Parallelepiped_)

	BOOST_AUTO_TEST_CASE(is_a_body)
	{
	CParallelepiped paral(expectedDensity, expectedWidth, expectedHeight, expectedDepth);
	BOOST_CHECK(static_cast<const CBody*>(&sparallelepiped));
	}

	BOOST_AUTO_TEST_CASE(has_a_width)
	{
	BOOST_CHECK_EQUAL(sparallelepiped.GetWidth(), expectedWidth);
	}

	BOOST_AUTO_TEST_CASE(has_a_height)
	{
	BOOST_CHECK_EQUAL(sparallelepiped.GetHeight(), expectedHeight);
	}

	BOOST_AUTO_TEST_CASE(has_a_depth)
	{
	BOOST_CHECK_EQUAL(sparallelepiped.GetDepth(), expectedDepth);
	}

	BOOST_AUTO_TEST_CASE(has_a_density)
	{
	BOOST_CHECK_EQUAL(sparallelepiped.GetDensity(), expectedDensity);
	}

	BOOST_AUTO_TEST_CASE(has_a_volume)
	{
	BOOST_CHECK_CLOSE_FRACTION(static_cast<const CBody &>(sparallelepiped).GetVolume(), expectedVolume, 1e-7);
	}

	BOOST_AUTO_TEST_CASE(has_a_mass)
	{
	BOOST_CHECK_CLOSE_FRACTION(static_cast<const CBody &>(sparallelepiped).GetMass(), expectedVolume * expectedDensity, 1e-7);
	}
	BOOST_AUTO_TEST_CASE(can_handle_negative_values)
	{
	BOOST_REQUIRE_THROW(CParallelepiped(1, -5, 2, 3), std::invalid_argument);
	BOOST_REQUIRE_THROW(CParallelepiped(1, 5, -2, 3), std::invalid_argument);
	BOOST_REQUIRE_THROW(CParallelepiped(1, 5, 2, -3), std::invalid_argument);
	}

BOOST_AUTO_TEST_SUITE_END()