#include <holiday.h>

#include <gtest/gtest.h>

#include <chrono>

using namespace std::chrono;


namespace calendar
{

	TEST(holiday, make_easter)
	{
		EXPECT_EQ(1961y / April / 2d, make_easter(1961y));
		EXPECT_EQ(2023y / April / 9d, make_easter(2023y));
	}

}
