// CMyStackTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../CMyStack/CMyStack.h"

struct MyStack
{
	CMyStack<int> intStack;
	CMyStack<std::string> stringStack;
};
struct ThrowableStruct
{
	ThrowableStruct(bool throws)
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
BOOST_FIXTURE_TEST_SUITE(My_stack, MyStack)
	BOOST_AUTO_TEST_CASE(in_constructor)
	{
		CMyStack<ThrowableStruct> stack;
		BOOST_REQUIRE_NO_THROW(stack.Push(ThrowableStruct(false)));
		BOOST_REQUIRE_THROW(stack.Push(ThrowableStruct(true)), std::exception);
	}

BOOST_AUTO_TEST_SUITE(Stack_Class)
		BOOST_AUTO_TEST_CASE(is_empty_by_default)
		{
			BOOST_CHECK(intStack.IsEmpty());
			BOOST_CHECK(stringStack.IsEmpty());
		}
		BOOST_AUTO_TEST_CASE(can_not_get_last_element_when_stack_is_empty)
		{
			BOOST_CHECK_THROW(intStack.GetLastElement(), std::underflow_error);
			BOOST_CHECK_THROW(stringStack.GetLastElement(), std::underflow_error);
		}
		BOOST_AUTO_TEST_CASE(can_push_element)
		{
			intStack.Push(4);
			BOOST_CHECK(!intStack.IsEmpty());
			BOOST_CHECK_EQUAL(intStack.GetLastElement(), 4);

			stringStack.Push("String");
			BOOST_CHECK(!stringStack.IsEmpty());
			BOOST_CHECK_EQUAL(stringStack.GetLastElement(), "String");
		}
		BOOST_AUTO_TEST_CASE(can_pop_element)
		{
			intStack.Push(19);
			BOOST_CHECK(!intStack.IsEmpty());

			intStack.Pop();
			BOOST_CHECK(intStack.IsEmpty());

			stringStack.Push("string");
			BOOST_CHECK(!stringStack.IsEmpty());

			stringStack.Pop();
			BOOST_CHECK(stringStack.IsEmpty());
		}
		BOOST_AUTO_TEST_CASE(cant_pop_elements_when_stack_is_empty)
		{
			BOOST_CHECK_THROW(intStack.Pop(), std::underflow_error);

			BOOST_CHECK_THROW(stringStack.Pop(), std::underflow_error);
		}
		BOOST_AUTO_TEST_CASE(can_get_size_of_stack)
		{
			intStack.Push(1);
			BOOST_CHECK_EQUAL(intStack.GetSize(), (size_t)1);

			stringStack.Push("word");
			stringStack.Push("my");
			BOOST_CHECK_EQUAL(stringStack.GetSize(), (size_t)2);
		}
		BOOST_AUTO_TEST_CASE(can_delete_all_elements_in_stack)
		{
			size_t currentSize = 3;
			size_t expectedSize = 0;

			for (size_t i = 0; i < currentSize; ++i)
			{
				intStack.Push((int)i);
			}
			BOOST_CHECK_EQUAL(intStack.GetSize(), currentSize);

			intStack.Clear();
			BOOST_CHECK_EQUAL(intStack.GetSize(), expectedSize);

			for (size_t i = 0; i < currentSize; ++i)
			{
				stringStack.Push("string");
			}
			BOOST_CHECK_EQUAL(stringStack.GetSize(), currentSize);

			stringStack.Clear();
			BOOST_CHECK_EQUAL(stringStack.GetSize(), expectedSize);
		}
		BOOST_AUTO_TEST_CASE(can_be_constructed_from_other_stack)
		{
			intStack.Push(97);
			CMyStack<int> secondStack(intStack);
			BOOST_CHECK_EQUAL(secondStack.GetSize(), intStack.GetSize());
			BOOST_CHECK_EQUAL(secondStack.GetLastElement(), intStack.GetLastElement());
		}
		BOOST_AUTO_TEST_CASE(can_compare_stacks)
		{
			CMyStack<int> newIntStack;

			newIntStack.Push(12);
			intStack.Push(12);
			BOOST_CHECK(intStack == newIntStack);

			intStack.Push(42);
			newIntStack.Push(666);

			BOOST_CHECK(intStack != newIntStack);

			CMyStack<std::string> newStringStack;

			newStringStack.Push("This world");
			stringStack.Push("This world");

			BOOST_CHECK(newStringStack == stringStack);

			stringStack.Push("This world is mine");
			BOOST_CHECK(newStringStack != stringStack);
		}

		BOOST_AUTO_TEST_CASE(can_be_copied)
		{
			for (size_t i = 0; i < 10; ++i)
			{
				intStack.Push((int)i);
				stringStack.Push(std::to_string(i));
			}

			CMyStack<int> newIntStack(intStack);

			BOOST_CHECK_EQUAL(newIntStack.GetSize(), intStack.GetSize());
			BOOST_CHECK(newIntStack == intStack);

			CMyStack<std::string> newStringStack(stringStack);

			BOOST_CHECK_EQUAL(newStringStack.GetSize(), stringStack.GetSize());
			BOOST_CHECK(newStringStack == stringStack);
		}

		BOOST_AUTO_TEST_CASE(can_not_be_copied_by_itself)
		{
			for (size_t i = 0; i < 10; ++i)
			{
				intStack.Push((int)i);
				stringStack.Push(std::to_string(i));
			}

			CMyStack<int> prevIntStackState = intStack;
			BOOST_CHECK(prevIntStackState == intStack);

			BOOST_CHECK_EQUAL(intStack.GetSize(), (size_t)10);

			intStack = intStack;

			BOOST_CHECK_EQUAL(intStack.GetSize(), (size_t)10);
			BOOST_CHECK(intStack == prevIntStackState);



			CMyStack<std::string> prevStringStackState = stringStack;
			BOOST_CHECK(prevStringStackState == stringStack);

			BOOST_CHECK_EQUAL(stringStack.GetSize(), (size_t)10);

			stringStack = stringStack;

			BOOST_CHECK_EQUAL(stringStack.GetSize(), (size_t)10);
			BOOST_CHECK(stringStack == prevStringStackState);
		}

		BOOST_AUTO_TEST_CASE(can_be_moved)
		{
			for (size_t i = 0; i < 10; ++i)
			{
				intStack.Push((int)i);
				stringStack.Push(std::to_string(i));
			}

			CMyStack<int> prevIntStackState = intStack;
			CMyStack<std::string> prevStringStackState = stringStack;

			CMyStack<int> newIntStack(std::move(intStack));
			BOOST_CHECK(intStack.IsEmpty());
			BOOST_CHECK(newIntStack == prevIntStackState);

			CMyStack<std::string> newStringStack = (std::move(stringStack));
			BOOST_CHECK(stringStack.IsEmpty());
			BOOST_CHECK(newStringStack == prevStringStackState);
		}

		BOOST_AUTO_TEST_CASE(can_not_be_moved_by_itself)
		{
			for (size_t i = 0; i < 5; ++i)
			{
				intStack.Push((int)i);
				stringStack.Push(std::to_string(i));
			}

			CMyStack<int> prevIntStackState = intStack;
			CMyStack<std::string> prevStringStackState = stringStack;

			intStack = std::move(intStack);
			BOOST_CHECK(intStack == prevIntStackState);
			BOOST_CHECK_EQUAL(intStack.GetSize(), (size_t)5);

			stringStack = std::move(stringStack);
			BOOST_CHECK(stringStack == prevStringStackState);
			BOOST_CHECK_EQUAL(stringStack.GetSize(), (size_t)5);
		}
	BOOST_AUTO_TEST_SUITE_END()
	
BOOST_AUTO_TEST_SUITE_END()