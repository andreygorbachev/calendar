#include <calendar.h>

#include <gtest/gtest.h>

#include <memory>
#include <chrono>
#include <algorithm>

#include "setup.h"

using namespace std;
using namespace std::chrono;


namespace
{

	auto make_April_London_calendar() -> calendar
	{
		auto hols = calendar::holidays_storage{
			2023y / April / 7d,
			2023y / April / 10d,
		};

		return calendar{ 2023y / April / 1d, 2023y / April / 30d, move(hols) };
	}

	auto make_May_London_calendar() -> calendar
	{
		auto hols = calendar::holidays_storage{
			2023y / May / 1d,
			2023y / May / 8d,
			2023y / May / 29d,
		};

		return calendar{ 2023y / May / 1d, 2023y / May / 31d, move(hols) };
	}

	auto make_May_NewYork_calendar() -> calendar
	{
		auto hols = calendar::holidays_storage{
			2023y / May / 29d,
		};

		return calendar{ 2023y / May / 1d, 2023y / May / 31d, move(hols) };
	}

	auto make_empty_calendar() -> calendar
	{
		auto hols = calendar::holidays_storage{
		};

		return calendar{ 2023y / May / 1d, 2023y / May / 31d, move(hols) };
	}


	TEST(calendar, operator_not_equal)
	{
		const auto c1 = make_May_London_calendar();
		const auto c2 = make_empty_calendar();
		const auto c3 = make_May_NewYork_calendar() | c1;
		const auto c4 = make_May_NewYork_calendar() & c1;

		EXPECT_EQ(true, c1 != c2);
		EXPECT_EQ(true, c3 != c4);
		EXPECT_EQ(true, c1 != c4);
	}

	TEST(calendar, operator_or)
	{
		const auto& c1 = test_parse_ics_england();
		const auto& c2 = test_parse_ics_united_states();

		const auto c = c1 | c2;

		EXPECT_EQ(max(c1.get_front(), c2.get_front()), c.get_front());
		EXPECT_EQ(min(c1.get_back(), c2.get_back()), c.get_back());
	}

	TEST(calendar, operator_and)
	{
		const auto& c1 = test_parse_ics_england();
		const auto& c2 = test_parse_ics_united_states();

		const auto c = c1 & c2;

		EXPECT_EQ(max(c1.get_front(), c2.get_front()), c.get_front());
		EXPECT_EQ(min(c1.get_back(), c2.get_back()), c.get_back());
	}

	TEST(calendar, is_holiday)
	{
		const auto c1 = make_May_London_calendar();
		const auto c3 = make_May_NewYork_calendar() | c1;
		const auto c4 = make_May_NewYork_calendar() & c1;
		const auto c5 = make_April_London_calendar() + c1;

		EXPECT_EQ(true, c1.is_holiday(2023y / May / 1d));
		EXPECT_EQ(true, c3.is_holiday(2023y / May / 1d));
		EXPECT_EQ(false, c4.is_holiday(2023y / May / 1d));
		EXPECT_EQ(true, c3.is_holiday(2023y / May / 1d));
	}

}
