#pragma once
class CUrlParsingError 
	: public std::invalid_argument
{
public:
	CUrlParsingError::CUrlParsingError(const std::string &err);
};
