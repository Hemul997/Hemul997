#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <boost/range/algorithm/transform.hpp>
#include <boost/algorithm/string.hpp> 

typedef std::map <std::string, int> CountWordsMap;
using namespace std;

void LowerCase(string & line);
void CountWord(istream & args, CountWordsMap & countWords);
void PrintMap(CountWordsMap const & store);