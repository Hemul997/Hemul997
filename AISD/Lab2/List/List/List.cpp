// List.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "StringList.h"
using namespace std;

bool ReadStream(istream &args, string &line, string & secline)
{
	if (!args.eof())
	{
		getline(args, line);
		if (!args.eof())
		{
			getline(args, secline);
			return true;
		}
	}
	return false;
}

int main()
{
	StringList mylist;
	string firstDisciplline;
	string secondDiscipline;
	/*mylist.AddFirst("Arifm");
	mylist.AddLast("Math");
	mylist.AddLast("Geom");
	
	cout << mylist.GetAllItemsInfo();
	//mylist.Remove("Math");
	//cout << mylist.GetAllItemsInfo();
	mylist.RemoveFirst();
	cout << mylist.GetAllItemsInfo();
	cout << mylist.Head();*/

	ReadStream(cin, firstDisciplline, secondDiscipline);
	mylist.AddFirst(firstDisciplline);
	if (!mylist.FindInList(secondDiscipline))
	{
		mylist.AddLast(secondDiscipline);
	}
	cout << mylist.GetAllItemsInfo();
	while (ReadStream(cin, firstDisciplline, secondDiscipline))
	{
		if (!mylist.FindInList(firstDisciplline))
		{
			mylist.AddLast(firstDisciplline);
		}
		if (!mylist.FindInList(secondDiscipline))
		{
			mylist.AddLast(secondDiscipline);
		}
		if (mylist.FindInList(firstDisciplline) && mylist.FindInList(secondDiscipline))
		{
			if (secondDiscipline == mylist.Head())
			{
				cout << "Cikl!!!!\n";
				mylist.AddLast(secondDiscipline);
				cout << mylist.GetAllItemsInfo();
				return 1;
			}

			mylist.Remove(firstDisciplline);
			mylist.Insert(firstDisciplline, secondDiscipline);
			cout << mylist.GetAllItemsInfo();
		}
	}
	//cout << mylist.GetAllItemsInfo();
    return 0;
}

