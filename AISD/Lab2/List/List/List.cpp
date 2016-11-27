// List.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "StringList.h"
using namespace std;

bool ReadStream(istream &args, string &line)
{
	if (!args.eof())
	{
		getline(args, line);
		return true;
	}
	return false;
}

int main()
{
	StringList mylist;
	string discipline;
	/*mylist.AddFirst("Arifm");
	mylist.AddLast("Math");
	mylist.AddLast("Geom");
	
	cout << mylist.GetAllItemsInfo();
	//mylist.Remove("Math");
	//cout << mylist.GetAllItemsInfo();
	mylist.RemoveFirst();
	cout << mylist.GetAllItemsInfo();
	cout << mylist.Head();*/

	getline(cin, discipline);
	mylist.AddFirst(discipline);
	cout << mylist.GetAllItemsInfo();
	while (ReadStream(cin, discipline))
	{
		if (!mylist.FindInList(discipline))
		{
			mylist.AddLast(discipline);
		}
	}
	cout << mylist.GetAllItemsInfo();
    return 0;
}

