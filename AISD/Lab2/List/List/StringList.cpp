#include "stdafx.h"
#include "StringList.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


StringList::StringList(const StringList & src)
{
	first = last = NULL;
	AddLast(src);
}

StringList::~StringList()
{
	ListItem *current = NULL;
	ListItem *next = first;
	while (next != NULL)
	{
		current = next;
		next = next->next;
		delete current;
	}
}

void StringList::AddLast(const StringList & src)
{
	for (ListItem *cur = src.first; cur != NULL; cur = cur->next)
	{
		AddLast(cur->item);
	}
}

void StringList::AddFirst(std::string const & str)
{
	ListItem *newItem = new ListItem(str, first);
	if (!first)
	{
		last = newItem;
	}
	first = newItem;
}

void StringList::AddLast(std::string const & str)
{
	ListItem *newItem = new ListItem(str/*, NULL*/);
	if (!last/* = NULL*/)
	{
		first = newItem;
	}
	else
	{
		last->next = newItem;
	}
	last = newItem;
}

/*std::string*/ void StringList::RemoveFirst()
{
	//std::string result = first->item;
	first = first->next;
	//return result;
}

bool StringList::Remove(std::string str)
{
	ListItem *prev = 0,
		*current = first;
	while (current)
	{
		if (current->item == str)
		{
			if (prev)
			{
				prev->next = current->next;
			}
			if (prev == 0)
			{
				current = current->next;
			}
			if (current == last)
			{
				last = prev;
			}
			delete current;
			return true;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
	return false;
}

void StringList::Insert(std::string const & str, std::string const & tofound)
{
	ListItem *prev = NULL,
		*succ = first;
	while (succ != NULL && succ->item != tofound)
	{
		prev = succ;
		succ = succ->next;
	}
	ListItem *newItem = new ListItem(str, succ);
	if (succ == NULL)
	{
		last = newItem;
	}
	if (prev == NULL)
	{
		first = newItem;
	}
	else
	{
		prev->next = newItem;
	}
}

std::string StringList::GetAllItemsInfo()
{
	std::stringstream stream;
	ListItem *current = first;
	while (current != NULL)
	{
		stream << current->item << ' ';
		current = current->next;
	}
	stream << std::endl;
	return stream.str();

}
bool StringList::FindInList(std::string const & str)
{
	ListItem *current = first;
	while(current != NULL)
	{
		if (current->item == str)
		{
			return true;
		}
		current = current->next;
	}
	return false;
}
bool StringList::GoToNext(std::string & str)
{
	ListItem *current = first->next;
	if (current != NULL)
	{
		str = current->item;
		return true;
	}
	return false;
}
bool StringList::FindTwoInList(std::string const & str, std::string const &sec)
{
	ListItem *current = first;
	bool FindFirst = false;	
	while (current != NULL)
	{
		if (current->item == str)
		{
			FindFirst = true;
		}
		if (FindFirst && current->item == sec)
		{
			return true;
		}
		current = current->next;
	}
	return false;
}
bool StringList::EmptyList()
{
	if (first == NULL && last == NULL)
	{
		return true;
	}
	return false;
}
bool StringList::IsFirst(std::string & str)
{
	ListItem *prev = 0,
		*current = first;
	while(current != NULL)
	{
		if (prev == 0 && current->item == str && first->item == str)
		{
			return true;
		}
		current = current->next;
	}
	return false;
}
//std::string StringList::ReturnNextElem()
//{
//	ListItem *current = first;
//	if(current != NULL)
//	{
//		current = current->next;
//		//return current->item;
//	}
//	return current->item;
//}
//std::string StringList::ReturnNextElem(std::string &str)
//{
//	ListItem *current = first;
//	while (current != NULL && current->item == str)
//	{
//		current = current->next;
//		if (current->item == str)
//		{
//			current = current->next;
//			return current->item;
//		}
//	}
//}