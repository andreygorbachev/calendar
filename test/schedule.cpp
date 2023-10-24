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
#include <business_day_conventions.h>

#include <gtest/gtest.h>

#include <memory>
#include <chrono>
#include <algorithm>

#include "setup.h"

using namespace std;
using namespace std::chrono;


namespace gregorian
{

	TEST(schedule, constructor_1)
	{
		auto from_until = days_period{ 2023y / May / 1d, 2023y / May / 1d };
		auto hols = schedule::storage{};

		EXPECT_NO_THROW(schedule(move(from_until), move(hols))); // ok to have a schedule for just 1 day
	}


	TEST(schedule, constructor_2)
	{
		const auto s1 = make_holiday_schedule_england();
		const auto s2 = schedule{
			{ 2023y / January / 1d,	2023y / December / 31d },
			s1.get_dates()
		};

		EXPECT_EQ(make_holiday_schedule_england(), s1);
		EXPECT_NE(make_holiday_schedule_england(), s2);
	}


	TEST(schedule, operator_bitwise_or)
	{
		const auto& s1 = make_holiday_schedule_england();
		const auto& s2 = make_holiday_schedule_united_states();

		const auto s = s1 | s2;

		EXPECT_EQ(max(s1.get_from_until().get_from(), s2.get_from_until().get_from()), s.get_from_until().get_from());
		EXPECT_EQ(min(s1.get_from_until().get_until(), s2.get_from_until().get_until()), s.get_from_until().get_until());
	}

	TEST(schedule, operator_bitwise_and)
	{
		const auto& s1 = make_holiday_schedule_england();
		const auto& s2 = make_holiday_schedule_united_states();

		const auto s = s1 & s2;

		EXPECT_EQ(max(s1.get_from_until().get_from(), s2.get_from_until().get_from()), s.get_from_until().get_from());
		EXPECT_EQ(min(s1.get_from_until().get_until(), s2.get_from_until().get_until()), s.get_from_until().get_until());
	}

	TEST(schedule, operator_bitwise_not)
	{
		auto s = make_mpc_holiday_schedule_2023_2024(); // ~ is inside that function
		const auto cal = calendar{ NoWeekend, std::move(s) };

		EXPECT_EQ(2023y / June / 22d, Following.adjust(2023y / May / 12d, cal));
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
		const auto& s2 = schedule{ days_period{ year{ 2024 } / January / day{ 1u }, year{ 2024 } / December / day{ 31u } }, {} };

		const auto s = s1 + s2;

		EXPECT_EQ(s1.get_from_until().get_from(), s.get_from_until().get_from());
		EXPECT_EQ(year{ 2024 } / December / day{ 31u }, s.get_from_until().get_until());

		EXPECT_THROW(s2 + s1, out_of_range);
	}

	TEST(schedule, operator_addition_assignment_schedule)
	{
		const auto& s1 = make_holiday_schedule_england();
		const auto& s2 = schedule{ days_period{ year{ 2024 } / January / day{ 1u }, year{ 2024 } / December / day{ 31u } }, {} };

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
		s -= 2023y / April / 1d;

		EXPECT_EQ(make_holiday_schedule_england(), s);
	}

	TEST(schedule, get_dates)
	{
		const auto s1 = make_holiday_schedule_england_may_2023();
		const auto s2 = schedule{ s1.get_from_until(), s1.get_dates() };

		EXPECT_EQ(s2.get_from_until(), s1.get_from_until());
	}

	TEST(schedule, contains)
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

}
