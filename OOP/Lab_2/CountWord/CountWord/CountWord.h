#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <boost/range/algorithm/transform.hpp>
#include <boost/algorithm/string.hpp> 

typedef std::map <std::wstring, int> CountWordsMap;
typedef std::map <int, int> CountNumbersMap;
using namespace std;

void LowerCase(wstring & line);
void CountWord(wistream & args, CountWordsMap & countWords);
void PrintMap(CountWordsMap const & store);
void PrintMap(CountNumbersMap const &store);
void CountNumbers(istream & args, CountNumbersMap & countWords);
float CountMap(CountNumbersMap const &store);
double Disp(CountNumbersMap const &store, float count);