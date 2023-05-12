#include <business_day_convention.h>
#include <weekend.h>
#include <holiday_schedule.h>
#include <business_days.h>

#include <gtest/gtest.h>

#include <chrono>

#include "setup.h"

using namespace std::chrono;


namespace
{

	TEST(business_day_convention, no_adjustment)
	{
		const auto c = test_parse_ics_england();
		const auto bd = business_days{ &SaturdaySundayWeekend, &c };

		EXPECT_EQ(2023y / January / 1d, NoAdjustment.adjust(2023y / January / 1d, bd));
	}

	TEST(business_day_convention, following)
	{
		const auto c = test_parse_ics_england();
		const auto bd = business_days{ &SaturdaySundayWeekend, &c };

		EXPECT_EQ(2023y / January / 3d, Following.adjust(2023y / January / 1d, bd));
		EXPECT_EQ(2023y / January / 3d, Following.adjust(2023y / January / 3d, bd));
	}

	TEST(business_day_convention, previous)
	{
		const auto c = test_parse_ics_england();
		const auto bd = business_days{ &SaturdaySundayWeekend, &c };

		EXPECT_EQ(2022y / December / 30d, Previous.adjust(2023y / January / 1d, bd));
		EXPECT_EQ(2022y / December / 30d, Previous.adjust(2022y / December / 30d, bd));
	}

	TEST(business_day_convention, monday_if_sunday)
	{
		const auto c = test_parse_ics_england();
		const auto bd = business_days{ &SaturdaySundayWeekend, &c };

		// Saturday
		EXPECT_EQ(2023y / March / 25d, MondayIfSunday.adjust(2023y / March / 25d, bd));

		// Sunday
		EXPECT_EQ(2023y / March / 27d, MondayIfSunday.adjust(2023y / March / 26d, bd));

		// Monday
		EXPECT_EQ(2023y / March / 27d, MondayIfSunday.adjust(2023y / March / 27d, bd));
	}

}
