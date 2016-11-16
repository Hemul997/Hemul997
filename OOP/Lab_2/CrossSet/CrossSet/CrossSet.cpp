// CrossSet.cpp : Defines the entry point for the console application.
//
#include "CrossSet.h"

using namespace std;

set<int> CrossSet(set<int> const& set1, set<int> const& set2)
{
	set<int> set3;
	set_intersection(set1.begin(), set1.end(),
		set2.begin(), set2.end(),
		inserter(set3, set3.begin()));
	return(set3);
}
void PrintSet(set<int> const& set)
{
	copy(set.begin(), set.end(), ostream_iterator<int>(cout, " "));
	cout << std::endl;
}
int SumOfNum(int i)
{
	int sum = 0;
	while (i > 0)
	{
		sum += i % 10;
		i /= 10;
	}
	return sum;
}
void InsertToSets(set<int> & set1, set<int> & set2, int num)
{
	for (auto i = 1; i <= num; ++i)
	{
		int sum = SumOfNum(i);
		if (i % sum == 0)
		{
			set1.insert(i);
		}
		if (sum % 2 == 0)
		{
			set2.insert(i);
		}
	}
}
