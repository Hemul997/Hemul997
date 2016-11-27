#include "stdafx.h"


std::string DeleteSpaces(const std::string & str)
{
	std::string name;
	for (size_t i = 0; i < str.size(); ++i)
	{
		if (str[i] != ' ')
		{
			name += str[i];
		}
		else
		{
			if (!(str[i] == ' ' && str[i + 1] == str[i]))
			{
				name += ' ';
			}
		}
	}
	return name;
}