// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../HtmlDecode/HtmlDecode.h"
#include <sstream>
#include <iostream>
using namespace std;


BOOST_AUTO_TEST_SUITE(Find_and_replace_function)
	BOOST_AUTO_TEST_CASE(nothing_to_replace)
	{
		string text = "test string";
		string oldText = "old";
		string newText = "new";
		string correct = string(text);
		FindAndReplace(text, oldText, newText);

		BOOST_CHECK(text.compare(correct) == 0);
	}
	BOOST_AUTO_TEST_CASE(replace_one_time)
	{
		string text = "test string";
		string oldText = "test";
		string newText = "new";
		string correct = "new string";
		FindAndReplace(text, oldText, newText);

		BOOST_CHECK(text.compare(correct) == 0);
	}
	BOOST_AUTO_TEST_CASE(replace_several_times)
	{
		string text = "first test, second test, third test";
		string oldText = "test";
		string newText = "word";
		string correct = "first word, second word, third word";
		FindAndReplace(text, oldText, newText);

		BOOST_CHECK(text.compare(correct) == 0);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Html_decoding)
	BOOST_AUTO_TEST_CASE(nothing_to_change)
	{
		string text = "test string";
		string correct = string(text);
		BOOST_CHECK(HtmlDecode(text).compare(correct) == 0);
	}
	BOOST_AUTO_TEST_CASE(lt_and_gt_chars)
	{
		string text = "Her &lt;dream&gt;";
		string correct = "Her <dream>";
		BOOST_CHECK(HtmlDecode(text).compare(correct) == 0);
	}
	BOOST_AUTO_TEST_CASE(apostrophes)
	{
		string text = "It&apos;s your home";
		string correct = "It's your home";
		BOOST_CHECK(HtmlDecode(text).compare(correct) == 0);
	}
	BOOST_AUTO_TEST_CASE(quotes)
	{
		string text = "&quot;Hello, World&quot;";
		string correct = "\"Hello, World\"";
		BOOST_CHECK(HtmlDecode(text).compare(correct) == 0);
	}
	BOOST_AUTO_TEST_CASE(ampersand)
	{
		string text = "string text = &amp;line;";
		string correct = "string text = &line;";
		BOOST_CHECK(HtmlDecode(text).compare(correct) == 0);
	}
	BOOST_AUTO_TEST_CASE(ampersand2)
	{
		string text = "string text = &amp;amp;line;";
		string correct = "string text = &amp;line;";
		BOOST_CHECK(HtmlDecode(text).compare(correct) == 0);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Reading_from_stream)
	BOOST_AUTO_TEST_CASE(empty)
	{
		stringstream stream;

		// Set stream to EOF
		getline(stream, string());

		string line;
		bool gotLine = ReadStream(stream, line);
		BOOST_CHECK(!gotLine);
		BOOST_CHECK(line.empty());
	}
	BOOST_AUTO_TEST_CASE(one_line)
	{
		stringstream stream;
		string correct = "Cat &lt; says&gt; &quot; Meow&quot; .M&amp; M&apos; s\n";
		stream << correct;
		string line;
		BOOST_CHECK(ReadStream(stream, line));
		BOOST_CHECK(line.compare(correct));
	}
	BOOST_AUTO_TEST_CASE(several_lines)
	{
		stringstream stream;
		string firstLine = "Cat &lt; says&gt; &quot; Meow&quot; .M&amp; M&apos; s\n";
		string secondLine = "&lt;p&gt;&quot;This is a &apos;paragraph&apos;&quot;&lt;/p&gt;\n";
		stream << firstLine << secondLine;
		string line;

		BOOST_CHECK(ReadStream(stream, line));
		BOOST_CHECK(line.compare(firstLine));
		BOOST_CHECK(ReadStream(stream, line));
		BOOST_CHECK(line.compare(secondLine));
	}
BOOST_AUTO_TEST_SUITE_END()