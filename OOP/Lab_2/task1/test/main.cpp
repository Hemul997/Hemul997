#include "stdafx.h"
#include "..\vector\vector\WorkWithVector.h"

using namespace std;

bool VectorsAreEqual(vector<double> const& x, vector<double> const& y)
{
	return x == y;
}


BOOST_AUTO_TEST_SUITE(process_vector_function)

	BOOST_AUTO_TEST_CASE(makes_empty_vector_from_empty_vector)
	{
		vector<double> emptyVector;
		ProcessVector(emptyVector);
		BOOST_CHECK(emptyVector.empty());
	}

	BOOST_AUTO_TEST_CASE(not_empty_vector)
	{
		vector<double> numbers = { 5.5, 8.0, 2};
		ProcessVector(numbers);
		BOOST_CHECK(VectorsAreEqual(numbers, { (5.5 * 2), (8 * 2), (2 * 2) }));
	}

	BOOST_AUTO_TEST_CASE(zeros_in_vector)
	{
		vector<double> numbers = { 5.5, 8, 0};
		ProcessVector(numbers);
		BOOST_CHECK(VectorsAreEqual(numbers, { (5.5 * 0), (8.0 * 0), (0 * 0) }));
	}

	BOOST_AUTO_TEST_CASE(sort_vector)
	{
		vector<double> numbers = { 5.5, 8, 2 };
		ProcessVector(numbers);
		SortVector(numbers);
		BOOST_CHECK(VectorsAreEqual(numbers, { (2 * 2) , (5.5 * 2), (8 * 2) }));
	}
BOOST_AUTO_TEST_SUITE_END()