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
void StringList::ReturnLastPrev()
{
	std::string str;
	ListItem *cur = last->prev;
	std::cout << cur->item;
}
void StringList::AddLast(const StringList & src)
{
	for (ListItem *cur = src.first; cur != NULL; cur = cur->next)
	{
		AddToList(cur->item);
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

void StringList::AddToList(std::string const & str)
{
	ListItem *newItem = new ListItem(str, NULL);
	if (!last/* = NULL*/)
	{
		first = newItem;
		first->prev = NULL;
	}
	else
	{
		last->next = newItem;
	}
	last = newItem;
}

void StringList::RemoveFirst()
{
	first = first->next;
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
void StringList::RemoveSecond()
{
	ListItem *prev = 0, *current = first->next;
	delete current;
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
	for (ListItem *current = first; current != NULL; current = current->next)
	{
		if (current->item == str)
		{
			return true;
		}
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
bool StringList::EmptyList()
{
	if (first==NULL)
	{
		return true;
	}
	return false;
}
bool StringList::IsFirst(std::string & str)
{
	for(ListItem *prev = 0, *current = first; current != NULL; current = current->next)
	{
		if (prev == 0 && current->item == str && first->item == str)
		{
			return true;
		}
	}
	return false;
}
bool StringList::IsEnd(std::string & str)
{
	for (ListItem *current = first; current != NULL; current = current->next)
	{
		if (current->item == str && current == NULL)
		{
			return true;
		}
	}
	return false;
}
bool StringList::RemoveFromLast(std::string str)
{
	ListItem *prev = 0,*current = last;
	while (current != NULL)
	{
		if (current->item == str)
		{
			if (prev)
			{
				prev->prev = current->prev;
			}
			if (prev == 0)
			{
				current = current->prev;
			}
			if (current == first)
			{
				first = prev;
			}
			if (current == last)
			{
				last = last->prev;
				return true;
			}
			delete current;
			return true;
		}
		else
		{
			prev = current;
			current = current->prev;

		}
	}
	return false;
}
void StringList::RemoveLast()
{
	last = last->prev;
}