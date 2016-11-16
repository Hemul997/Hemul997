// CountWord.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "CountWord.h"

using boost::transform;

void LowerCase(string & line)
{
	boost::algorithm::to_lower(line);
}
void CountWord(istream & args, CountWordsMap & countWords)
{
	string line;
	while(args >> line)
	{
		LowerCase(line);
		countWords[line]++;
	}
}
void PrintMap(CountWordsMap const & store)
{
	for (auto i = store.begin(); i != store.end(); ++i)
	{
		cout << i->first << "->" << i->second << endl;
	}
}

