#include <business_day_conventions.h>
#include <weekend.h>
#include <holiday_schedule.h>
#include <calendar.h>

#include <gtest/gtest.h>

#include <chrono>

#include "setup.h"

using namespace std::chrono;


namespace calendar
{

	TEST(business_day_convention, no_adjustment)
	{
		const auto c = calendar{ SaturdaySundayWeekend, parse_ics_england() };

		EXPECT_EQ(2023y / January / 1d, NoAdjustment.adjust(2023y / January / 1d, c));
	}

	TEST(business_day_convention, following)
	{
		const auto c = calendar{ SaturdaySundayWeekend, parse_ics_england() };

		EXPECT_EQ(2023y / January / 3d, Following.adjust(2023y / January / 1d, c));
		EXPECT_EQ(2023y / January / 3d, Following.adjust(2023y / January / 3d, c));
	}

	TEST(business_day_convention, modified_following)
	{
		const auto c = calendar{ SaturdaySundayWeekend, parse_ics_england() };

		EXPECT_EQ(2023y / January / 3d, ModifiedFollowing.adjust(2023y / January / 1d, c));
		EXPECT_EQ(2023y / January / 3d, ModifiedFollowing.adjust(2023y / January / 3d, c));
		// add a test for "modifed"
	}

	TEST(business_day_convention, preceding)
	{
		const auto c = calendar{ SaturdaySundayWeekend, parse_ics_england() };

		EXPECT_EQ(2022y / December / 30d, Preceding.adjust(2023y / January / 1d, c));
		EXPECT_EQ(2022y / December / 30d, Preceding.adjust(2022y / December / 30d, c));
	}

	TEST(business_day_convention, friday_if_saturday_and_monday_if_sunday)
	{
		const auto c = calendar{ SaturdaySundayWeekend, parse_ics_england() };

		// Friday
		EXPECT_EQ(2023y / March / 24d, FridayIfSaturdayAndMondayIfSunday.adjust(2023y / March / 24d, c));

		// Saturday
		EXPECT_EQ(2023y / March / 24d, FridayIfSaturdayAndMondayIfSunday.adjust(2023y / March / 25d, c));

		// Sunday
		EXPECT_EQ(2023y / March / 27d, FridayIfSaturdayAndMondayIfSunday.adjust(2023y / March / 26d, c));

		// Monday
		EXPECT_EQ(2023y / March / 27d, FridayIfSaturdayAndMondayIfSunday.adjust(2023y / March / 27d, c));
	}

}
