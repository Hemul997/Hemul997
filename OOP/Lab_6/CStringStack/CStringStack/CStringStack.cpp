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
	auto newNode = std::make_shared<Node>();

	newNode->value = element;

	if (m_top != nullptr)
	{
		newNode->m_prevNode = m_top;
	}

	m_top = newNode;

	++m_size;
}
void CStringStack::Pop()
{
	if (IsEmpty())
	{
		throw std::underflow_error("Can't pop element from empty stack.");
	}

	m_top = m_top->m_prevNode;

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

	return(m_top->value);
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
	if (!stack.IsEmpty())
	{
		auto tempNode = stack.m_top;

		auto seed = std::make_shared<Node>();
		auto prevNode = seed;

		seed->value = tempNode->value;

		tempNode = tempNode->m_prevNode;

		while (tempNode != nullptr)
		{
			auto newNode = std::make_shared<Node>();
			newNode->value = tempNode->value;

			prevNode->m_prevNode = newNode;
			prevNode = newNode;

			tempNode = tempNode->m_prevNode;
		}
		m_size = stack.GetSize();
		m_top = seed;
	}
	return *this;
}
CStringStack &CStringStack::operator=(CStringStack &&stack)
{
	if (this != &stack)
	{
		m_top = stack.m_top;
		m_size = stack.GetSize();

		stack.m_top = nullptr;
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

	auto tempNode1 = m_top;
	auto tempNode2 = stack.m_top;

	while (tempNode1 != nullptr)
	{
		if (tempNode1->value != tempNode2->value)
		{
			return false;
		}

		tempNode1 = tempNode1->m_prevNode;
		tempNode2 = tempNode2->m_prevNode;
	}

	return true;
}
bool CStringStack::operator !=(CStringStack const &stack)const
{
	return !(*this == stack);
}
