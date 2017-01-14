// CStringTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../CStringStack/CStringStack.h"
struct StringStack_
{
	CStringStack stack;
};

BOOST_FIXTURE_TEST_SUITE(My_string_stack, StringStack_)
	
	BOOST_AUTO_TEST_CASE(is_empty_by_default)
	{
		BOOST_CHECK(stack.IsEmpty());
	}
	BOOST_AUTO_TEST_CASE(can_not_get_last_element_when_stack_is_empty)
	{
		BOOST_CHECK_THROW(stack.GetLastElement(), std::underflow_error);
	}
	BOOST_AUTO_TEST_CASE(can_push_element)
	{

		stack.Push("String");
		BOOST_CHECK(!stack.IsEmpty());
		BOOST_CHECK_EQUAL(stack.GetLastElement(), "String");
	}
	BOOST_AUTO_TEST_CASE(can_pop_element)
	{
		stack.Push("string");
		BOOST_CHECK(!stack.IsEmpty());

		stack.Pop();
		BOOST_CHECK(stack.IsEmpty());
	}
	BOOST_AUTO_TEST_CASE(cant_pop_elements_when_stack_is_empty)
	{
		BOOST_CHECK_THROW(stack.Pop(), std::underflow_error);
	}
	BOOST_AUTO_TEST_CASE(can_get_size_of_stack)
	{
		stack.Push("word");
		stack.Push("my");
		BOOST_CHECK_EQUAL(stack.GetSize(), (size_t)2);
	}
	BOOST_AUTO_TEST_CASE(can_delete_all_elements_in_stack)
	{
		size_t currentSize = 3;
		size_t expectedSize = 0;

		for (size_t i = 0; i < currentSize; ++i)
		{
			stack.Push("string");
		}
		BOOST_CHECK_EQUAL(stack.GetSize(), currentSize);

		stack.Clear();
		BOOST_CHECK_EQUAL(stack.GetSize(), expectedSize);
	}
	BOOST_AUTO_TEST_CASE(can_be_constructed_from_other_stack)
	{
		stack.Push("word");
		CStringStack secondStack(stack);
		BOOST_CHECK_EQUAL(secondStack.GetSize(), stack.GetSize());
		BOOST_CHECK_EQUAL(secondStack.GetLastElement(), stack.GetLastElement());
	}
	BOOST_AUTO_TEST_CASE(can_compare_stacks)
	{
		CStringStack newStringStack;

		newStringStack.Push("This world");
		stack.Push("This world");

		BOOST_CHECK(newStringStack == stack);

		stack.Push("This world is mine");
		BOOST_CHECK(newStringStack != stack);
	}

	BOOST_AUTO_TEST_CASE(can_be_copied)
	{
		for (size_t i = 0; i < 10; ++i)
		{
			stack.Push(std::to_string(i));
		}

		CStringStack newStringStack(stack);

		BOOST_CHECK_EQUAL(newStringStack.GetSize(), stack.GetSize());
		BOOST_CHECK(newStringStack == stack);
	}
	BOOST_AUTO_TEST_CASE(can_not_copy_empty_stack)
	{
		CStringStack newStack = stack;
		BOOST_CHECK(newStack.IsEmpty());
	}
	BOOST_AUTO_TEST_CASE(can_not_be_copied_by_itself)
	{
		for (size_t i = 0; i < 10; ++i)
		{
			stack.Push(std::to_string(i));
		}
		CStringStack prevStringStackState = stack;
		BOOST_CHECK(prevStringStackState == stack);

		BOOST_CHECK_EQUAL(stack.GetSize(), (size_t)10);

		stack = stack;

		BOOST_CHECK_EQUAL(stack.GetSize(), (size_t)10);
		BOOST_CHECK(stack == prevStringStackState);
	}

	BOOST_AUTO_TEST_CASE(can_be_moved)
	{
		for (size_t i = 0; i < 10; ++i)
		{
			stack.Push(std::to_string(i));
		}
		CStringStack prevStringStackState = stack;
		CStringStack newStringStack = (std::move(stack));
		BOOST_CHECK(stack.IsEmpty());
		BOOST_CHECK(newStringStack == prevStringStackState);
	}

	BOOST_AUTO_TEST_CASE(can_not_be_moved_by_itself)
	{
		for (size_t i = 0; i < 5; ++i)
		{
			stack.Push(std::to_string(i));
		}
					
		CStringStack prevStringStackState = stack;
						
		stack = std::move(stack);
		BOOST_CHECK(stack == prevStringStackState);
		BOOST_CHECK_EQUAL(stack.GetSize(), (size_t)5);
	}

BOOST_AUTO_TEST_SUITE_END()