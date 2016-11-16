// CrossSetsTests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\CrossSet\CrossSet.h"

using namespace std;
set<int> DiffersOfSet(set<int> const &firstSet, set<int> const &secondSet)
{
	set<int> diff;
	set_difference(firstSet.begin(), firstSet.end(), secondSet.begin(), secondSet.end(),
		std::inserter(diff, diff.begin()));
	return diff;
}
BOOST_AUTO_TEST_SUITE(process_sets_function)

	BOOST_AUTO_TEST_CASE(makes_empty_set_from_two_empty_sets)
	{
		set<int> emptySet1;
		set<int> emptySet2;
		set<int> resultSet;
		resultSet = CrossSet(emptySet1, emptySet2);
		BOOST_CHECK(resultSet.empty());
	}
	BOOST_AUTO_TEST_CASE(not_empty_sets)
	{
		set<int> firstSet = { 1, 2, 3, 4, 5 };
		set<int> secondSet = { 2, 4, 5 ,8, 3 };
		set<int> testSet = { 2, 3, 4, 5 };
		set<int> resultSet;
		set<int> diff;
		resultSet = CrossSet(firstSet, secondSet);
		diff = DiffersOfSet(testSet, resultSet);
		BOOST_CHECK(diff.empty());
	}
	BOOST_AUTO_TEST_CASE(insert_to_sets)
	{
		int num = 24;
		set<int> firstSet;
		set<int> secondSet;
		set<int> testFirstSet = { 2, 4, 6, 8, 20, 24 };
		set<int> testSecondSet = { 2, 3, 4, 5 };
		set<int> resultSet;
		set<int> diff;
		InsertToSets(firstSet, secondSet, num);
		resultSet = CrossSet(firstSet, secondSet);
		diff = DiffersOfSet(testFirstSet, resultSet);
		BOOST_CHECK(diff.empty());
		diff = DiffersOfSet(testSecondSet, resultSet);
		BOOST_CHECK(!diff.empty());
	}
BOOST_AUTO_TEST_SUITE_END()