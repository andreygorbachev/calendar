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


	TEST(holiday_schedule, operator_or)
	{
		const auto& h1 = parse_ics_england();
		const auto& h2 = parse_ics_united_states();

		const auto h = h1 | h2;

		EXPECT_EQ(max(h1.get_front(), h2.get_front()), h.get_front());
		EXPECT_EQ(min(h1.get_back(), h2.get_back()), h.get_back());
	}

	TEST(holiday_schedule, operator_and)
	{
		const auto& h1 = parse_ics_england();
		const auto& h2 = parse_ics_united_states();

		const auto h = h1 & h2;

		EXPECT_EQ(max(h1.get_front(), h2.get_front()), h.get_front());
		EXPECT_EQ(min(h1.get_back(), h2.get_back()), h.get_back());
	}

	TEST(holiday_schedule, is_holiday)
	{
		const auto h1 = make_May_London_holiday_schedule();
		const auto h3 = make_May_NewYork_holiday_schedule() | h1;
		const auto h4 = make_May_NewYork_holiday_schedule() & h1;
		const auto h5 = make_April_London_holiday_schedule() + h1;

		EXPECT_EQ(true, h1.is_holiday(2023y / May / 1d));
		EXPECT_EQ(true, h3.is_holiday(2023y / May / 1d));
		EXPECT_EQ(false, h4.is_holiday(2023y / May / 1d));
		EXPECT_EQ(true, h3.is_holiday(2023y / May / 1d));
	}

}
