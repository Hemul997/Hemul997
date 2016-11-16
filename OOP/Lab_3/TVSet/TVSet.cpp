#include "stdafx.h"
#include "TVSet.h"
#include <regex>

std::string DeleteSpaces(std::string const & channelName)
{
	std::string str = std::regex_replace(channelName, std::regex("[ ]+"), " ");
	boost::trim(str);
	if (str == " ")
	{
		str = "";
	}
	return str;
}
auto CTVSet::SearchMap(int channel)const
{
	auto foundName = m_channelMap.find(channel);
	return foundName;
}
auto CTVSet::SearchMap(std::string str)const
{
	auto foundNum(std::find_if(m_channelMap.begin(), m_channelMap.end(),
		[&](auto a) {return a.second == str; }));
	return foundNum;
}
bool isAvailableChannel(int channel)
{
	return channel >= 1 && channel <= 99;
}
bool CTVSet::IsTurnedOn()const
{
	return m_isOn;
}

void CTVSet::TurnOn()
{
	m_isOn = true;
}

void CTVSet::TurnOff()
{
	m_isOn = false;
}

int CTVSet::GetChannel()const
{
	return m_isOn ? m_selectedChannel : 0;
}
bool CTVSet::SelectChannel(int channel)
{
	if (isAvailableChannel(channel) && m_isOn)
	{
		m_prevChannel = m_selectedChannel;
		m_selectedChannel = channel;
		return true;
	}
	return false;
}
int CTVSet::GetPreviousChannel()const
{
	return m_prevChannel;
}
bool CTVSet::SelectPreviousChannel()
{
	return SelectChannel(GetPreviousChannel()) && m_isOn;
}
bool CTVSet::SelectChannel(std::string const & channelName)
{
	int num = GetChannelByName(channelName);
	if (num != 0 && m_isOn)
	{
		SelectChannel(num);
		return true;
	}
	else
	{
		return false;
	}
}
int CTVSet::GetChannelByName(std::string const & channelName)const
{
	int num = 0;
	std::string str = DeleteSpaces(channelName);
	if (SearchMap(str) != m_channelMap.end())
	{
		num = SearchMap(str)->first;
	}
	return num;
}
bool CTVSet::SetChannelName(int channel, std::string const & channelName)
{
	std::string str = DeleteSpaces(channelName);
	if (isAvailableChannel(channel) && m_isOn && !str.empty())
	{
		DeleteChannelName(str);
		if (SearchMap(channel) != m_channelMap.end())
		{
			m_channelMap.erase(SearchMap(channel));
		}
		auto it = m_channelMap.begin();
		m_channelMap.insert(it, std::pair<int, std::string>(channel, str));
		return true;
	}
	return false;
}
bool CTVSet::DeleteChannelName(std::string const & channelName)
{
	std::string str = DeleteSpaces(channelName);
	if (SearchMap(str) != m_channelMap.end() && m_isOn)
	{
		m_channelMap.erase(SearchMap(str));
		return true;
	}
	return false;
}
std::string CTVSet::GetChannelName(int channel)const
{
	std::string str;
	if (isAvailableChannel(channel) && m_isOn && SearchMap(channel)!= m_channelMap.end())
	{
		str = SearchMap(channel)->second;
	}
	return str;
}
void CTVSet::PrintMap(std::ostream & out)const
{
	for (auto it = m_channelMap.begin(); it != m_channelMap.end(); ++it)
	{
		out << it->first << " - " << it->second << "\n";
	}
}