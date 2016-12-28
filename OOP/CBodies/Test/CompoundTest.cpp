#include "stdafx.h"

#define _USE_MATH_DEFINES
#include "../CBodies/Compound.h"
#include "../CBodies/Sphere.h"
#include "../CBodies/Parallelepiped.h"
#include "../CBodies/Cone.h"
#include "../CBodies/Cylinder.h"

struct Compound_
{
	CCompound compound;
	Compound_()
		: compound()
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(Compound, Compound_)

	BOOST_AUTO_TEST_CASE(is_a_body)
	{
		BOOST_CHECK(static_cast<const CBody*>(&compound));
	}

	struct EmptyCompound_ : Compound_
	{
		const double expectedDensity = 0;
		const double expectedVolume = 0;
		const double expectedMass = 0;
		const size_t expectedCountOfElements = 0;
	};
	BOOST_FIXTURE_TEST_SUITE(When_have_no_elements, EmptyCompound_)

	BOOST_AUTO_TEST_CASE(density_is_zero_by_default)
	{
		BOOST_CHECK_EQUAL(static_cast<const CBody &>(compound).GetDensity(), expectedDensity);
	}

	BOOST_AUTO_TEST_CASE(volume_is_zero_by_default)
	{
		BOOST_CHECK_EQUAL(static_cast<const CBody &>(compound).GetVolume(), expectedVolume);
	}

	BOOST_AUTO_TEST_CASE(mass_is_zero_by_default)
	{
		BOOST_CHECK_EQUAL(static_cast<const CBody &>(compound).GetMass(), expectedMass);
	}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_CASE(can_added_child_body)
	{
		compound.AddBody(std::make_shared<CCone>(CCone(4, 23, 1)));
		compound.AddBody(std::make_shared<CCylinder>(CCylinder(654, 2, 32)));
		compound.AddBody(std::make_shared<CCompound>(CCompound()));
		BOOST_CHECK(compound.GetCompoundSize() == 3);
	}

BOOST_AUTO_TEST_SUITE_END()