// The MIT License (MIT)
//
// Copyright (c) 2023 Andrey Gorbachev
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <period.h>

#include <schedule.h>
#include <business_day_adjusters.h>

#include <gtest/gtest.h>

#include <utility>
#include <chrono>
#include <algorithm>

#include "setup.h"

using namespace std;
using namespace std::chrono;
using namespace gregorian::util;


namespace gregorian
{

	TEST(schedule, constructor_1)
	{
		auto p = days_period{ 2023y / April / 1d, 2023y / April / 1d };
		auto ds = schedule::dates{};

		EXPECT_NO_THROW(schedule(move(p), move(ds))); // ok to have a schedule for just 1 day
	}

	TEST(schedule, constructor_2)
	{
		const auto s1 = make_holiday_schedule_england();
		const auto s2 = schedule{
			days_period{ 2023y / FirstDayOfJanuary, 2023y / LastDayOfDecember },
			s1.get_dates()
		};

		EXPECT_EQ(make_holiday_schedule_england(), s1);
		EXPECT_NE(make_holiday_schedule_england(), s2);
	}

	TEST(schedule, constructor_3)
	{
		const auto s1 = make_holiday_schedule_england();
		const auto s2 = schedule{
			s1.get_dates()
		};

		EXPECT_EQ(make_holiday_schedule_england(), s2);
	}


	TEST(schedule, operator_bitwise_or)
	{
		const auto& s1 = make_holiday_schedule_england();
		const auto& s2 = make_holiday_schedule_united_states();

		const auto s = s1 | s2;

		EXPECT_EQ(min(s1.get_period().get_from(), s2.get_period().get_from()), s.get_period().get_from());
		EXPECT_EQ(max(s1.get_period().get_until(), s2.get_period().get_until()), s.get_period().get_until());
	}

	TEST(schedule, operator_bitwise_and)
	{
		const auto& s1 = make_holiday_schedule_england();
		const auto& s2 = make_holiday_schedule_united_states();

		const auto s = s1 & s2;

		EXPECT_EQ(max(s1.get_period().get_from(), s2.get_period().get_from()), s.get_period().get_from());
		EXPECT_EQ(min(s1.get_period().get_until(), s2.get_period().get_until()), s.get_period().get_until());
	}

	TEST(schedule, operator_bitwise_not)
	{
		const auto& dates = make_mpc_dates_may_2023();
		
		const auto hols = ~dates;

		const auto expected = schedule{ util::days_period{ 2023y / May / 1d, 2023y / May / 31d }, {
			2023y / May / 1d,
			2023y / May / 2d,
			2023y / May / 3d,
			2023y / May / 4d,
			2023y / May / 5d,
			2023y / May / 6d,
			2023y / May / 7d,
			2023y / May / 8d,
			2023y / May / 9d,
			2023y / May / 10d,
			2023y / May / 12d,
			// no 11th
			2023y / May / 13d,
			2023y / May / 14d,
			2023y / May / 15d,
			2023y / May / 16d,
			2023y / May / 17d,
			2023y / May / 18d,
			2023y / May / 19d,
			2023y / May / 20d,
			2023y / May / 21d,
			2023y / May / 22d,
			2023y / May / 23d,
			2023y / May / 24d,
			2023y / May / 25d,
			2023y / May / 26d,
			2023y / May / 27d,
			2023y / May / 28d,
			2023y / May / 29d,
			2023y / May / 30d,
			2023y / May / 31d
		} };

		EXPECT_EQ(expected, hols);
	}

	TEST(schedule, operator_equal_to)
	{
		const auto& s1 = make_holiday_schedule_england();
		const auto& s2 = make_holiday_schedule_england();

		EXPECT_TRUE(s1 == s2);
	}

	TEST(schedule, operator_not_equal_to)
	{
		const auto& s1 = make_holiday_schedule_england();
		const auto& s2 = make_holiday_schedule_united_states();

		EXPECT_TRUE(s1 != s2);
	}

	TEST(schedule, operator_addition)
	{
		const auto& s1 = make_holiday_schedule_england();
		const auto& s2 = schedule{ days_period{ year{ 2024 } / FirstDayOfJanuary, year{ 2024 } / LastDayOfDecember }, {} };

		const auto s = s1 + s2;

		EXPECT_EQ(s1.get_period().get_from(), s.get_period().get_from());
		EXPECT_EQ(year{ 2024 } / December / day{ 31u }, s.get_period().get_until());

		EXPECT_THROW(s2 + s1, out_of_range);
	}

	TEST(schedule, operator_addition_assignment_schedule)
	{
		const auto& s1 = make_holiday_schedule_england();
		const auto& s2 = schedule{ days_period{ year{ 2024 } / FirstDayOfJanuary, year{ 2024 } / LastDayOfDecember }, {} };

		auto s = s1;
		s += s2;

		EXPECT_EQ(s1 + s2, s);

		EXPECT_THROW(s = s2; s += s1, out_of_range);
	}

	TEST(schedule, operator_addition_assignment_date)
	{
		auto s = make_holiday_schedule_england();

		EXPECT_FALSE(s.contains(2023y / April / 1d));
		s += 2023y / April / 1d;
		EXPECT_TRUE(s.contains(2023y / April / 1d));

		EXPECT_FALSE(s.contains(2024y / April / 1d));
		s += 2024y / April / 1d;
		EXPECT_FALSE(s.contains(2024y / April / 1d));
	}

	TEST(schedule, operator_subtraction_assignment_date)
	{
		auto s = make_holiday_schedule_england();

		s += 2023y / April / 1d;
		EXPECT_NE(make_holiday_schedule_england(), s);

		s -= 2023y / April / 1d;
		EXPECT_EQ(make_holiday_schedule_england(), s);
	}


	TEST(schedule, get_period)
	{
		const auto s1 = make_holiday_schedule_england_may_2023();
		const auto s2 = schedule{ s1.get_period(), s1.get_dates() };

		EXPECT_EQ(s1, s2);
	}
	TEST(schedule, get_dates)
	{
		const auto s1 = make_holiday_schedule_england_may_2023();
		const auto s2 = schedule{ s1.get_period(), s1.get_dates() };

		EXPECT_EQ(s1, s2);
	}

	TEST(schedule, contains1)
	{
		const auto s1 = make_holiday_schedule_england_may_2023();
		const auto s3 = make_holiday_schedule_united_states_may_2023() | s1;
		const auto s4 = make_holiday_schedule_united_states_may_2023() & s1;
		const auto s5 = make_holiday_schedule_england_april_2023() + s1;

		EXPECT_TRUE(s1.contains(2023y / May / 1d));
		EXPECT_TRUE(s3.contains(2023y / May / 1d));
		EXPECT_FALSE(s4.contains(2023y / May / 1d));
		EXPECT_TRUE(s3.contains(2023y / May / 1d));
	}

	TEST(schedule, contains2)
	{
		const auto s1 = make_holiday_schedule_england_may_2023();
		const auto s3 = make_holiday_schedule_united_states_may_2023() | s1;
		const auto s4 = make_holiday_schedule_united_states_may_2023() & s1;
		const auto s5 = make_holiday_schedule_england_april_2023() + s1;

		EXPECT_TRUE(s1.contains(sys_days{ 2023y / May / 1d }));
		EXPECT_TRUE(s3.contains(sys_days{ 2023y / May / 1d }));
		EXPECT_FALSE(s4.contains(sys_days{ 2023y / May / 1d }));
		EXPECT_TRUE(s3.contains(sys_days{ 2023y / May / 1d }));
	}


	TEST(_make_period, multiple_years)
	{
		const auto ds = schedule::dates{ 2023y / April / 1d, 2024y / April / 1d };

		const auto p = _make_period(ds);

		EXPECT_EQ(2023y / FirstDayOfJanuary, p.get_from());
		EXPECT_EQ(2024y / LastDayOfDecember, p.get_until());
	}

	TEST(_make_period, single_years)
	{
		const auto ds = schedule::dates{ 2023y / April / 1d };

		const auto p = _make_period(ds);

		EXPECT_EQ(2023y / FirstDayOfJanuary, p.get_from());
		EXPECT_EQ(2023y / LastDayOfDecember, p.get_until());
	}

	TEST(_make_period, no_years)
	{
		const auto ds = schedule::dates{};

		EXPECT_NO_THROW(_make_period(ds)); // ok to create [from, until] from an empty set of holiday dates

		const auto p = _make_period(ds);
		EXPECT_EQ(p.get_from(), p.get_until());
	}

}
