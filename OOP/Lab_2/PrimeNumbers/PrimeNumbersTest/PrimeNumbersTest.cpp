// PrimeNumbersTest.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "../PrimeNumbers/PrimeNumbers.h"

BOOST_AUTO_TEST_SUITE(Set_processor)

BOOST_AUTO_TEST_CASE(can_create_empty_set)
{
	std::set<int> referenceSet = {};
	BOOST_CHECK(GeneratePrimeNumbersSet(0) == referenceSet);
}

BOOST_AUTO_TEST_CASE(can_create_a_set_to_user_upper_bound)
{
	std::set<int> referenceSet = { 2, 3, 5, 7 };
	BOOST_CHECK(GeneratePrimeNumbersSet(10) == referenceSet);
}



BOOST_AUTO_TEST_SUITE_END()
