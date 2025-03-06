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

#include <business_day_conventions.h>
#include <weekend.h>
#include <schedule.h>
#include <calendar.h>

#include <gtest/gtest.h>

#include <chrono>
#include <exception>
#include <memory>

#include "setup.h"

using namespace std;
using namespace std::chrono;


namespace gregorian
{

	TEST(no_adjustment, adjust1)
	{
		const auto& c = make_calendar_england();

		const auto d = 2023y / January / 1d;

		EXPECT_EQ(d, NoAdjustment.adjust(d, c));
	}

	TEST(no_adjustment, adjust2)
	{
		const auto& c = make_calendar_england();

		const auto d = sys_days{ 2023y / January / 1d };

		EXPECT_EQ(d, NoAdjustment.adjust(d, c));
	}

	TEST(following, adjust1)
	{
		const auto& c = make_calendar_england();

		const auto d1 = 2023y / January / 1d;
		const auto r1 = 2023y / January / 3d;
		EXPECT_EQ(r1, Following.adjust(d1, c));
		const auto d2 = 2023y / January / 3d;
		const auto r2 = 2023y / January / 3d;
		EXPECT_EQ(r2, Following.adjust(d2, c));
	}

	TEST(following, adjust2)
	{
		const auto& c = make_calendar_england();

		const auto d1 = sys_days{ 2023y / January / 1d };
		const auto r1 = sys_days{ 2023y / January / 3d };
		EXPECT_EQ(r1, Following.adjust(d1, c));
		const auto d2= sys_days{ 2023y / January / 3d };
		const auto r2 = sys_days{ 2023y / January / 3d };
		EXPECT_EQ(r2, Following.adjust(d2, c));
	}

	TEST(following, adjust3)
	{
		// what if we adjust past the end of the calendar?

		auto hols = schedule::dates{
			2024y / FirstDayOfJanuary,	
			2024y / LastDayOfDecember,
		};
		auto s = schedule{ days_period{ 2024y / FirstDayOfJanuary, 2024y / LastDayOfDecember }, move(hols) };
		const auto c = calendar{ NoWeekend, move(s) };

		EXPECT_THROW(Following.adjust(c.get_schedule().get_from_until().get_until(), c), out_of_range);
	}

	TEST(modified_following, adjust1)
	{
		const auto& c = make_calendar_england();

		const auto d1 = 2023y / January / 1d;
		const auto r1 = 2023y / January / 3d;
		EXPECT_EQ(r1, ModifiedFollowing.adjust(d1, c));
		const auto d2 = 2023y / January / 3d;
		const auto r2 = 2023y / January / 3d;
		EXPECT_EQ(r2, ModifiedFollowing.adjust(d2, c));

		const auto d3 = 2022y / December / 31d;
		const auto r3 = 2022y / December / 30d;
		EXPECT_EQ(r3, ModifiedFollowing.adjust(d3, c));
		const auto d4 = 2022y / December / 30d;
		const auto r4 = 2022y / December / 30d;
		EXPECT_EQ(r4, ModifiedFollowing.adjust(d4, c));
	}

	TEST(modified_following, adjust2)
	{
		const auto& c = make_calendar_england();

		const auto d1 = sys_days{ 2023y / January / 1d };
		const auto r1 = sys_days{ 2023y / January / 3d };
		EXPECT_EQ(r1, ModifiedFollowing.adjust(d1, c));
		const auto d2 = sys_days{ 2023y / January / 3d };
		const auto r2 = sys_days{ 2023y / January / 3d };
		EXPECT_EQ(r2, ModifiedFollowing.adjust(d2, c));

		const auto d3 = sys_days{ 2022y / December / 31d };
		const auto r3 = sys_days{ 2022y / December / 30d };
		EXPECT_EQ(r3, ModifiedFollowing.adjust(d3, c));
		const auto d4 = sys_days{ 2022y / December / 30d };
		const auto r4 = sys_days{ 2022y / December / 30d };
		EXPECT_EQ(r4, ModifiedFollowing.adjust(d4, c));
	}

	TEST(modified_following, adjust3)
	{
		// what if we adjust past the end of the calendar?

		auto hols = schedule::dates{
			2024y / FirstDayOfJanuary,
			2024y / LastDayOfDecember,
		};
		auto s = schedule{ days_period{ 2024y / FirstDayOfJanuary, 2024y / LastDayOfDecember }, move(hols) };
		const auto c = calendar{ NoWeekend, move(s) };

		EXPECT_THROW(ModifiedFollowing.adjust(c.get_schedule().get_from_until().get_until(), c), out_of_range); //?
	}

	TEST(preceding, adjust1)
	{
		const auto& c = make_calendar_england();

		const auto d1 = 2023y / January / 1d;
		const auto r1 = 2022y / December / 30d;
		EXPECT_EQ(r1, Preceding.adjust(d1, c));
		const auto d2 = 2022y / December / 30d;
		const auto r2 = 2022y / December / 30d;
		EXPECT_EQ(r2, Preceding.adjust(d2, c));
	}

	TEST(preceding, adjust2)
	{
		const auto& c = make_calendar_england();

		const auto d1 = sys_days{ 2023y / January / 1d };
		const auto r1 = sys_days{ 2022y / December / 30d };
		EXPECT_EQ(r1, Preceding.adjust(d1, c));
		const auto d2 = sys_days{ 2022y / December / 30d };
		const auto r2 = sys_days{ 2022y / December / 30d };
		EXPECT_EQ(r2, Preceding.adjust(d2, c));
	}

	TEST(preceding, adjust3)
	{
		// what if we adjust past the end of the calendar?

		auto hols = schedule::dates{
			2024y / FirstDayOfJanuary,
			2024y / LastDayOfDecember,
		};
		auto s = schedule{ days_period{ 2024y / FirstDayOfJanuary, 2024y / LastDayOfDecember }, move(hols) };
		const auto c = calendar{ NoWeekend, move(s) };

		EXPECT_THROW(Preceding.adjust(c.get_schedule().get_from_until().get_from(), c), out_of_range);
	}

	TEST(modified_preceding, adjust1)
	{
		const auto& c = make_calendar_england();

		const auto d1 = 2022y / December / 31d;
		const auto r1 = 2022y / December / 30d;
		EXPECT_EQ(r1, ModifiedPreceding.adjust(d1, c));
		const auto d2 = 2022y / December / 30d;
		const auto r2 = 2022y / December / 30d;
		EXPECT_EQ(r2, ModifiedPreceding.adjust(d2, c));

		const auto d3 = 2023y / January / 1d;
		const auto r3 = 2023y / January / 3d;
		EXPECT_EQ(r3, ModifiedPreceding.adjust(d3, c));
		const auto d4 = 2023y / January / 3d;
		const auto r4 = 2023y / January / 3d;
		EXPECT_EQ(r4, ModifiedPreceding.adjust(d4, c));
	}

	TEST(modified_preceding, adjust2)
	{
		const auto& c = make_calendar_england();

		const auto d1 = sys_days{ 2022y / December / 31d };
		const auto r1 = sys_days{ 2022y / December / 30d };
		EXPECT_EQ(r1, ModifiedPreceding.adjust(d1, c));
		const auto d2 = sys_days{ 2022y / December / 30d };
		const auto r2 = sys_days{ 2022y / December / 30d };
		EXPECT_EQ(r2, ModifiedPreceding.adjust(d2, c));

		const auto d3 = sys_days{ 2023y / January / 1d };
		const auto r3 = sys_days{ 2023y / January / 3d };
		EXPECT_EQ(r3, ModifiedPreceding.adjust(d3, c));
		const auto d4 = sys_days{ 2023y / January / 3d };
		const auto r4 = sys_days{ 2023y / January / 3d };
		EXPECT_EQ(r4, ModifiedPreceding.adjust(d4, c));
	}

	TEST(modified_preceding, adjust3)
	{
		// what if we adjust past the end of the calendar?

		auto hols = schedule::dates{
			2024y / FirstDayOfJanuary,
			2024y / LastDayOfDecember,
		};
		auto s = schedule{ days_period{ 2024y / FirstDayOfJanuary, 2024y / LastDayOfDecember }, move(hols) };
		const auto c = calendar{ NoWeekend, move(s) };

		EXPECT_THROW(ModifiedPreceding.adjust(c.get_schedule().get_from_until().get_from(), c), out_of_range); //?
	}

	TEST(nearest, adjust1)
	{
		const auto& c = make_calendar_england();

		// Friday
		const auto d1 = 2023y / March / 24d;
		const auto r1 = 2023y / March / 24d;
		EXPECT_EQ(r1, Nearest.adjust(d1, c));

		// Saturday
		const auto d2 = 2023y / March / 25d;
		const auto r2 = 2023y / March / 24d;
		EXPECT_EQ(r2, Nearest.adjust(d2, c));

		// Sunday
		const auto d3 = 2023y / March / 26d;
		const auto r3 = 2023y / March / 27d;
		EXPECT_EQ(r3, Nearest.adjust(d3, c));

		// Monday
		const auto d4 = 2023y / March / 27d;
		const auto r4 = 2023y / March / 27d;
		EXPECT_EQ(r4, Nearest.adjust(d4, c));
	}

	TEST(nearest, adjust2)
	{
		const auto& c = make_calendar_england();

		// Friday
		const auto d1 = sys_days{ 2023y / March / 24d };
		const auto r1 = sys_days{ 2023y / March / 24d };
		EXPECT_EQ(r1, Nearest.adjust(d1, c));

		// Saturday
		const auto d2 = sys_days{ 2023y / March / 25d };
		const auto r2 = sys_days{ 2023y / March / 24d };
		EXPECT_EQ(r2, Nearest.adjust(d2, c));

		// Sunday
		const auto d3 = sys_days{ 2023y / March / 26d };
		const auto r3 = sys_days{ 2023y / March / 27d };
		EXPECT_EQ(r3, Nearest.adjust(d3, c));

		// Monday
		const auto d4 = sys_days{ 2023y / March / 27d };
		const auto r4 = sys_days{ 2023y / March / 27d };
		EXPECT_EQ(r4, Nearest.adjust(d4, c));
	}

	// what about adjusting past the end of the calendar?

	TEST(make_first_business_day, make_first_business_day)
	{
		const auto& c = make_calendar_england();

		EXPECT_EQ(2023y / January / 3d, make_first_business_day(2023y / January, c));
	}

	TEST(make_last_business_day, make_last_business_day)
	{
		const auto& c = make_calendar_england();

		EXPECT_EQ(2022y / December / 30d, make_last_business_day(2022y / December, c));
	}

}
