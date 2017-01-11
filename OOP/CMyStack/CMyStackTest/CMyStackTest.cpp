// CMyStackTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../CMyStack/CMyStack.h"

struct MyStack
{
	CMyStack<int> IntStack;
	CMyStack<std::string> StringStack;
};

BOOST_FIXTURE_TEST_SUITE(My_stack, MyStack)
	BOOST_AUTO_TEST_SUITE(Stack_Class)
		BOOST_AUTO_TEST_CASE(is_empty_by_default)
		{
			BOOST_CHECK(IntStack.IsEmpty());
			BOOST_CHECK(StringStack.IsEmpty());
		}
		BOOST_AUTO_TEST_CASE(can_not_get_last_element_when_stack_is_empty)
		{
			BOOST_CHECK_THROW(IntStack.GetLastElement(), std::underflow_error);
			BOOST_CHECK_THROW(StringStack.GetLastElement(), std::underflow_error);
		}
		BOOST_AUTO_TEST_CASE(can_push_element)
		{
			IntStack.Push(4);
			BOOST_CHECK(!IntStack.IsEmpty());
			BOOST_CHECK_EQUAL(IntStack.GetLastElement(), 4);

			StringStack.Push("String");
			BOOST_CHECK(!StringStack.IsEmpty());
			BOOST_CHECK_EQUAL(StringStack.GetLastElement(), "String");
		}
		BOOST_AUTO_TEST_CASE(can_pop_element)
		{
			IntStack.Push(19);
			BOOST_CHECK(!IntStack.IsEmpty());

			IntStack.Pop();
			BOOST_CHECK(IntStack.IsEmpty());

			StringStack.Push("string");
			BOOST_CHECK(!StringStack.IsEmpty());

			StringStack.Pop();
			BOOST_CHECK(StringStack.IsEmpty());
		}
		BOOST_AUTO_TEST_CASE(cant_pop_elements_when_stack_is_empty)
		{
			BOOST_CHECK_THROW(IntStack.Pop(), std::underflow_error);

			BOOST_CHECK_THROW(StringStack.Pop(), std::underflow_error);
		}
		BOOST_AUTO_TEST_CASE(can_get_size_of_stack)
		{
			IntStack.Push(1);
			BOOST_CHECK_EQUAL(IntStack.GetSize(), (size_t)1);

			StringStack.Push("word");
			StringStack.Push("my");
			BOOST_CHECK_EQUAL(StringStack.GetSize(), (size_t)2);
		}
		BOOST_AUTO_TEST_CASE(can_delete_all_elements_in_stack)
		{
			size_t currentSize = 3;
			size_t expectedSize = 0;

			for (size_t i = 0; i < currentSize; ++i)
			{
				IntStack.Push((int)i);
			}
			BOOST_CHECK_EQUAL(IntStack.GetSize(), currentSize);

			IntStack.Clear();
			BOOST_CHECK_EQUAL(IntStack.GetSize(), expectedSize);

			for (size_t i = 0; i < currentSize; ++i)
			{
				StringStack.Push("string");
			}
			BOOST_CHECK_EQUAL(StringStack.GetSize(), currentSize);

			StringStack.Clear();
			BOOST_CHECK_EQUAL(StringStack.GetSize(), expectedSize);
		}
		BOOST_AUTO_TEST_CASE(can_be_constructed_from_other_stack)
		{
			IntStack.Push(97);
			CMyStack<int> secondStack(IntStack);
			BOOST_CHECK_EQUAL(secondStack.GetSize(), IntStack.GetSize());
			BOOST_CHECK_EQUAL(secondStack.GetLastElement(), IntStack.GetLastElement());
		}
		BOOST_AUTO_TEST_CASE(can_compare_stacks)
		{
			CMyStack<int> newIntStack;

			newIntStack.Push(12);
			IntStack.Push(12);
			BOOST_CHECK(IntStack == newIntStack);

			IntStack.Push(42);
			newIntStack.Push(666);

			BOOST_CHECK(IntStack != newIntStack);

			CMyStack<std::string> newStringStack;

			newStringStack.Push("This world");
			StringStack.Push("This world");

			BOOST_CHECK(newStringStack == StringStack);

			StringStack.Push("This world is mine");
			BOOST_CHECK(newStringStack != StringStack);
		}

		BOOST_AUTO_TEST_CASE(can_be_copied)
		{
			for (size_t i = 0; i < 10; ++i)
			{
				IntStack.Push((int)i);
				StringStack.Push(std::to_string(i));
			}

			CMyStack<int> newIntStack(IntStack);

			BOOST_CHECK_EQUAL(newIntStack.GetSize(), IntStack.GetSize());
			BOOST_CHECK(newIntStack == IntStack);

			CMyStack<std::string> newStringStack(StringStack);

			BOOST_CHECK_EQUAL(newStringStack.GetSize(), StringStack.GetSize());
			BOOST_CHECK(newStringStack == StringStack);
		}

		BOOST_AUTO_TEST_CASE(can_not_be_copied_by_itself)
		{
			for (size_t i = 0; i < 10; ++i)
			{
				IntStack.Push((int)i);
				StringStack.Push(std::to_string(i));
			}

			CMyStack<int> prevIntStackState = IntStack;
			BOOST_CHECK(prevIntStackState == IntStack);

			BOOST_CHECK_EQUAL(IntStack.GetSize(), (size_t)10);

			IntStack = IntStack;

			BOOST_CHECK_EQUAL(IntStack.GetSize(), (size_t)10);
			BOOST_CHECK(IntStack == prevIntStackState);



			CMyStack<std::string> prevStringStackState = StringStack;
			BOOST_CHECK(prevStringStackState == StringStack);

			BOOST_CHECK_EQUAL(StringStack.GetSize(), (size_t)10);

			StringStack = StringStack;

			BOOST_CHECK_EQUAL(StringStack.GetSize(), (size_t)10);
			BOOST_CHECK(StringStack == prevStringStackState);
		}

		BOOST_AUTO_TEST_CASE(can_be_moved)
		{
			for (size_t i = 0; i < 10; ++i)
			{
				IntStack.Push((int)i);
				StringStack.Push(std::to_string(i));
			}

			CMyStack<int> prevIntStackState = IntStack;
			CMyStack<std::string> prevStringStackState = StringStack;

			CMyStack<int> newIntStack(std::move(IntStack));
			BOOST_CHECK(IntStack.IsEmpty());
			BOOST_CHECK(newIntStack == prevIntStackState);

			CMyStack<std::string> newStringStack = (std::move(StringStack));
			BOOST_CHECK(StringStack.IsEmpty());
			BOOST_CHECK(newStringStack == prevStringStackState);
		}

		BOOST_AUTO_TEST_CASE(can_not_be_moved_by_itself)
		{
			for (size_t i = 0; i < 5; ++i)
			{
				IntStack.Push((int)i);
				StringStack.Push(std::to_string(i));
			}

			CMyStack<int> prevIntStackState = IntStack;
			CMyStack<std::string> prevStringStackState = StringStack;

			IntStack = std::move(IntStack);
			BOOST_CHECK(IntStack == prevIntStackState);
			BOOST_CHECK_EQUAL(IntStack.GetSize(), (size_t)5);

			StringStack = std::move(StringStack);
			BOOST_CHECK(StringStack == prevStringStackState);
			BOOST_CHECK_EQUAL(StringStack.GetSize(), (size_t)5);
		}
	BOOST_AUTO_TEST_SUITE_END()
	
BOOST_AUTO_TEST_SUITE_END()