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
		ListItem *prev;

		ListItem(std::string str, ListItem *n = NULL)
		{
			item = str;
			prev = next;
			next = n;
		}

	};
	int itemsCount;
	
	bool empty;
	ListItem *first;
	//ListItem *prev;
	ListItem *last;
public:
	StringList() 
	{
		int itemsCount = 0;
		first = NULL;
		last = NULL;
		empty = true;
	}
	
	StringList(const StringList & src);

	~StringList();

	void ReturnLastPrev();

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
	void AddToList(std::string const & str);
	void RemoveFirst();//Метод для удаления первого элемента в списке
	bool Remove(std::string str);
	void RemoveSecond();
	void Insert(std::string const & str, std::string const & tofound);
	std::string GetAllItemsInfo();
	bool FindInList(std::string const & str);
	bool GoToNext(std::string & next);
	bool EmptyList();
	bool IsFirst(std::string & str);
	bool IsEnd(std::string & str);
	bool RemoveFromLast(std::string str);
	void RemoveLast();
};
