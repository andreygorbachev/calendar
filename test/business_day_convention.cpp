#include <business_day_convention.h>
#include <weekend.h>
#include <holiday_schedule.h>
#include <calendar.h>

#include <gtest/gtest.h>

#include <chrono>

#include "setup.h"

using namespace std::chrono;


namespace
{

	TEST(business_day_convention, no_adjustment)
	{
		const auto c = calendar{ SaturdaySundayWeekend, test_parse_ics_england() };

		EXPECT_EQ(2023y / January / 1d, NoAdjustment.adjust(2023y / January / 1d, c));
	}

	TEST(business_day_convention, following)
	{
		const auto c = calendar{ SaturdaySundayWeekend, test_parse_ics_england() };

		EXPECT_EQ(2023y / January / 3d, Following.adjust(2023y / January / 1d, c));
		EXPECT_EQ(2023y / January / 3d, Following.adjust(2023y / January / 3d, c));
	}

	TEST(business_day_convention, previous)
	{
		const auto c = calendar{ SaturdaySundayWeekend, test_parse_ics_england() };

		EXPECT_EQ(2022y / December / 30d, Previous.adjust(2023y / January / 1d, c));
		EXPECT_EQ(2022y / December / 30d, Previous.adjust(2022y / December / 30d, c));
	}

	TEST(business_day_convention, monday_if_sunday)
	{
		const auto c = calendar{ SaturdaySundayWeekend, test_parse_ics_england() };

		// Saturday
		EXPECT_EQ(2023y / March / 25d, MondayIfSunday.adjust(2023y / March / 25d, c));

		// Sunday
		EXPECT_EQ(2023y / March / 27d, MondayIfSunday.adjust(2023y / March / 26d, c));

		// Monday
		EXPECT_EQ(2023y / March / 27d, MondayIfSunday.adjust(2023y / March / 27d, c));
	}

}
