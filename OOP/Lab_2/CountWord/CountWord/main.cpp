#include "stdafx.h"
#include "CountWord.h"




int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "");
	map<wstring, int> countWords;
	while (!wcin.eof())
	{
		CountWord(wcin, countWords);
	}
	PrintMap(countWords);
	return 0;
}