#include <calendar.h>
#include <business_days.h>

#include <gtest/gtest.h>

#include <cstddef>
#include <memory>
#include <chrono>

using namespace std;
using namespace std::chrono;


namespace
{

	auto make_May_London_calendar() -> calendar
	{
		auto hols = calendar::holidays_storage{
			2023y/May/1d,
			2023y/May/8d,
			2023y/May/29d,
		};

		return calendar{ 2023y/May/1d, 2023y/May/31d, move(hols) };
	}



	TEST(business_days, is_business_day_false)
	{
		const auto c = make_May_London_calendar();
		const auto bd = business_days{ &c };

		EXPECT_EQ(false, bd.is_business_day(2023y/May/1d));
	}

	TEST(business_days, is_business_day_true)
	{
		const auto c = make_May_London_calendar();
		const auto bd = business_days{ &c };

		EXPECT_EQ(true, bd.is_business_day(2023y/May/2d));
	}

	TEST(business_days, count)
	{
		const auto c = make_May_London_calendar();
		const auto bd = business_days{ &c };

		EXPECT_EQ(0/*uz*/, bd.count(2023y/May/1d, 2023y/May/31d));
	}

}
