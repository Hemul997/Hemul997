#include "stdafx.h"
#include "../TVSet/RemoteControl.h"
#include "../TVSet/TVSet.h"
#include <sstream>
#include <boost/optional.hpp>

using namespace std;
using boost::optional;
using boost::none;

// Зависимости RemoteControl-а вынесены в родительскую структуру,
// чтобы гарантировать их создание до конструирования самого remote-контрола
struct RemoteControlDependencies
{
	CTVSet tv;
	stringstream input;
	stringstream output;
};

struct RemoteControlFixture : RemoteControlDependencies
{
	CRemoteControl remoteControl;
	
	RemoteControlFixture()
		: remoteControl(tv, input, output)
	{
	}

	// Вспомогательная функция для проверки работы команды command
	// Она принимает ожидаемый номер канала expectedChannel и expectedOutput
	void VerifyCommandHandling(const string& command, const optional<int> & expectedChannel, const string& expectedOutput)
	{
		// Предварительно очищаем содержимое выходного потока
		output = stringstream();
		input = stringstream();
		BOOST_CHECK(input << command);
		BOOST_CHECK(remoteControl.HandleCommand());
		BOOST_CHECK_EQUAL(tv.IsTurnedOn(), expectedChannel.is_initialized());
		BOOST_CHECK_EQUAL(tv.GetChannel(), expectedChannel.get_value_or(0));
		BOOST_CHECK(input.eof());
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}
};

BOOST_FIXTURE_TEST_SUITE(Remote_Control, RemoteControlFixture)

	BOOST_AUTO_TEST_CASE(can_handle_TurnOn_command)
	{
		VerifyCommandHandling("TurnOn", 1, "TV is turned on\n");
	}

	BOOST_AUTO_TEST_CASE(can_turn_off_tv_which_is_on)
	{
		tv.TurnOn();
		VerifyCommandHandling("TurnOff", none, "TV is turned off\n");
	}



	BOOST_AUTO_TEST_CASE(can_print_tv_info)
	{
		VerifyCommandHandling("Info", none, "TV is turned off\n");

		tv.TurnOn();
		tv.SelectChannel(42);
		VerifyCommandHandling("Info", 42, "TV is turned on\nChannel is: 42\n");
	}



	
	BOOST_AUTO_TEST_CASE(can_select_a_valid_channel_when_tv_which_is_on)
	{
		tv.TurnOn();
		VerifyCommandHandling("SelectChannel 42", 42, "Channel selected\n");
	}



	BOOST_AUTO_TEST_CASE(cant_select_channel_when_tv_is_turned_off)
	{
		VerifyCommandHandling("SelectChannel 42", none, "Can't select channel because TV is turned off\n");
		VerifyCommandHandling("SelectChannel 100", none, "Can't select channel because TV is turned off\n");
	}



	BOOST_AUTO_TEST_CASE(cant_select_an_invalid_channel_when_tv_is_on)
	{
		tv.TurnOn();
		tv.SelectChannel(42);
		VerifyCommandHandling("SelectChannel 100", 42, "Invalid channel\n");
		VerifyCommandHandling("SelectChannel 0", 42, "Invalid channel\n");
	}

	BOOST_AUTO_TEST_CASE(can_select_previous_channel_when_tv_is_on)
	{
		tv.TurnOn();
		tv.SelectChannel(42);
		tv.SelectChannel(86);
		VerifyCommandHandling("SelectPreviousChannel", 42, "Previous channel selected\n");
	}
	BOOST_AUTO_TEST_CASE(cant_select_previous_channel_when_tv_is_off)
	{
		tv.TurnOn();
		tv.SelectChannel(42);
		tv.SelectChannel(86);
		tv.TurnOff();
		VerifyCommandHandling("SelectPreviousChannel", none, "Can't select previous channel because TV is turned off\n");
	}
	BOOST_AUTO_TEST_CASE(can_save_previous_channel_when_tv_is_turned_off)
	{
		tv.TurnOn();
		tv.SelectChannel(42);
		tv.SelectChannel(86);
		tv.TurnOff();
		tv.TurnOn();
		VerifyCommandHandling("SelectPreviousChannel", 42, "Previous channel selected\n");
	}
	BOOST_AUTO_TEST_CASE(can_set_channel_name)
	{
		tv.TurnOn();
		VerifyCommandHandling("SetChannelName 5 five", 1, "Name set\n");
	}
	BOOST_AUTO_TEST_CASE(can_print_list_of_name_in_info)
	{
		tv.TurnOn();
		VerifyCommandHandling("SetChannelName 5 five", 1, "Name set\n");
		VerifyCommandHandling("Info", 1, "TV is turned on\nChannel is: 1\n5 - five\n");
	}
	BOOST_AUTO_TEST_CASE(can_select_channel_by_name)
	{
		tv.TurnOn();
		VerifyCommandHandling("SetChannelName 5 five", 1, "Name set\n");
		VerifyCommandHandling("SelectChannel five", 5, "Channel selected\n");
	}
	BOOST_AUTO_TEST_CASE(can_get_channel_name_by_number)
	{
		tv.TurnOn();
		VerifyCommandHandling("SetChannelName 5 five", 1, "Name set\n");
		VerifyCommandHandling("GetChannelName 5", 1, "five is gotten channel name\n");
	}
	BOOST_AUTO_TEST_CASE(can_get_channel_by_name)
	{
		tv.TurnOn();
		VerifyCommandHandling("SetChannelName 5 five", 1, "Name set\n");
		VerifyCommandHandling("GetChannelByName five", 1, "5 is gotten channel number\n");
	}
	BOOST_AUTO_TEST_CASE(can_print_tv_info_after_setting_name)
	{
		VerifyCommandHandling("Info", none, "TV is turned off\n");
		tv.TurnOn();
		VerifyCommandHandling("SetChannelName 5 five", 1, "Name set\n");
		VerifyCommandHandling("Info", 1, "TV is turned on\nChannel is: 1\n5 - five\n");
	}
	BOOST_AUTO_TEST_CASE(can_change_old_name_of_channel_to_the_new)
	{
		VerifyCommandHandling("Info", none, "TV is turned off\n");

		tv.TurnOn();
		VerifyCommandHandling("SetChannelName 5 give", 1, "Name set\n");
		VerifyCommandHandling("SetChannelName 5 five", 1, "Name set\n");
		VerifyCommandHandling("Info", 1, "TV is turned on\nChannel is: 1\n5 - five\n");
	}
	BOOST_AUTO_TEST_CASE(can_delete_name_of_channel_after_setting_name)
	{
        tv.TurnOn();
		VerifyCommandHandling("SetChannelName 5 give", 1, "Name set\n");
		VerifyCommandHandling("Info", 1, "TV is turned on\nChannel is: 1\n5 - give\n");
		VerifyCommandHandling("DeleteChannelName give", 1, "Name has been deleted\n");
		VerifyCommandHandling("Info", 1, "TV is turned on\nChannel is: 1\n");
	}
	BOOST_AUTO_TEST_CASE(cant_delete_name_of_channel_without_setting_name)
	{
		tv.TurnOn();
		VerifyCommandHandling("DeleteChannelName give", 1, "The channel was not found by name\n");
	}
	BOOST_AUTO_TEST_CASE(can_select_channel_by_empty_name_without_setting_empty_name)
	{
		tv.TurnOn();
		VerifyCommandHandling("SelectChannel", 1, "Invalid channel\n");
	}

BOOST_AUTO_TEST_SUITE_END()