// Test.cpp : Defines the entry point for the console application.

#include "../CountWord/CountWord.h"
#include "stdafx.h"


BOOST_AUTO_TEST_SUITE(Count_Word_function)
	BOOST_AUTO_TEST_CASE(cant_count_words_when_empty_input)
	{
		CountWordsMap result = {};
		CountWordsMap  testMap;
		istringstream test("");
		CountWord(test, testMap);
		BOOST_CHECK(result == testMap);
}
	BOOST_AUTO_TEST_CASE(can_count_words_when_not_empty_input)
	{
		CountWordsMap testMap;
		CountWordsMap result = { { "hello", 3 },{ "world", 3 } };
		istringstream test("Hello World\nHELLO wOrLd\thello world");
		CountWord(test, testMap);
		BOOST_CHECK(result == testMap);
	}
BOOST_AUTO_TEST_SUITE_END()