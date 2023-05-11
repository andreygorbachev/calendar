#include <calendar.h>
#include <business_days.h>

#include <gtest/gtest.h>

#include <cstddef>
#include <memory>
#include <chrono>

#include "setup.h"

using namespace std;
using namespace std::chrono;


namespace
{

	TEST(business_days, is_business_day)
	{
		const auto c = test_parse_ics_england();
		const auto bd = business_days{ &SaturdaySundayWeekend, &c };

		EXPECT_EQ(false, bd.is_business_day(2023y/May/1d));
		EXPECT_EQ(true, bd.is_business_day(2023y/May/2d));
	}

	TEST(business_days, count)
	{
		const auto c = test_parse_ics_england();
		const auto bd = business_days{ &SaturdaySundayWeekend, &c };

		EXPECT_EQ(20/*uz*/, bd.count(2023y/May/1d, 2023y/May/31d));
	}

}
