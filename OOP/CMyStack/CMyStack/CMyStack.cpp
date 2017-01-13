// CMyStack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CMyStack.h"
struct ThrowableStruct
{
	ThrowableStruct(bool throws = true)
		: m_throws(throws)
	{

	}

	ThrowableStruct()
		: m_throws(true)
	{
		if (m_throws)
		{
			throw std::exception("constructor");
		}
	}

	ThrowableStruct(ThrowableStruct const& arg)
	{
		if (m_throws)
		{
			throw std::exception("copy");
		}
	}

	ThrowableStruct(ThrowableStruct && arg)
	{
		if (m_throws)
		{
			throw std::exception("move");
		}
	}

	ThrowableStruct operator=(ThrowableStruct const& arg)
	{
		if (m_throws)
		{
			throw std::exception("assign");
		}
	}

	~ThrowableStruct()
	{
		if (m_throws)
		{
			throw std::exception("destructor");
		}
	}


private:
	bool m_throws;
};

int main()
{
	/*try 
	{

	}
    return 0;*/
}

