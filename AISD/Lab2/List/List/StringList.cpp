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

std::string StringList::RemoveFirst()
{
	std::string result = first->item;
	first = first->next;
	return result;
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

void StringList::Insert(std::string str)
{
	ListItem *prev = NULL,
		*succ = first;
	while (succ != NULL && succ->item < str)
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