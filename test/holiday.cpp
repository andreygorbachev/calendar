#include <holiday.h>

#include <gtest/gtest.h>

#include <chrono>

#include "setup.h"

using namespace std::chrono;


namespace
{

	TEST(holiday, named_holiday)
	{
		EXPECT_EQ(2023y / January / 1d, NewYearsDay.holiday(2023y));
	}


	TEST(holiday, good_friday_holiday)
	{
		EXPECT_EQ(2023y / April / 7d, GoodFriday.holiday(2023y));
	}


	TEST(holiday, easter_monday_holiday)
	{
		EXPECT_EQ(2023y / April / 10d, EasterMonday.holiday(2023y));
	}


	TEST(holiday, weekday_indexed_holiday)
	{
		const auto h = weekday_indexed_holiday{ May / Monday[1] }; // Early May Bank Holiday

		EXPECT_EQ(2023y / May / 1d, h.holiday(2023y));
	}


	TEST(holiday, weekday_last_holiday)
	{
		const auto h = weekday_last_holiday{ May / Monday[last]}; // Spring Bank Holiday

		EXPECT_EQ(2023y / May / 29d, h.holiday(2023y));
	}


	TEST(holiday, make_calendar)
	{
		const auto c = test_rule_england();

		EXPECT_EQ(true, c.is_holiday(2023y / April / 7d));
		EXPECT_EQ(true, c.is_holiday(2023y / April / 10d));
	}

}
