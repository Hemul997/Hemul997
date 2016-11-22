#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <boost/range/algorithm/transform.hpp>
#include <boost/algorithm/string.hpp> 

typedef std::map <std::wstring, int> CountWordsMap;
using namespace std;

void LowerCase(wstring & line);
void CountWord(wistream & args, CountWordsMap & countWords);
void PrintMap(CountWordsMap const & store);