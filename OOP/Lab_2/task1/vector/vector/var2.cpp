// task1.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "WorkWithVector.h"
using namespace std;

int main()
{
	vector<double> numbers = ReadVector(cin);
	ProcessVector(numbers);
	SortVector(numbers);
	OutVector(cout, numbers);
	return 0;
}