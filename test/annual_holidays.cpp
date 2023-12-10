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

#include <annual_holidays.h>

#include <gtest/gtest.h>

#include <chrono>

#include "setup.h"

using namespace std::chrono;


namespace gregorian
{

	TEST(named_holiday, make_holiday_1)
	{
		EXPECT_EQ(2023y / FirstDayOfJanuary, NewYearsDay.make_holiday(2023y));
	}

	TEST(named_holiday, make_holiday_2)
	{
		EXPECT_EQ(2023y / LastDayOfDecember, NewYearsEve.make_holiday(2023y));
	}


	TEST(_easter_holiday, make_holiday)
	{
		EXPECT_EQ(1961y / April / 2d, _Easter.make_holiday(1961y));
		EXPECT_EQ(2023y / April / 9d, _Easter.make_holiday(2023y));
	}


	TEST(offset_holiday, make_holiday_1)
	{
		EXPECT_EQ(2023y / April / 7d, GoodFriday.make_holiday(2023y));
	}

	TEST(offset_holiday, make_holiday_2)
	{
		EXPECT_EQ(2023y / April / 10d, EasterMonday.make_holiday(2023y));
	}

	TEST(offset_holiday, make_holiday_3)
	{
		EXPECT_EQ(2022y / May / 26d, AscensionDay.make_holiday(2022y));
		EXPECT_EQ(2023y / May / 18d, AscensionDay.make_holiday(2023y));
		EXPECT_EQ(2024y / May / 9d, AscensionDay.make_holiday(2024y));
		EXPECT_EQ(2025y / May / 29d, AscensionDay.make_holiday(2025y));
	}

	TEST(offset_holiday, make_holiday_4)
	{
		EXPECT_EQ(2022y / June / 6d, WhitMonday.make_holiday(2022y));
		EXPECT_EQ(2023y / May / 29d, WhitMonday.make_holiday(2023y));
		EXPECT_EQ(2024y / May / 20d, WhitMonday.make_holiday(2024y));
		EXPECT_EQ(2025y / June / 9d, WhitMonday.make_holiday(2025y));
	}


	TEST(weekday_indexed_holiday, make_holiday)
	{
		const auto h = weekday_indexed_holiday{ May / Monday[1] }; // Early May Bank Holiday

		EXPECT_EQ(2023y / May / 1d, h.make_holiday(2023y));
	}


	TEST(weekday_last_holiday, make_holiday)
	{
		const auto h = weekday_last_holiday{ May / Monday[last] }; // Spring Bank Holiday

		EXPECT_EQ(2023y / May / 29d, h.make_holiday(2023y));
	}


//	TEST(annual_holiday, make_holiday_schedule)
//	{
//	}

}
