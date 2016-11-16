// vector.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "WorkWithVector.h"
#include <numeric>
#include <functional>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <boost/range/algorithm/transform.hpp>
#pragma warning (push, 3)
#include <boost/phoenix.hpp>
#pragma warning (pop)

using namespace std;
using namespace std::placeholders;
using namespace boost::phoenix::placeholders;
using boost::transform;

vector<double> ReadVector(istream & input)
{
	vector<double> numbers(istream_iterator<double>(input), (istream_iterator<double>()));
	return numbers;
}

void SortVector(vector<double> & numbers)
{
	sort(numbers.begin(), numbers.end());
}

void ProcessVector(vector<double> & numbers)
{
	if (!numbers.empty())
	{
		auto minNumber = min_element(numbers.begin(), numbers.end());
		boost::transform(numbers, numbers.begin(), arg1 * (*minNumber));
	}
}

void OutVector(ostream & output, vector<double> & numbers)
{
	copy(numbers.begin(), numbers.end(), ostream_iterator<double>(output << fixed << setprecision(3), ", "));
}