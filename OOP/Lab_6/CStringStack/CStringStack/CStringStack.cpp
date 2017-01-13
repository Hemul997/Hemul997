// CStringStack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CStringStack.h"

CStringStack::CStringStack(CStringStack const &stack)
{
	*this = stack;
}

CStringStack::CStringStack(CStringStack &&stack)
{
	*this = std::move(stack);
}

CStringStack::~CStringStack()
{
	Clear();
}
void CStringStack::Push(std::string const &element)
{
	auto newElement = std::make_shared<Node>();

	newElement->element = element;

	if (m_lastElement != nullptr)
	{
		newElement->prevElement = m_lastElement;
	}

	m_lastElement = newElement;

	++m_size;
}
void CStringStack::Pop()
{
	if (IsEmpty())
	{
		throw std::underflow_error("Can't pop element from empty stack.");
	}

	m_lastElement = m_lastElement->prevElement;

	--m_size;
}
void CStringStack::Clear()
{
	while (!IsEmpty())
	{
		Pop();
	}
}
std::string CStringStack::GetLastElement()const
{
	if (IsEmpty())
	{
		throw std::underflow_error("Can't get last element from empty stack.");
	}

	return(m_lastElement->element);
}
size_t CStringStack::GetSize()const
{
	return(m_size);
}

bool CStringStack::IsEmpty()const
{
	return(m_size == 0);
}
CStringStack& CStringStack::operator =(CStringStack const &stack)
{
	if (this != &stack)
	{
		auto tempNode = stack.m_lastElement;

		auto seed = std::make_shared<Node>();
		auto prevNode = seed;

		seed->element = tempNode->element;

		tempNode = tempNode->prevElement;

		while (tempNode != nullptr)
		{
			auto newNode = std::make_shared<Node>();
			newNode->element = tempNode->element;

			prevNode->prevElement = newNode;
			prevNode = newNode;

			tempNode = tempNode->prevElement;
		}

		m_size = stack.GetSize();
		m_lastElement = seed;
	}

	return *this;
}
CStringStack &CStringStack::operator=(CStringStack &&stack)
{
	if (this != &stack)
	{
		m_lastElement = stack.m_lastElement;
		m_size = stack.GetSize();

		stack.m_lastElement = nullptr;
		stack.m_size = 0;
	}

	return *this;
}
bool CStringStack::operator ==(CStringStack const &stack)const
{
	if (GetSize() != stack.GetSize())
	{
		return false;
	}

	auto tempNode1 = m_lastElement;
	auto tempNode2 = stack.m_lastElement;

	while (tempNode1 != nullptr)
	{
		if (tempNode1->element != tempNode2->element)
		{
			return false;
		}

		tempNode1 = tempNode1->prevElement;
		tempNode2 = tempNode2->prevElement;
	}

	return true;
}
bool CStringStack::operator !=(CStringStack const &stack)const
{
	return !(*this == stack);
}
