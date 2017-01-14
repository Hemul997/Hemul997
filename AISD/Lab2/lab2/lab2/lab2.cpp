// lab2.cpp: определяет точку входа для консольного приложения.
//Мошкин Никита ПС 22
//Учебный план включает перечень дисциплин.  Задан список
//пар дисциплин.Отдельная пара показывает, что вторая
//дисциплина должна изучаться  после  первой.Составить  список
//дисциплин учебного плана в порядке их изучения.В том случае,
//когда задание некорректно, т.е.в списке пар имеются  циклы,
//выдать хотя бы один из них(10).

#include "stdafx.h"
#include <list>
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>
#include <fstream>
#include <Windows.h>

using namespace std;
ostream & operator<<(ostream &out, const list<string> & obj);
bool ReadStream(istream & args, string & firstLine, string & secondLine);
bool ReadStream(istream & args1, istream &args2, string & firstLine, string & secondLine);
auto getPos(string const & line, list<string> &mylist);
auto getReversePos(string const & line, list<string> &mylist);
bool foundInList(string const & line, list<string> &mylist);
bool findCycle(list<string>const & firstDisciplines, list<string> const & secondDisciplines);
void SortDisciplines(list<string> &firstDisciplines, list<string> &secondDisciplines, list<string> &tempList, list<string> &outList, string &firstDiscipline, string& secondDiscipline);

int _tmain(int argc, _TCHAR* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	list<string> firstDisciplines;
	list<string> secondDisciplines;
	list<string> outList;
	list<string> tempList;
	string firstDiscipline;
	string secondDiscipline;
	ifstream inputFile("disciplines.txt");
	bool ListCorrected = false;
	bool CycleFound = false;
	if (inputFile.is_open())
	{
		while (ReadStream(inputFile, firstDiscipline, secondDiscipline))
		{
			firstDisciplines.push_back(firstDiscipline);
			secondDisciplines.push_back(secondDiscipline);
		}
	}
	else
	{
		return EXIT_FAILURE;
	}
	inputFile.clear();
	inputFile.seekg(0, ios::beg);
	//cout << firstDisciplines << endl;
	//cout << secondDisciplines << endl;
	ofstream out1File("first.txt");
	ofstream out2File("second.txt");
	out1File << firstDisciplines << endl;
	out2File << secondDisciplines << endl;
	out1File.close();
	out2File.close();
	ifstream inp1File("first.txt");
	ifstream inp2File("second.txt");
	while(!ListCorrected && !CycleFound)
	{
		if(!inp1File.eof() && !inp2File.eof())
		{
			ReadStream(inp1File, inp2File, firstDiscipline, secondDiscipline);
			if (!inp1File.eof() && !inp2File.eof())
			{
				SortDisciplines(firstDisciplines, secondDisciplines, tempList, outList, firstDiscipline, secondDiscipline);
			}
		}
		else
		{
			ofstream out1File("first.txt");
			ofstream out2File("second.txt");
			out1File << firstDisciplines << endl;
			out2File << secondDisciplines << endl;
			inp1File.clear();
			inp1File.seekg(0, ios::beg);
			inp2File.clear();
			inp2File.seekg(0, ios::beg);
		}
		if (firstDisciplines.empty() && firstDisciplines.empty())
		{
			ListCorrected = true;
		}
		if (findCycle(firstDisciplines, secondDisciplines) && !firstDisciplines.empty() && !firstDisciplines.empty())
		{
			CycleFound = true;
		}
	}
	if (ListCorrected)
	{
		cout << "Получен список дисциплин :" << endl;
		cout << outList << endl;
		return 0;
	}
	if (CycleFound)
	{
		cout << "Множество пар упорядочить невозможно!\n"
			 << "Следующие пары дисциплин образуют цикл :\n";
		cout << firstDisciplines << endl;
		cout << secondDisciplines << endl;
		return 1;
	}
}
ostream & operator<<(ostream &out, const list<string> & obj)
{
	for (auto it = obj.begin(); it != obj.end(); ++it)
	{
		out << *it << ' ';
	}
	return out;
}
bool ReadStream(istream & args, string & firstLine, string & secondLine)
{
	bool readFirst = false;
	if (!args.eof())
	{
		args >> firstLine;
		readFirst = true;
		if (!args.eof() && readFirst)
		{
			args >> secondLine;
			return true;
		}
	}
	return false;
}
bool ReadStream(istream & args1, istream &args2, string & firstLine, string & secondLine)
{
	bool readFirst = false;
	if (!args1.eof())
	{
		args1 >> firstLine;
		readFirst = true;
		if (!args2.eof() && readFirst)
		{
			args2 >> secondLine;
			return true;
		}
	}
	return false;
}
auto getPos(string const & line, list<string> &mylist)
{
	auto it = find(mylist.begin(), mylist.end(), line);
	if (it != mylist.end())
	{
		return it;
	}
}
auto getReversePos(string const & line, list<string> &mylist)
{
	auto rev_it = find(mylist.rbegin(), mylist.rend(), line);
	if (rev_it != mylist.rend())
	{
		return --rev_it.base();
	}
}
bool foundInList(string const & line, list<string> &mylist)
{
	auto it = find(mylist.begin(), mylist.end(), line);
	if (it != mylist.end())
	{
		return true;
	}
	return false;
}
bool findCycle(list<string>const & firstDisciplines, list<string> const & secondDisciplines)
{
	auto first = firstDisciplines;
	auto second = secondDisciplines;
	first.sort();
	first.unique();
	second.sort();
	second.unique();
	return first == second;
}
void SortDisciplines(list<string> &firstDisciplines, list<string> &secondDisciplines, list<string> &tempList, list<string> &outList, string &firstDiscipline, string& secondDiscipline)
{
	if (!foundInList(firstDiscipline, secondDisciplines) && foundInList(firstDiscipline, firstDisciplines) && !foundInList(firstDiscipline, outList))
	{

		firstDisciplines.remove(firstDiscipline);
		if (!foundInList(secondDiscipline, tempList))
		{
			secondDisciplines.erase(getPos(secondDiscipline, secondDisciplines));
		}
		else
		{
			secondDisciplines.erase(getReversePos(secondDiscipline, secondDisciplines));
		}
		if (outList.empty())
		{
			outList.push_front(firstDiscipline);
		}
		else
		{
			outList.push_back(firstDiscipline);
		}
	}
	else
	{
		if (foundInList(firstDiscipline, outList))
		{
			secondDisciplines.erase(getPos(secondDiscipline, secondDisciplines));
		}
	}
	tempList.push_back(secondDiscipline);
	if (!foundInList(secondDiscipline, firstDisciplines) && !foundInList(secondDiscipline, secondDisciplines) && foundInList(secondDiscipline, tempList))
	{
		outList.push_back(secondDiscipline);
	}
}