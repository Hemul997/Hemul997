#pragma once
#include "stdafx.h"


template <typename Base>
class CPersonImpl : public Base
{
public:

	virtual std::string GetName()
	{
		return m_name;
	}
	
	virtual std::string GetSurname()
	{
		return m_surname;
	}
	virtual std::string GetPatronymic()
	{
		return m_patronymic;
	}
	virtual std::string GetAdress()
	{
		return m_adress;
	}
private:
	std::string m_name;
	std::string m_surname;
	std::string m_patronymic;
	std::string m_adress;
};
