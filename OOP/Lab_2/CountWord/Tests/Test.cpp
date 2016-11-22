// Test.cpp : Defines the entry point for the console application.

#include "../CountWord/CountWord.h"
#include "stdafx.h"


BOOST_AUTO_TEST_SUITE(Count_Word_function)
	BOOST_AUTO_TEST_CASE(cant_count_words_when_empty_input)
	{
		CountWordsMap result = {};
		CountWordsMap  testMap;
		wistringstream test(L"");
		CountWord(test, testMap);
		BOOST_CHECK(result == testMap);
}
	BOOST_AUTO_TEST_CASE(can_count_words_when_not_empty_input)
	{
		CountWordsMap testMap;
		CountWordsMap result = { { L"hello", 3 },{ L"world", 3 } };
		wistringstream test(L"Hello World\nHELLO wOrLd\thello world");
		CountWord(test, testMap);
		BOOST_CHECK(result == testMap);
	}
	BOOST_AUTO_TEST_CASE(can_count_russian_words_when_not_empty_input)
	{
		CountWordsMap testMap;
		CountWordsMap result = { { L"привет", 3 },{ L"мир", 3 } };
		wistringstream test(L"Привет Мир\nПРИвет миР\tпРиВеТ Мир");
		CountWord(test, testMap);
		BOOST_CHECK(result == testMap);
	}
BOOST_AUTO_TEST_SUITE_END()