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
		auto currentNode = stack.m_top;
		auto temporaryNode = std::make_shared<Node>();
		temporaryNode->value = currentNode->value;
		m_top = temporaryNode;

		currentNode = currentNode->m_prevNode;

		while (currentNode != nullptr)
		{
			auto newNode = std::make_shared<Node>();
			newNode->value = currentNode->value;
			currentNode = currentNode->m_prevNode;
		}
		m_size = stack.GetSize();
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

	auto firstNode = m_top;
	auto secondNode = stack.m_top;

	while (firstNode != nullptr && secondNode != nullptr)
	{
		if (firstNode->value != secondNode->value)
		{
			return false;
		}

		firstNode = firstNode->m_prevNode;
		secondNode = secondNode->m_prevNode;
	}

	return true;
}
bool CStringStack::operator !=(CStringStack const &stack)const
{
	return !(*this == stack);
}