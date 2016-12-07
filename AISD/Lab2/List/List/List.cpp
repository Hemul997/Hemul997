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
bool ReadStream(istream &args, string &firstLine)
{
	if (!args.eof())
	{
		args >> firstLine;
		return true;
	}
	return false;
}
void ProccessDisciplines(StringList & firstList, StringList & secondList, StringList & outList, StringList& tempList, string & firstDiscipline, string & secondDiscipline)
{
	cout << firstDiscipline << " " << secondDiscipline << " disp\n";
	
	if (firstList.FindInList(firstDiscipline) && !secondList.FindInList(firstDiscipline) && !outList.FindInList(firstDiscipline))
	{
		cout << "1:\n";
		outList.AddToList(firstDiscipline);
		if (firstList.IsFirst(firstDiscipline) && secondList.IsFirst(secondDiscipline))
		{
			firstList.RemoveFirst();
			secondList.RemoveFirst();
		}
		else
		{
			if (tempList.FindInList(secondDiscipline) && secondList.FindInList(secondDiscipline))
			{
				firstList.Remove(firstDiscipline);
				secondList.RemoveLast();
				//secondList.RemoveFromLast(secondDiscipline);
			}
			else
			{
				if (!firstList.IsFirst(firstDiscipline) && secondList.IsFirst(secondDiscipline))
				{
					firstList.Remove(firstDiscipline);
					secondList.RemoveFirst();
				}
				else
				{
					firstList.Remove(firstDiscipline);
					secondList.Remove(secondDiscipline);
				}
			}
			
		}
	}
	else
	{
		cout << "2:\n";
		if (outList.FindInList(firstDiscipline))
		{
			//cout << firstDiscipline << " " << secondDiscipline << endl;
			if (firstList.IsFirst(firstDiscipline) && secondList.IsFirst(secondDiscipline))
			{
				firstList.RemoveFirst();
				secondList.RemoveFirst();

			}
			else
			{
				if (!firstList.IsFirst(firstDiscipline) && secondList.IsFirst(secondDiscipline))
				{
					firstList.Remove(firstDiscipline);
					secondList.RemoveFirst();
				}
				else
				{
					firstList.Remove(firstDiscipline);
					secondList.Remove(secondDiscipline);
				}
			}
		}
	}
	tempList.AddToList(secondDiscipline);
	if (!firstList.FindInList(secondDiscipline) && !secondList.FindInList(secondDiscipline) && !outList.FindInList(secondDiscipline))
	{
		outList.AddToList(secondDiscipline);
	}
	//cout << "O: " << outList.GetAllItemsInfo();
	
}
int main()
{
	StringList firstList;
	StringList secondList;
	StringList tempList;
	StringList outList;
	string tempDisp;
	string firstDiscipline;
	string secondDiscipline;
	bool findFirstSucc = false;
	ifstream inputFile("disciplines.txt");
	bool flag = false;
	if (inputFile.is_open() && !inputFile.eof())
	{
		while (ReadStream(inputFile, firstDiscipline) && ReadStream(inputFile, secondDiscipline))
		{
			firstList.AddToList(firstDiscipline);
			secondList.AddToList(secondDiscipline);
		}
	}
	else
	{
		cout << "Failed to open disciplines.txt for reading\n" << endl;
		return EXIT_FAILURE;
	}
	ofstream out1File("first.txt");
	ofstream out2File("second.txt");
	out1File << firstList.GetAllItemsInfo();
	out2File << secondList.GetAllItemsInfo();
	out1File.close();
	out2File.close();
	ifstream inp1File("first.txt");
	ifstream inp2File("second.txt");
	/*inputFile.clear();
	inputFile.seekg(0, ios::beg);*/
	cout << firstList.GetAllItemsInfo();
	cout << secondList.GetAllItemsInfo();
	while (!flag)
	{
		if (!firstList.EmptyList() && !secondList.EmptyList())
		{
			
			ReadStream(inp1File, firstDiscipline) && ReadStream(inp2File, secondDiscipline);
			ProccessDisciplines(firstList, secondList, outList, tempList, firstDiscipline, secondDiscipline);
			if (inp1File.eof() && inp2File.eof())
			{
				ofstream out1File("first.txt");
				ofstream out2File("second.txt");
				out1File << firstList.GetAllItemsInfo();
				out2File << secondList.GetAllItemsInfo();
				inp1File.clear();
				inp1File.seekg(0, ios::beg);
				inp2File.clear();
				inp2File.seekg(0, ios::beg);
			}
			cout << "F: " << firstList.GetAllItemsInfo();
			cout << "S: " << secondList.GetAllItemsInfo();
			cout << "O: " << outList.GetAllItemsInfo();
		}
		else
		{
			flag = true;
		}

		//cout << "S: " << secondList.GetAllItemsInfo();
		/*cout << "O: " << outList.GetAllItemsInfo();
		cout << "F: " << firstList.GetAllItemsInfo();
		cout << "S: " << secondList.GetAllItemsInfo();*/
	}
	
	cout << "F: " << firstList.GetAllItemsInfo();
	cout << "S: " << secondList.GetAllItemsInfo();
	cout << "O: "<<outList.GetAllItemsInfo();
	//cout << secondList.GetAllItemsInfo();

	return 0;
}