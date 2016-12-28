#include "stdafx.h"
#include "../Cbodies/Sphere.h"

struct Sphere_
{
	const double expectedRadius = 10;
	const double expectedDensity = 10;
	const double expectedVolume = (pow(expectedRadius, 3) * M_PI) * 4 / 3;
	const CSphere sphere;
	Sphere_()
		:sphere(expectedDensity, expectedRadius)
	{}
};

BOOST_FIXTURE_TEST_SUITE(Sphere_test, Sphere_)

	BOOST_AUTO_TEST_CASE(is_a_body)
	{
		BOOST_CHECK(static_cast<const CBody*>(&sphere));
	}

	BOOST_AUTO_TEST_CASE(has_a_radius)
	{
		BOOST_CHECK_EQUAL(sphere.GetRadius(), expectedRadius);
	}

	BOOST_AUTO_TEST_CASE(has_a_density)
	{
		BOOST_CHECK_EQUAL(sphere.GetDensity(), expectedDensity);
	}

	BOOST_AUTO_TEST_CASE(has_a_volume)
	{
		BOOST_CHECK_CLOSE_FRACTION(static_cast<const CBody &>(sphere).GetVolume(), expectedVolume, 1e-7);
	}

	BOOST_AUTO_TEST_CASE(has_a_mass)
	{
		BOOST_CHECK_CLOSE_FRACTION(static_cast<const CBody &>(sphere).GetMass(), expectedVolume * expectedDensity, 1e-7);
	}

	BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
	{
		const std::string expectedString = "Sphere:\n\tDensity: 10\n\tVolume: 4188.79\n\tMass: 41887.9\n\tRadius: 10\n";
		BOOST_CHECK_EQUAL(static_cast<const CBody &>(sphere).ToString(), expectedString);
	}
	BOOST_AUTO_TEST_CASE(can_handle_negative_values)
	{
		BOOST_REQUIRE_THROW(CSphere(0, -5), std::invalid_argument);
	}

BOOST_AUTO_TEST_SUITE_END()