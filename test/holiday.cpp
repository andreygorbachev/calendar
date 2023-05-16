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

#include <holidays.h>

#include <gtest/gtest.h>

#include <chrono>

#include "setup.h"

using namespace std::chrono;


namespace calendar
{

	TEST(holiday, named_holiday)
	{
		EXPECT_EQ(2023y / January / 1d, NewYearsDay.holiday(2023y));
	}


	TEST(holiday, good_friday_holiday)
	{
		EXPECT_EQ(2023y / April / 7d, GoodFriday.holiday(2023y));
	}


	TEST(holiday, easter_monday_holiday)
	{
		EXPECT_EQ(2023y / April / 10d, EasterMonday.holiday(2023y));
	}


	TEST(holiday, weekday_indexed_holiday)
	{
		const auto h = weekday_indexed_holiday{ May / Monday[1] }; // Early May Bank Holiday

		EXPECT_EQ(2023y / May / 1d, h.holiday(2023y));
	}


	TEST(holiday, weekday_last_holiday)
	{
		const auto h = weekday_last_holiday{ May / Monday[last]}; // Spring Bank Holiday

		EXPECT_EQ(2023y / May / 29d, h.holiday(2023y));
	}


	TEST(holiday, make_calendar)
	{
		const auto hs = make_holiday_schedule_england();

		EXPECT_EQ(true, hs.is_holiday(2023y / April / 7d));
		EXPECT_EQ(true, hs.is_holiday(2023y / April / 10d));
	}

}
