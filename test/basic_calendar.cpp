#include <calendar.h>

#include <gtest/gtest.h>

#include <chrono>

using namespace std::chrono;


namespace
{

	auto make_FSS_weekend() -> basic_calendar::weekend_storage
	{
		auto we = basic_calendar{}.get_weekend(); // start with Saturday/Sunday
		we[std::chrono::Friday.c_encoding()] = true; // add Friday

		return we;
	}

	auto make_empty_weekend() -> basic_calendar::weekend_storage
	{
		return {};
	}


	TEST(basic_calendar, operator_not_equal)
	{
		const auto c1 = basic_calendar{}; // weekend on Saturday/Sunday
		const auto c2 = basic_calendar{ make_empty_weekend() }; // no weekend
		const auto c3 = basic_calendar{ make_FSS_weekend() }; // weekend on Friday/Saturday/Sunday

		EXPECT_EQ(true, c1 != c2);
		EXPECT_EQ(true, c1 != c3);
	}

	TEST(basic_calendar, is_business_day)
	{
		const auto c1 = basic_calendar{}; // weekend on Saturday/Sunday
		const auto c2 = basic_calendar{ make_empty_weekend() }; // no weekend

		// Friday
		EXPECT_EQ(true, c1.is_business_day(2023y / March / 24d));
		EXPECT_EQ(true, c2.is_business_day(2023y / March / 24d));

		// Saturday
		EXPECT_EQ(false, c1.is_business_day(2023y / March / 25d));
		EXPECT_EQ(true, c2.is_business_day(2023y / March / 25d));

		// Sunday
		EXPECT_EQ(false, c1.is_business_day(2023y / March / 26d));
		EXPECT_EQ(true, c2.is_business_day(2023y / March / 26d));

		// Monday
		EXPECT_EQ(true, c1.is_business_day(2023y / March / 27d));
		EXPECT_EQ(true, c2.is_business_day(2023y / March / 27d));
	}

}