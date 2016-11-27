// FizzBuzz.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;
void FizzBuzz()
{
	setlocale(LC_CTYPE, "rus");
	int i;
	cout << "¬ведите число  от 1 до 100\n";
	while (cin >> i )
	{
		if (i <= 100 && i > 0)
		{
			cout << i << '\n';
			if (i % 3 == 0 && i % 5 == 0)
			{
				cout << "FizzBuzz\n";
			} 
			else if (i % 3 == 0)
			{
				cout << "Fizz\n";
			}
			else if (i % 5 == 0)
			{
				cout << "Buzz\n";
			}
			
		}
		else
		{
			break;
		}
	}
}
int main()
{
	FizzBuzz();
    return 0;
}

