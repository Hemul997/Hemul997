#include "stdafx.h"
#include "RemoteControl.h"
#include "TVSet.h"


using namespace std;
using namespace std::placeholders;



CRemoteControl::CRemoteControl(CTVSet & tv, std::istream & input, std::ostream & output)
	: m_tv(tv)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		{ "TurnOn", [this](istream & strm) {
				return TurnOn(strm);
			} },
		{ "TurnOff", bind(&CRemoteControl::TurnOff, this, _1) },
		{ "Info", bind(&CRemoteControl::Info, this, _1) },
		{ "SelectChannel", bind(&CRemoteControl::SelectChannel, this, _1) },
		{ "SelectPreviousChannel", bind(&CRemoteControl::SelectPreviousChannel, this, _1) },
		{ "SetChannelName", bind(&CRemoteControl::SetChannelName, this, _1) },
		{ "DeleteChannelName", bind(&CRemoteControl::DeleteChannelName, this, _1) },
		{ "GetChannelName", bind(&CRemoteControl::GetChannelName, this, _1) },
		{ "GetChannelByName", bind(&CRemoteControl::GetChannelByName, this, _1) }
	})
{
}

bool CRemoteControl::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}
	
	return false;
}

bool CRemoteControl::TurnOn(std::istream & /*args*/)
{
	m_tv.TurnOn();
	m_output << "TV is turned on" << endl;
	return true;
}

bool CRemoteControl::TurnOff(std::istream & /*args*/)
{
	m_tv.TurnOff();
	m_output << "TV is turned off" << endl;
	return true;
}

bool CRemoteControl::Info(std::istream & /*args*/)
{
	string info = (m_tv.IsTurnedOn())
		? ("TV is turned on\nChannel is: " + to_string(m_tv.GetChannel()) + "\n")
		: "TV is turned off\n";

	m_output << info;
	if(m_tv.IsTurnedOn())
	{
		for (auto it = m_tv.m_channelMap.begin(); it != m_tv.m_channelMap.end(); ++it)
		{
			m_output << it->first << " - " << it->second << "\n";
		}
	}
	return true;
}

bool CRemoteControl::SelectChannel(std::istream & args)
{
	if (m_tv.IsTurnedOn())
	{
		int selectedChannel = 0;
		string channelName;
		getline(args, channelName);
		boost::trim(channelName);
		if (all_of(channelName.begin(), channelName.end(), isdigit) && !channelName.empty())
		{
			selectedChannel = stoi(channelName);
		}
		if (m_tv.SelectChannel(selectedChannel) || m_tv.SelectChannel(channelName))
		{
			m_output << "Channel selected\n";
		}
		else
		{
			m_output << "Invalid channel\n";
		}
	}
	else
	{
		m_output << "Can't select channel because TV is turned off\n";
	}
	return true;
}

bool CRemoteControl::SelectPreviousChannel(std::istream & /*args*/)
{
	if (m_tv.SelectPreviousChannel())
	{
		m_output << "Previous channel selected\n";
	}
	else
	{
		m_output << "Can't select previous channel because TV is turned off\n";
	}
	return true;
}

bool CRemoteControl::SetChannelName(std::istream & args)
{
	if (m_tv.IsTurnedOn())
	{
		int num;
		string str;
		args >> num;
		getline(args, str);
		if (m_tv.SetChannelName(num, str))
		{
			m_output << "Name set\n";
		}
		else
		{
			m_output << "Invalid channel\n";
		}
	}
	else
	{
		m_output << "Can't set channel name because TV is turned off\n";
	}
	return true;
}

bool CRemoteControl::DeleteChannelName(std::istream & args)
{
	if (m_tv.IsTurnedOn())
	{
		string str;
		getline(args, str);
		if (m_tv.DeleteChannelName(str))
		{
			m_output << "Name has been deleted\n";
		}
		else
		{
			m_output << "The channel was not found by name\n";
		}
	}
	else
	{
		m_output << "Can't delete channel name because TV is turned off\n";
	}
	return true;
}

bool CRemoteControl::GetChannelName(std::istream & args)
{
	if (m_tv.IsTurnedOn())
	{
		int num;
		args >> num;
		if (m_tv.GetChannelName(num))
		{
			m_output << m_tv.ReturnChannelName() << " is gotten channel name\n";
		}
		else
		{
			m_output << "The channel was not found by number\n";
		}
	}
	else
	{
		m_output << "Can't get channel because TV is turned off\n";
	}
	return true;
}
bool CRemoteControl::GetChannelByName(std::istream & args)
{
	if (m_tv.IsTurnedOn())
	{
		string str;
		getline(args, str);
		if (m_tv.GetChannelByName(str))
		{
			m_output << m_tv.ReturnChannelNumber() << " is gotten channel number\n";
		}
		else
		{
			m_output << "The channel was not found by name\n";
		}
	}
	else
	{
		m_output << "Can't get channel because TV is turned off\n";
	}
	return true;
}