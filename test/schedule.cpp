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

#include <schedule.h>

#include <gtest/gtest.h>

#include <memory>
#include <chrono>
#include <algorithm>

#include "setup.h"

using namespace std;
using namespace std::chrono;


namespace calendar
{

	TEST(schedule, constructor1)
	{
		const auto hols = schedule::storage{};

		EXPECT_NO_THROW(schedule(2023y / May / 1d, 2023y / May / 1d, hols)); // ok to have a schedule for just 1 day
		EXPECT_THROW(schedule(2023y / May / 31d, 2023y / May / 1d, hols), out_of_range);
	}


	TEST(schedule, constructor2)
	{
		const auto s1 = schedule{ parse_ics_england() };
		const auto s2 = schedule{
			2023y / January / 1d,
			2023y / December / 31d,
			s1.get_dates()
		};

		EXPECT_EQ(parse_ics_england(), s1);
		EXPECT_NE(parse_ics_england(), s2);
	}


	TEST(schedule, operator_or)
	{
		const auto& s1 = parse_ics_england();
		const auto& s2 = parse_ics_united_states();

		const auto s = s1 | s2;

		EXPECT_EQ(max(s1.get_from(), s2.get_from()), s.get_from());
		EXPECT_EQ(min(s1.get_until(), s2.get_until()), s.get_until());
	}

	TEST(schedule, operator_and)
	{
		const auto& s1 = parse_ics_england();
		const auto& s2 = parse_ics_united_states();

		const auto s = s1 & s2;

		EXPECT_EQ(max(s1.get_from(), s2.get_from()), s.get_from());
		EXPECT_EQ(min(s1.get_until(), s2.get_until()), s.get_until());
	}

	TEST(schedule, operator_equal)
	{
		const auto s1 = parse_ics_england();
		const auto s2 = parse_ics_england();

		EXPECT_TRUE(s1 == s2);
	}

	TEST(schedule, operator_not_equal)
	{
		const auto& s1 = parse_ics_england();
		const auto& s2 = parse_ics_united_states();

		EXPECT_TRUE(s1 != s2);
	}

	TEST(schedule, operator_plus)
	{
		const auto& s1 = parse_ics_england();
		const auto& s2 = parse_ics_united_states();

		const auto s3 = s1 + s2;
		const auto s4 = s2 + s1;

		EXPECT_EQ(s3.get_from(), s4.get_from());
		EXPECT_EQ(s3.get_until(), s4.get_until());
	}

	TEST(schedule, operator_plus_equal_1)
	{
		const auto& s1 = parse_ics_england();
		const auto& s2 = parse_ics_united_states();

		auto s3 = s1;
		s3 += s2;

		EXPECT_EQ(s1 + s2, s3);
	}

	TEST(schedule, operator_plus_equal_2)
	{
		auto s1 = parse_ics_england();
		s1 += 2023y / April / 1d;
		s1 -= 2023y / April / 1d;

		EXPECT_EQ(parse_ics_england(), s1);
	}

	TEST(schedule, get_dates)
	{
		const auto s1 = make_holiday_schedule_england_may_2023();
		const auto s2 = schedule{ s1.get_from(), s1.get_until(), s1.get_dates() };

		EXPECT_EQ(s2.get_from(), s1.get_from());
		EXPECT_EQ(s2.get_until(), s1.get_until());
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
