// List.cpp : Defines the entry point for the console application.
//
//Учебный план включает перечень дисциплин.Задан список
//пар   дисциплин.Отдельная   пара   показывает, что  вторая
//дисциплина должна изучаться  после  первой.Составить  список
//дисциплин учебного плана в порядке их изучения.В том случае,
//когда задание некорректно, т.е.в списке пар имеются  циклы,
//выдать хотя бы один из них(10).
#include "stdafx.h"
#include "StringList.h"
using namespace std;

bool ReadStream(istream &args, string &firstLine, string &secondLine)
{
	if (!args.eof())
	{
		args >> firstLine;
		if (!args.eof())
		{
			args >> secondLine;
			return true;
		}
	}
	return false;
}
void ProccessDisciplines(StringList & firstList, StringList & secondList , StringList & tempList, StringList & outList, string & firstDiscipline, string & secondDiscipline)
{
	cout << firstDiscipline << " " << secondDiscipline << "disp\n";
	if (firstList.FindInList(firstDiscipline) && !secondList.FindInList(firstDiscipline) && !outList.FindInList(firstDiscipline))
	{
		outList.AddLast(firstDiscipline);
		if (firstList.IsFirst(firstDiscipline) && secondList.IsFirst(secondDiscipline))
		{
			firstList.RemoveFirst();
			secondList.RemoveFirst();
			tempList.AddLast(secondDiscipline);
		}
		else
		{
			firstList.Remove(firstDiscipline);
			secondList.Remove(secondDiscipline);
			tempList.AddLast(secondDiscipline);
		}
		cout << "1:\n";
	}
	else
	{
		if (outList.FindInList(firstDiscipline))
		{
			if (firstList.IsFirst(firstDiscipline) && secondList.IsFirst(secondDiscipline))
			{

				firstList.RemoveFirst();
				tempList.AddLast(secondDiscipline);
				secondList.RemoveFirst();

			}
			else
			{
				firstList.Remove(firstDiscipline);
				tempList.AddLast(secondDiscipline);
				secondList.Remove(secondDiscipline);

			}
		}
		cout << "2:\n";
	}

}
int main()
{
	StringList firstList;
	StringList secondList;
	StringList tempList;
	StringList outList;
	string firstDiscipline;
	string secondDiscipline;
	bool findFirstSucc = false;
	ifstream inputFile1("disciplines.txt");
	bool firstListSuccProc = false;
	if (inputFile1.is_open() && !inputFile1.eof())
	{
		while (ReadStream(inputFile1, firstDiscipline, secondDiscipline))
		{
			firstList.AddLast(firstDiscipline);
			secondList.AddLast(secondDiscipline);
		}
	}
	else
	{
		cout << "Failed to open disciplines.txt for reading\n" << endl;
		return EXIT_FAILURE;
	}
	inputFile1.clear();
	inputFile1.seekg(0, ios::beg);
	cout << firstList.GetAllItemsInfo();
	cout << secondList.GetAllItemsInfo();
	if (inputFile1.is_open() && !inputFile1.eof())
	{
		string firstDiscipline;
		string secondDiscipline;
		while (ReadStream(inputFile1, firstDiscipline, secondDiscipline))
		{
			ProccessDisciplines(firstList, secondList, tempList, outList, firstDiscipline, secondDiscipline);
		}
		
	}
	cout << "F: " << firstList.GetAllItemsInfo();
	cout << "S: " << secondList.GetAllItemsInfo();
	cout << "T: " << tempList.GetAllItemsInfo();
	cout << "O: "<<outList.GetAllItemsInfo();
	//cout << secondList.GetAllItemsInfo();

	return 0;
}

