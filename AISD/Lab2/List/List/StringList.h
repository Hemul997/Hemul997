#pragma once
#include <iostream>
//#include <fstream>
#include <string>
#include <sstream>

class StringList
{
private:
	struct ListItem
	{
		std::string item;
		ListItem *next;

		ListItem(std::string str, ListItem *n = NULL) 
		{
			item = str;
			next = n;
		}
		
	};
	ListItem *first;
	ListItem *last;
public:
	StringList() 
	{
		first = last = NULL;
	}

	StringList(const StringList & src);

	~StringList();
	std::string Head()const
	{
		return first->item;
	}
	std::string & Head()
	{
		return first->item;
	}
	std::string Tail()const
	{
		return last->item;
	}
	std::string & Tail()
	{
		return last->item;
	}
	void AddLast(const StringList &src);
	void AddFirst(std::string const & str);
	void AddLast(std::string const & str);
	std::string RemoveFirst();//����� ��� �������� ������� �������� � ������
	bool Remove(std::string str);
	void Insert(std::string const & str, std::string const & tofound);
	//����� ��� �������� �� �������� ������ ������� � ��������� ���������
	//void Insert(std::string str);//���������� �������� �� ��������� ������
	std::string GetAllItemsInfo();
	bool FindInList(std::string const & str);
};
