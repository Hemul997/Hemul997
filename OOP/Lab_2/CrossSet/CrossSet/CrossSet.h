#pragma once
#include <iostream>
#include <set>
#include <algorithm>
#include <iterator>
#include "stdafx.h"

using namespace std;

set<int> CrossSet(set<int> const& set1, set<int> const& set2);
int SumOfNum(int i);
void PrintSet(set<int> const& set);
void InsertToSets(set<int> & set1, set<int> & set2, int num);