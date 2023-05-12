#include <holiday_schedule.h>

#include <gtest/gtest.h>

#include <memory>
#include <chrono>
#include <algorithm>

#include "setup.h"

using namespace std;
using namespace std::chrono;


namespace calendar
{

	auto make_April_London_holiday_schedule() -> holiday_schedule
	{
		auto hols = holiday_schedule::storage{
			2023y / April / 7d,
			2023y / April / 10d,
		};

		return holiday_schedule{ 2023y / April / 1d, 2023y / April / 30d, move(hols) };
	}

	auto make_May_London_holiday_schedule() -> holiday_schedule
	{
		auto hols = holiday_schedule::storage{
			2023y / May / 1d,
			2023y / May / 8d,
			2023y / May / 29d,
		};

		return holiday_schedule{ 2023y / May / 1d, 2023y / May / 31d, move(hols) };
	}

	auto make_May_NewYork_holiday_schedule() -> holiday_schedule
	{
		auto hols = holiday_schedule::storage{
			2023y / May / 29d,
		};

		return holiday_schedule{ 2023y / May / 1d, 2023y / May / 31d, move(hols) };
	}

	auto make_empty_holiday_schedule() -> holiday_schedule
	{
		auto hols = holiday_schedule::storage{
		};

		return holiday_schedule{ 2023y / May / 1d, 2023y / May / 31d, move(hols) };
	}


	TEST(holiday_schedule, operator_equal)
	{
		const auto c1 = make_May_London_holiday_schedule();
		const auto c2 = make_empty_holiday_schedule();
		const auto c3 = make_May_NewYork_holiday_schedule() | c1;
		const auto c4 = make_May_NewYork_holiday_schedule() & c1;

		EXPECT_EQ(false, c1 == c2);
		EXPECT_EQ(false, c3 == c4);
		EXPECT_EQ(false, c1 == c4);
	}

	TEST(holiday_schedule, operator_or)
	{
		const auto& c1 = parse_ics_england();
		const auto& c2 = parse_ics_united_states();

		const auto c = c1 | c2;

		EXPECT_EQ(max(c1.get_front(), c2.get_front()), c.get_front());
		EXPECT_EQ(min(c1.get_back(), c2.get_back()), c.get_back());
	}

	TEST(holiday_schedule, operator_and)
	{
		const auto& c1 = parse_ics_england();
		const auto& c2 = parse_ics_united_states();

		const auto c = c1 & c2;

		EXPECT_EQ(max(c1.get_front(), c2.get_front()), c.get_front());
		EXPECT_EQ(min(c1.get_back(), c2.get_back()), c.get_back());
	}

	TEST(holiday_schedule, is_holiday)
	{
		const auto c1 = make_May_London_holiday_schedule();
		const auto c3 = make_May_NewYork_holiday_schedule() | c1;
		const auto c4 = make_May_NewYork_holiday_schedule() & c1;
		const auto c5 = make_April_London_holiday_schedule() + c1;

		EXPECT_EQ(true, c1.is_holiday(2023y / May / 1d));
		EXPECT_EQ(true, c3.is_holiday(2023y / May / 1d));
		EXPECT_EQ(false, c4.is_holiday(2023y / May / 1d));
		EXPECT_EQ(true, c3.is_holiday(2023y / May / 1d));
	}

}
