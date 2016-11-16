#pragma once

class CTVSet
{
public:
	bool IsTurnedOn()const;
	void TurnOn();
	void TurnOff();
	int GetChannel()const;
	bool SelectChannel(int channel);
	int ReturnPreviousChannel()const;
	bool SelectChannel(const std::string channel);
	bool SetChannelName(int num, std::string channelNam);
	bool DeleteChannelName(std::string channelName);
	bool GetChannelName(int channel);
	bool GetChannelByName(std::string channelName);
	bool CTVSet::SelectPreviousChannel();
	typedef std::map<int, std::string> ChannelMap;
	ChannelMap m_channelMap;
	std::string CTVSet::ReturnChannelName()const;
	int CTVSet::ReturnChannelNumber()const;
private:
	bool m_isOn = false;
	int m_selectedChannel = 1;
	int m_prevChannel = 1;
	int m_settedNum = 0;
	std::string m_settedName;
};