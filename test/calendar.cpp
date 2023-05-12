#include <weekend.h>
#include <holiday_schedule.h>
#include <calendar.h>
#include <business_day_conventions.h>

#include <gtest/gtest.h>

#include <cstddef>
#include <memory>
#include <chrono>

#include "setup.h"

using namespace std;
using namespace std::chrono;


namespace calendar
{

	TEST(calendar, substitute1)
	{
		const auto expected = calendar{ SaturdaySundayWeekend, parse_ics_england() };

		auto c = calendar{ SaturdaySundayWeekend, make_holiday_schedule_england() };
		c.substitute(&Following);

		EXPECT_EQ(expected, c);
	}

	TEST(calendar, substitute2)
	{
		const auto expected = calendar{ SaturdaySundayWeekend, parse_ics_united_states() };

		auto c = calendar{ SaturdaySundayWeekend, make_holiday_schedule_united_states() };
		c.substitute(&FridayIfSaturdayAndMondayIfSunday);

		EXPECT_EQ(expected, c);
	}

	TEST(calendar, is_business_day)
	{
		const auto c = calendar{ SaturdaySundayWeekend, parse_ics_england() };

		EXPECT_EQ(false, c.is_business_day(2023y/May/1d));
		EXPECT_EQ(true, c.is_business_day(2023y/May/2d));
	}

	TEST(calendar, count_business_days)
	{
		const auto c = calendar{ SaturdaySundayWeekend, parse_ics_england() };

		EXPECT_EQ(20/*uz*/, c.count_business_days(2023y/May/1d, 2023y/May/31d));
	}

}
