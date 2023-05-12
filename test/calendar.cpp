#include <weekend.h>
#include <holiday_schedule.h>
#include <calendar.h>

#include <gtest/gtest.h>

#include <cstddef>
#include <memory>
#include <chrono>

#include "setup.h"

using namespace std;
using namespace std::chrono;


namespace calendar
{

	TEST(calendar, is_business_day)
	{
		const auto c = calendar{ SaturdaySundayWeekend, test_parse_ics_england() };

		EXPECT_EQ(false, c.is_business_day(2023y/May/1d));
		EXPECT_EQ(true, c.is_business_day(2023y/May/2d));
	}

	TEST(calendar, count_business_days)
	{
		const auto c = calendar{ SaturdaySundayWeekend, test_parse_ics_england() };

		EXPECT_EQ(20/*uz*/, c.count_business_days(2023y/May/1d, 2023y/May/31d));
	}

}
