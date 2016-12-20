// CountWord.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "CountWord.h"
#include <cmath>

using boost::transform;

void LowerCase(wstring & line)
{
	boost::algorithm::to_lower(line);
}
void CountWord(wistream & args, CountWordsMap & countWords)
{
	wstring line;
	while(args >> line)
	{
		LowerCase(line);
		++countWords[line];
	}
}
void CountNumbers(istream & args, CountNumbersMap & countWords)
{
	int line;
	while (args >> line)
	{
		++countWords[line];
	}
}
float CountMap(CountNumbersMap const &store)
{
	float count = 0;
	for (auto i = store.begin(); i != store.end(); ++i)
	{
		count += (i->first * i->second);
	}
	return count;
}
double Disp(CountNumbersMap const &store, float count)
{
	double disp = 0;
	for (auto i = store.begin(); i != store.end(); ++i)
	{
		disp += pow((i->first - count),2) * i->second;
	}
	return disp;
}
void PrintMap(CountNumbersMap const &store)
{
	for (auto i = store.begin(); i != store.end(); ++i)
	{
		cout << i->first << "->" << i->second << endl;
	}
}
void PrintMap(CountWordsMap const & store)
{
	for (auto i = store.begin(); i != store.end(); ++i)
	{
		wcout << i->first << "->" << i->second << endl;
	}
}

