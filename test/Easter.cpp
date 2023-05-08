#include <holiday.h>

#include <gtest/gtest.h>

#include <chrono>

using namespace std::chrono;


namespace
{

	TEST(holiday, make_Easter)
	{
		EXPECT_EQ(1961y / April / 2d, make_Easter(1961y));
		EXPECT_EQ(2023y / April / 9d, make_Easter(2023y));
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

}
