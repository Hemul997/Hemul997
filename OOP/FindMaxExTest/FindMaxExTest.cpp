// FindMaxExTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../FindMaxEx/FindMaxEx/FindMaxEx.h"

struct Athlete
{
	std::string name;
	unsigned short height;
	unsigned short weight;

};

struct Athletes_
{
	const Athlete first{ "first", 175, 70 };
	const Athlete second{ "second", 173, 69 };
	const Athlete third{ "third", 176, 70 };
	const Athlete fourth{ "fourth", 172, 67 };
	const Athlete fifth{ "fifth", 181, 77 };
	const Athlete sixth{ "sixth", 194, 87 };
	const Athlete seventh{ "seventh", 168, 60 };
	const Athlete eighth{ "eighth", 175, 73 };
	const Athlete ninth{ "ninth", 179, 79 };

	const std::vector<Athlete> athletes{ first, second, third, fourth, fifth, sixth, seventh, eighth, ninth };
};

bool IsHeightLess(const Athlete &first, const Athlete &second)
{
	return (first.height < second.height);
}

bool IsWeightLess(const Athlete &first, const Athlete &second)
{
	return (first.weight < second.weight);
}

BOOST_FIXTURE_TEST_SUITE(FindMax, Athletes_)

	BOOST_AUTO_TEST_CASE(can_find_max_element_by_copmarator_function)
	{
		Athlete maxValue;
		FindMaxEx(athletes, maxValue, IsHeightLess);
		BOOST_CHECK_EQUAL(maxValue.height, 194);
	}

	BOOST_AUTO_TEST_CASE(can_find_max_element_by_copmarator_function2)
	{
		Athlete maxValue;
		FindMaxEx(athletes, maxValue, IsWeightLess);
		BOOST_CHECK_EQUAL(maxValue.weight, 87);
	}

BOOST_AUTO_TEST_SUITE_END()