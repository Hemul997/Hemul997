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

const int MWORD = 30;           //макс длина слова

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
		cout << "\nВыберите действие:"
			<< "\n1 - ввод текста с клавиатуры"
			<< "\n2 - ввод текста с файла"
			<< "\n3 - показать список(начиная с первого звена)"
			<< "\n4 - удалить из списка все пары слов, которые являются обратными друг другу"
			<< "\n5 - очистить список"
			<< "\n0 - выход"
			<< "\nВаш выбор: ";
		cin >> menu;
		switch (menu)
		{
		case '1':
		{
			cin.sync();
			string text;
			char word[MWORD];

			cout << "\nВведите текст:\n";
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

			cout << "\nВведите адрес файла: ";
		
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
				cout << "\nНевозможно открыть файл!\n";
			break;
		}
		case '3':
			if (!li.empty())
			{
				cout << "\nCписок начиная с первого звена: " << endl;
				copy(li.begin(), li.end(), ostream_iterator<string>(cout, "\n"));
			}
			else
				cout << "\nСписок пуст\n" << endl;
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
				cout << "\nИз списка удалены все пары слов, которые являются обратными друг другу" << endl;
			}
			else
				cout << "\nСписок пуст\n" << endl;
			break;

		case '5':
		{
			li.clear();
			cout << "\nСписок очищен\n" << endl;
			break;
		}
		case '0': return 0;
		default: cout << "\nНеизвестное действие\n";
		}
	}
	return 0;
}