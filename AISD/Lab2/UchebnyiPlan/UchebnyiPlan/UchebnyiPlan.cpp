// UchebnyiPlan.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<string>
#include<fstream>
#include <Windows.h>
#include<list>
#include <clocale>
#include<iterator>
using namespace std;

const int MWORD = 30;           //���� ����� �����

int main()
{
	setlocale(LC_CTYPE, "rus");
	/*SetConsoleCP(1251);
	SetConsoleOutputCP(1251);*/

	list<string> li;
	char menu;

	while (true)
	{
		cin.sync();
		cout << "\n�������� ��������:"
			<< "\n1 - ���� ������ � ����������"
			<< "\n2 - ���� ������ � �����"
			<< "\n3 - �������� ������(������� � ������� �����)"
			<< "\n4 - ������� �� ������ ��� ���� ����, ������� �������� ��������� ���� �����"
			<< "\n5 - �������� ������"
			<< "\n0 - �����"
			<< "\n��� �����: ";
		cin >> menu;
		switch (menu)
		{
		case '1':
		{
			cin.sync();
			string text;
			char word[MWORD];

			cout << "\n������� �����:\n";
			getline(cin, text);

			for (int x = 0; x < text.length(); x++)
			{
				int y = 0;
				while (isalpha((unsigned char)text[x]))
					word[y++] = text[x++];
				word[y] = ' ';

				if (y != 0)
					li.push_back(word);
			}
			break;
		}
		case '2':
		{
			cin.sync();
			char adres[MWORD];
			char ch;
			char word[MWORD];

			cout << "\n������� ����� �����: ";
		
			//ifstream fail(adres);
			ifstream inputFile("text");
			/*if (inputFile.is_open())
			{
				string line1;
				if (!getline(inputFile, line1))
				{
					cout << "Failed to read a line from file" << endl;
					return;
				}
*/
			if (inputFile.is_open())
				while (inputFile.is_open())
				{
					inputFile.get(ch);
					int y = 0;
					for (; isalpha((unsigned char)ch) && inputFile; inputFile.get(ch))
						word[y++] = ch;
					word[y] = ' ';

					if (y)
						li.push_back(word);
				}
			else
				cout << "\n���������� ������� ����!\n";
			break;
		}
		case '3':
			if (!li.empty())
			{
				cout << "\nC����� ������� � ������� �����: " << endl;
				copy(li.begin(), li.end(), ostream_iterator<string>(cout, "\n"));
			}
			else
				cout << "\n������ ����\n" << endl;
			break;

		case '4':
			if (!li.empty())
			{
				list<string>::iterator it;
				list<string>::iterator ih;

				for (it = li.begin(); it != li.end(); it++)
					for (++(ih = it); ih != li.end(); ih++)
					{
						string temp = *ih;
						if (*it == temp.assign(temp.rbegin(), temp.rend()))
						{
							li.erase(it);
							li.erase(ih);
							break;
						}
					}
				cout << "\n�� ������ ������� ��� ���� ����, ������� �������� ��������� ���� �����" << endl;
			}
			else
				cout << "\n������ ����\n" << endl;
			break;

		case '5':
		{
			li.clear();
			cout << "\n������ ������\n" << endl;
			break;
		}
		case '0': return 0;
		default: cout << "\n����������� ��������\n";
		}
	}
	return 0;
}