#include "stdafx.h"
#include "TVSet.h"

std::string DeleteSpaces(std::string str)
{
	std::string channelName;
	for (size_t i = 0; i < str.size(); ++i)
	{
		if (str[i] != ' ')
		{
			channelName += str[i];
		}
		else
		{
			if (!(str[i] == ' ' && str[i + 1] == str[i]))
			{
				channelName += ' ';
			}
		}
	}
	if (channelName == " ")
	{
		channelName = "";
	}
	return channelName;
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
	bool isAvailableChannel = (channel >= 1) && (channel <= 99);
	if (isAvailableChannel && m_isOn)
	{
		m_prevChannel = m_selectedChannel;
		m_selectedChannel = channel;
		return true;
	}
	return false;
}
int CTVSet::ReturnPreviousChannel()const
{
	return m_prevChannel;
}

bool CTVSet::SelectPreviousChannel()
{
	if (SelectChannel(ReturnPreviousChannel()) && m_isOn)
	{
	    return true;
	}
	return false;
}

bool CTVSet::SelectChannel(const std::string channelName)
{
	if (GetChannelByName(channelName) && m_isOn)
	{
		SelectChannel(ReturnChannelNumber());
		return true;
	}
	else
	{
		return false;
	}
}

bool CTVSet::GetChannelByName(std::string channelName)
{
	boost::trim(channelName);
	channelName = DeleteSpaces(channelName);
	auto foundNum(std::find_if(m_channelMap.begin(), m_channelMap.end(),
		[&](auto a) {return a.second == channelName; }));\
	if(foundNum != m_channelMap.end() && m_isOn)
	{
		m_settedNum = foundNum->first;
		return true;
	}
	return false;
}

bool CTVSet::SetChannelName(int channel, std::string channelName)
{
	bool isAvailableChannel = (channel >= 1) && (channel <= 99);
	boost::trim(channelName);
	channelName = DeleteSpaces(channelName);
	if (isAvailableChannel && m_isOn && !channelName.empty())
	{
		DeleteChannelName(channelName);
		auto foundName = m_channelMap.find(channel);
		if (foundName != m_channelMap.end())
		{
			m_channelMap.erase(foundName);
		}
		auto it = m_channelMap.begin();
		m_channelMap.insert(it, std::pair<int, std::string>(channel, channelName));
		return true;
	}
	return false;
}

bool CTVSet::DeleteChannelName(std::string channelName)
{
	boost::trim(channelName);
	channelName = DeleteSpaces(channelName);
	auto foundNum(std::find_if(m_channelMap.begin(), m_channelMap.end(),
		[&](auto a) {return a.second == channelName; }));
	if (foundNum != m_channelMap.end() && m_isOn)
	{
		m_channelMap.erase(foundNum);
		return true;
	}
	return false;
}

bool CTVSet::GetChannelName(int channel)
{
	bool isAvailableChannel = (channel >= 1) && (channel <= 99);
	if (isAvailableChannel && m_isOn)
	{
		auto foundName = m_channelMap.find(channel);
		if (foundName != m_channelMap.end())
		{
			m_settedName = foundName->second;
			return true;
		}
	}
	return false;
}
int CTVSet::ReturnChannelNumber()const
{
	return m_settedNum;
}
std::string CTVSet::ReturnChannelName()const
{
	return m_settedName;
}