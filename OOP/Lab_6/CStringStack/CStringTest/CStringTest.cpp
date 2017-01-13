// CStringTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../CStringStack/CStringStack.h"
struct StringStack
{
	CStringStack stringStack;
};

BOOST_FIXTURE_TEST_SUITE(My_stack, StringStack)
	BOOST_AUTO_TEST_SUITE(Stack_Class)
		BOOST_AUTO_TEST_CASE(is_empty_by_default)
		{
			BOOST_CHECK(stringStack.IsEmpty());
		}
		BOOST_AUTO_TEST_CASE(can_not_get_last_element_when_stack_is_empty)
		{
			BOOST_CHECK_THROW(stringStack.GetLastElement(), std::underflow_error);
		}
		BOOST_AUTO_TEST_CASE(can_push_element)
		{

			stringStack.Push("String");
			BOOST_CHECK(!stringStack.IsEmpty());
			BOOST_CHECK_EQUAL(stringStack.GetLastElement(), "String");
		}
		BOOST_AUTO_TEST_CASE(can_pop_element)
		{
			stringStack.Push("string");
			BOOST_CHECK(!stringStack.IsEmpty());

			stringStack.Pop();
			BOOST_CHECK(stringStack.IsEmpty());
		}
		BOOST_AUTO_TEST_CASE(cant_pop_elements_when_stack_is_empty)
		{
			BOOST_CHECK_THROW(stringStack.Pop(), std::underflow_error);
		}
		BOOST_AUTO_TEST_CASE(can_get_size_of_stack)
		{
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
				stringStack.Push("string");
			}
			BOOST_CHECK_EQUAL(stringStack.GetSize(), currentSize);

			stringStack.Clear();
			BOOST_CHECK_EQUAL(stringStack.GetSize(), expectedSize);
		}
		BOOST_AUTO_TEST_CASE(can_be_constructed_from_other_stack)
		{
			stringStack.Push("word");
			CStringStack secondStack(stringStack);
			BOOST_CHECK_EQUAL(secondStack.GetSize(), stringStack.GetSize());
			BOOST_CHECK_EQUAL(secondStack.GetLastElement(), stringStack.GetLastElement());
		}
		BOOST_AUTO_TEST_CASE(can_compare_stacks)
		{
			CStringStack newStringStack;

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
				stringStack.Push(std::to_string(i));
			}

			CStringStack newStringStack(stringStack);

			BOOST_CHECK_EQUAL(newStringStack.GetSize(), stringStack.GetSize());
			BOOST_CHECK(newStringStack == stringStack);
		}

		BOOST_AUTO_TEST_CASE(can_not_be_copied_by_itself)
		{
			for (size_t i = 0; i < 10; ++i)
			{
				stringStack.Push(std::to_string(i));
			}
			CStringStack prevStringStackState = stringStack;
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
				stringStack.Push(std::to_string(i));
			}
			CStringStack prevStringStackState = stringStack;
			CStringStack newStringStack = (std::move(stringStack));
			BOOST_CHECK(stringStack.IsEmpty());
			BOOST_CHECK(newStringStack == prevStringStackState);
		}

		BOOST_AUTO_TEST_CASE(can_not_be_moved_by_itself)
		{
			for (size_t i = 0; i < 5; ++i)
			{
				stringStack.Push(std::to_string(i));
			}
					
			CStringStack prevStringStackState = stringStack;
						
			stringStack = std::move(stringStack);
			BOOST_CHECK(stringStack == prevStringStackState);
			BOOST_CHECK_EQUAL(stringStack.GetSize(), (size_t)5);
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()