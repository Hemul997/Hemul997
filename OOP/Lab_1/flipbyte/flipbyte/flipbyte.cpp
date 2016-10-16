// flipbyte.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;
int ReverseBits(int numToReverse)
{
	int result = 0;
	//int i;
	for (int i = 7; i >= 0; --i)
	{
		result ^= (numToReverse >> (7 - i) & 1) << i;
	}
	return result;
}

bool IsDigit(char *val)
{
	int length = strlen(val);
	for (int i = 0; i < length; ++i)
	{
		if (val[i] < '0' || val[i] >'9')
		{
			return false;
		}
	}
		
	return true;
}		

bool IsByte(int const& val)
{
	return ((val >= 0) && (val <= 255));
}

int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments count: \n"
			<< "Usage: flipbyte.exe <byte>\n";
		return 1;
	}
	if (strlen(argv[1]) == 0)
	{
		cout << "<byte> should not be empty\n";
		return 1;
	}
	if (!IsDigit(argv[1]))
	{
		cout << "Input is not number\n";
		return 1;
	}
	int NumToReverse = atoi(argv[1]);
	if (!IsByte(NumToReverse))
	{
		cout << "Input number is not included\n";
		return 1;
	}
	cout << ReverseBits(NumToReverse)
		 << "\n" ;
    return 0;//
}

