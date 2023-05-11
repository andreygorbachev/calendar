#include <weekend.h>

#include <gtest/gtest.h>

#include <chrono>

using namespace std::chrono;


namespace
{

	TEST(weekend, operator_equal)
	{
		EXPECT_EQ(false, FridaySaturdayWeekend == SaturdaySundayWeekend);
		EXPECT_EQ(false, SundayWeekend == SaturdaySundayWeekend);
	}

	TEST(weekend, is_weekend)
	{
		// Friday
		EXPECT_EQ(false, SaturdaySundayWeekend.is_weekend(2023y / March / 24d));
		EXPECT_EQ(true, FridaySaturdayWeekend.is_weekend(2023y / March / 24d));
		EXPECT_EQ(false, SundayWeekend.is_weekend(2023y / March / 24d));

		// Saturday
		EXPECT_EQ(true, SaturdaySundayWeekend.is_weekend(2023y / March / 25d));
		EXPECT_EQ(true, FridaySaturdayWeekend.is_weekend(2023y / March / 25d));
		EXPECT_EQ(false, SundayWeekend.is_weekend(2023y / March / 25d));

		// Sunday
		EXPECT_EQ(true, SaturdaySundayWeekend.is_weekend(2023y / March / 26d));
		EXPECT_EQ(false, FridaySaturdayWeekend.is_weekend(2023y / March / 26d));
		EXPECT_EQ(true, SundayWeekend.is_weekend(2023y / March / 26d));

		// Monday
		EXPECT_EQ(false, SaturdaySundayWeekend.is_weekend(2023y / March / 27d));
		EXPECT_EQ(false, FridaySaturdayWeekend.is_weekend(2023y / March / 27d));
		EXPECT_EQ(false, SundayWeekend.is_weekend(2023y / March / 27d));
	}


	TEST(weekend, operator_or)
	{
		const auto we = FridaySaturdayWeekend | SaturdaySundayWeekend;

		// Friday
		EXPECT_EQ(true, we.is_weekend(2023y / March / 24d));

		// Saturday
		EXPECT_EQ(true, we.is_weekend(2023y / March / 25d));

		// Sunday
		EXPECT_EQ(true, we.is_weekend(2023y / March / 26d));

		// Monday
		EXPECT_EQ(false, we.is_weekend(2023y / March / 27d));
	}


	TEST(weekend, operator_and)
	{
		const auto we = FridaySaturdayWeekend & SaturdaySundayWeekend;

		// Friday
		EXPECT_EQ(false, we.is_weekend(2023y / March / 24d));

		// Saturday
		EXPECT_EQ(true, we.is_weekend(2023y / March / 25d));

		// Sunday
		EXPECT_EQ(false, we.is_weekend(2023y / March / 26d));

		// Monday
		EXPECT_EQ(false, we.is_weekend(2023y / March / 27d));
	}

}
