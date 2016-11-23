#include "stdafx.h"
#include "HTMLDecode.h"

#include <iostream>

using namespace std;

int main()
{
	string line;
	while (ReadStream(cin, line))
	{
		cout << HtmlDecode(line) << '\n';
	}
	return 0;
}