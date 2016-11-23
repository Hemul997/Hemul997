#include "stdafx.h"

using namespace std;


void FindAndReplace(string &text, string const& oldText, string const& newText)
{
	size_t pos = 0;
	while ((pos = text.find(oldText, pos)) != string::npos)
	{
		text.replace(pos, oldText.size(), newText);
		++pos;
	}
}

string HtmlDecode(string const& html)
{
	static map<string, string> htmlDecode =
	{
		{ "&quot;", "\"" },
		{ "&apos;", "\'" },
		{ "&lt;", "<" },
		{ "&gt;", ">" },
		{ "&amp;", "&" }
	};

	string text(html);
	for_each(htmlDecode.begin(), htmlDecode.end(), [&text](pair<string, string> pair) { FindAndReplace(text, pair.first, pair.second); });

	return move(text);
}

bool ReadStream(istream &args, string &line)
{
	if (!args.eof())
	{
		getline(args, line);
		return true;
	}
	return false;
}