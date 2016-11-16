#include "stdafx.h"
#include "CountWord.h"


int main()
{
	map<string, int> countWords;
	while (!cin.eof())
	{
		CountWord(cin, countWords);
	}
	PrintMap(countWords);
	return 0;
}