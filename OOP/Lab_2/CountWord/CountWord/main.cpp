#include "stdafx.h"
#include "CountWord.h"
#include <fstream>



int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "");
	ifstream file("new.txt");
	CountNumbersMap countNumbers;
	//map<wstring, int> countWords;
	while (!file.eof())
	{
		CountNumbers(file, countNumbers);
		/*CountWord(file, countWords);*/
	}
	float num = CountMap(countNumbers);
	double disp = Disp(countNumbers, num/100);
	PrintMap(countNumbers);
	cout << num / 100 << endl;
	cout << disp / 99 << endl;
	return 0;
}