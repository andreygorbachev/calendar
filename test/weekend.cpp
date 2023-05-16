#include <weekend.h>

#include <gtest/gtest.h>

#include <chrono>

using namespace std::chrono;


namespace calendar
{

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
		const auto w = FridaySaturdayWeekend | SaturdaySundayWeekend;

		// Friday
		EXPECT_EQ(true, w.is_weekend(2023y / March / 24d));

		// Saturday
		EXPECT_EQ(true, w.is_weekend(2023y / March / 25d));

		// Sunday
		EXPECT_EQ(true, w.is_weekend(2023y / March / 26d));

		// Monday
		EXPECT_EQ(false, w.is_weekend(2023y / March / 27d));
	}


	TEST(weekend, operator_and)
	{
		const auto w = FridaySaturdayWeekend & SaturdaySundayWeekend;

		// Friday
		EXPECT_EQ(false, w.is_weekend(2023y / March / 24d));

		// Saturday
		EXPECT_EQ(true, w.is_weekend(2023y / March / 25d));

		// Sunday
		EXPECT_EQ(false, w.is_weekend(2023y / March / 26d));

		// Monday
		EXPECT_EQ(false, w.is_weekend(2023y / March / 27d));
	}


	TEST(weekend, operator_equal)
	{
		EXPECT_EQ(true, SaturdaySundayWeekend == SaturdaySundayWeekend);
	}


	TEST(weekend, operator_not_equal)
	{
		EXPECT_EQ(true, SaturdaySundayWeekend != SundayWeekend);
	}


	TEST(weekend, get_we)
	{
		const auto we = SaturdaySundayWeekend.get_we();

		EXPECT_EQ(SaturdaySundayWeekend, weekend{ we });
	}

}
