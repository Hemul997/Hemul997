#pragma once
#include <iostream>
#include <vector>
using namespace std;

vector<double> ReadVector(istream & input);
void SortVector(vector<double> & numbers);
void WorkWithVector(vector<double> & numbers);
void OutVector(ostream & output, vector<double> & numbers);