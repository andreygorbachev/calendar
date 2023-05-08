#include <holiday.h>

#include <gtest/gtest.h>

#include <chrono>

using namespace std::chrono;


namespace
{

	TEST(holiday, NewYearsDay)
	{
		const auto& h = NewYearsDay;

		EXPECT_EQ(2023y / January / 1d, h.holiday(2023y));
	}

	TEST(holiday, GoodFriday)
	{
		const auto h = GoodFriday{};

		EXPECT_EQ(2023y / April / 7d, h.holiday(2023y));
	}


	TEST(holiday, EasterMonday)
	{
		const auto h = EasterMonday{};

		EXPECT_EQ(2023y / April / 10d, h.holiday(2023y));
	}


	TEST(holiday, EarlyMayBankHoliday)
	{
		const auto h = weekday_indexed_holiday{ May / Monday[1] };

		EXPECT_EQ(2023y / May / 1d, h.holiday(2023y));
	}


	TEST(holiday, SpringBankHoliday)
	{
		const auto h = weekday_last_holiday{ May / Monday[last]};

		EXPECT_EQ(2023y / May / 29d, h.holiday(2023y));
	}

}
