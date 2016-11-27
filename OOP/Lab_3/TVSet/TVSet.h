#pragma once

class CTVSet
{
public:
	bool IsTurnedOn()const;
	void TurnOn();
	void TurnOff();
	int GetChannel()const;
	bool SelectChannel(int channel);

	int GetPreviousChannel()const;
	
	bool SelectChannel(const std::string & channel);
	bool SetChannelName(int channel, std::string const & channelName);
	bool DeleteChannelName(std::string const & channelName);
	std::string CTVSet::GetChannelName(int channel)const;
	int GetChannelByName(std::string const & channelName)const;
	bool SelectPreviousChannel();
	typedef std::map<int, std::string> ChannelMap;
	auto CTVSet::SearchMap(std::string str)const;
	auto CTVSet::SearchMap(int num)const;
	void CTVSet::PrintMap(std::ostream & out)const;
private:
	bool m_isOn = false;
	int m_selectedChannel = 1;
	int m_prevChannel = 1;
	ChannelMap m_channelMap;
};