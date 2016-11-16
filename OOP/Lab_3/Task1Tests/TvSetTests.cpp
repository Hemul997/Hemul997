#include "stdafx.h"
#include "../TVSet/TVSet.h"

/*
Телевизор
	изначально выключен
*/

struct TVSetFixture
{
	CTVSet tv;
};
// Телевизор 
BOOST_FIXTURE_TEST_SUITE(TVSet, TVSetFixture)
	// изначально выключен
	BOOST_AUTO_TEST_CASE(is_turned_off_by_default)
	{
		BOOST_CHECK(!tv.IsTurnedOn());
	}
	// не может переключать канал в выключенном состоянии
	BOOST_AUTO_TEST_CASE(cant_select_channel_when_turned_off)
	{
		BOOST_CHECK(!tv.SelectChannel(87));
		BOOST_CHECK_EQUAL(tv.GetChannel(), 0);
	}
	BOOST_AUTO_TEST_CASE(cant_set_channel_name_when_turned_off)
	{
		BOOST_CHECK(!tv.SetChannelName(5, "five"));
	}
	// может быть включен
	BOOST_AUTO_TEST_CASE(can_be_turned_on)
	{
		tv.TurnOn();
		BOOST_CHECK(tv.IsTurnedOn());
	}
	// изначально отображает 0 канал
	BOOST_AUTO_TEST_CASE(displays_channel_0_by_default)
	{
		BOOST_CHECK_EQUAL(tv.GetChannel(), 0);
	}
	struct when_turned_on_ : TVSetFixture
	{
		when_turned_on_()
		{
			tv.TurnOn();
		}
	};
	// после включения
	BOOST_FIXTURE_TEST_SUITE(when_turned_on, when_turned_on_)
		// отображает канал 1
		BOOST_AUTO_TEST_CASE(displays_channel_one)
		{
			BOOST_CHECK_EQUAL(tv.GetChannel(), 1);
		}
		// можно выключить
		BOOST_AUTO_TEST_CASE(can_be_turned_off)
		{
			tv.TurnOff();
			BOOST_CHECK(!tv.IsTurnedOn());
		}
		// позволяет выбрать канал от 1 до 99
		BOOST_AUTO_TEST_CASE(can_select_channel_from_1_to_99)
		{
			BOOST_CHECK(tv.SelectChannel(1));
			BOOST_CHECK_EQUAL(tv.GetChannel(), 1);

			BOOST_CHECK(!tv.SelectChannel(0));
			BOOST_CHECK_EQUAL(tv.GetChannel(), 1);

			BOOST_CHECK(tv.SelectChannel(99));
			BOOST_CHECK_EQUAL(tv.GetChannel(), 99);

			BOOST_CHECK(!tv.SelectChannel(100));
			BOOST_CHECK_EQUAL(tv.GetChannel(), 99);
		}	
		BOOST_AUTO_TEST_CASE(cant_select_empty_channel_name_without_setting_name)
		{
			BOOST_CHECK(!tv.SelectChannel(""));
		}
		BOOST_AUTO_TEST_CASE(can_set_channel_name_when_turned_on)
		{
			BOOST_CHECK(tv.SetChannelName(5, "five"));
		}
		BOOST_AUTO_TEST_CASE(cant_set_channel_empty_name_when_turned_on)
		{
			BOOST_CHECK(!tv.SetChannelName(5, ""));
		}
		BOOST_AUTO_TEST_CASE(cant_set_channel_name_with_only_spaces_when_turned_on)
		{
			BOOST_CHECK(!tv.SetChannelName(5, "           "));
		}
		BOOST_AUTO_TEST_CASE(can_delete_whitespaces_in_channel_name_when_turned_on)
		{
			BOOST_CHECK(tv.SetChannelName(5, "   five         channel    "));
			BOOST_CHECK_EQUAL(tv.GetChannelName(5), "five channel");
		}
		BOOST_AUTO_TEST_CASE(cant_delete_name_of_channel_without_setting_name)
		{
			BOOST_CHECK(!tv.DeleteChannelName("five"));
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct after_subsequent_turning_on_ : when_turned_on_
	{
		after_subsequent_turning_on_()
		{
			tv.SelectChannel(33);
			tv.TurnOff();
			tv.TurnOn();
		}
	};

	// после повторного включения
	BOOST_FIXTURE_TEST_SUITE(after_subsequent_turning_on, after_subsequent_turning_on_)
		// восстанавливает последний выбранный канал
		BOOST_AUTO_TEST_CASE(restores_last_selected_channel)
		{
			BOOST_CHECK_EQUAL(tv.GetChannel(), 33);
		}
		BOOST_AUTO_TEST_CASE(restores_previous_selected_channel)
		{
			tv.SelectChannel(55);
			BOOST_CHECK(tv.SelectPreviousChannel());
			BOOST_CHECK_EQUAL(tv.GetChannel(), 33);
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct after_setting_name_ : when_turned_on_
	{
		after_setting_name_()
		{
			tv.SetChannelName(5, "five");
		}
	};

	BOOST_FIXTURE_TEST_SUITE(after_setting_name, after_setting_name_)
		BOOST_AUTO_TEST_CASE(can_get_channel_by_name)
		{
			BOOST_CHECK_EQUAL(tv.GetChannelByName("five"), 5);
		}
		BOOST_AUTO_TEST_CASE(can_get_channel_name)
		{
			BOOST_CHECK_EQUAL(tv.GetChannelName(5), "five");
		}
		BOOST_AUTO_TEST_CASE(can_delete_channel_name)
		{
			BOOST_CHECK(tv.DeleteChannelName("five"));
			BOOST_CHECK(tv.GetChannelName(5).empty());
			BOOST_CHECK(tv.GetChannelByName("five") == 0);
		}
		BOOST_AUTO_TEST_CASE(can_select_channel_by_name)
		{
			BOOST_CHECK(tv.SelectChannel("five"));
			BOOST_CHECK_EQUAL(tv.GetChannel(), 5);
		}
		BOOST_AUTO_TEST_CASE(cant_set_two_channels_by_one_name)
		{
			BOOST_CHECK(tv.SetChannelName(6, "five"));
			BOOST_CHECK(tv.GetChannelName(5).empty());
			BOOST_CHECK_EQUAL(tv.GetChannelByName("five"), 6);
		}
		BOOST_AUTO_TEST_CASE(can_rename_channel)
		{
			BOOST_CHECK(tv.SetChannelName(5, "five channel"));
			BOOST_CHECK_EQUAL(tv.GetChannelByName("five channel"), 5);
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()