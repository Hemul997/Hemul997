#pragma once

#include <string>
using namespace std;

void FindAndReplace(string &text, string const& oldText, string const& newText);
string HtmlDecode(string const& html);
bool ReadStream(istream &args, string &line);