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

#include <annual_holiday_interface.h>
#include <annual_holidays.h>
#include <schedule.h>
#include <period.h>
#include <schedule.h>

#include <gtest/gtest.h>

#include <chrono>

using namespace std::chrono;

using namespace gregorian::util;


namespace gregorian
{

	TEST(named_holiday, make_holiday_1)
	{
		static_assert(2023y / FirstDayOfJanuary == NewYearsDay.make_holiday(2023y));
	}

	TEST(named_holiday, make_holiday_2)
	{
		static_assert(2023y / LastDayOfDecember == NewYearsEve.make_holiday(2023y));
	}


	TEST(_easter_holiday, make_holiday)
	{
		static_assert(1961y / April / 2d == _Easter.make_holiday(1961y));
		static_assert(2023y / April / 9d == _Easter.make_holiday(2023y));

		// Earliest Easter
		static_assert(2285y / March / 22d == _Easter.make_holiday(2285y));

		// Latest Easter
		static_assert(2038y / April / 25d == _Easter.make_holiday(2038y));
	}


	TEST(offset_holiday, make_holiday_1)
	{
		static_assert(2023y / April / 7d == GoodFriday.make_holiday(2023y));
	}

	TEST(offset_holiday, make_holiday_2)
	{
		static_assert(2023y / April / 10d == EasterMonday.make_holiday(2023y));
	}

	TEST(offset_holiday, make_holiday_3)
	{
		static_assert(2022y / May / 26d == AscensionDay.make_holiday(2022y));
		static_assert(2023y / May / 18d == AscensionDay.make_holiday(2023y));
		static_assert(2024y / May / 9d == AscensionDay.make_holiday(2024y));
		static_assert(2025y / May / 29d == AscensionDay.make_holiday(2025y));
	}

	TEST(offset_holiday, make_holiday_4)
	{
		static_assert(2022y / June / 6d == WhitMonday.make_holiday(2022y));
		static_assert(2023y / May / 29d == WhitMonday.make_holiday(2023y));
		static_assert(2024y / May / 20d == WhitMonday.make_holiday(2024y));
		static_assert(2025y / June / 9d == WhitMonday.make_holiday(2025y));
	}


	TEST(weekday_indexed_holiday, make_holiday)
	{
		constexpr auto h = weekday_indexed_holiday{ May / Monday[1] }; // Early May Bank Holiday

		static_assert(2023y / May / 1d == h.make_holiday(2023y));
	}


	TEST(weekday_last_holiday, make_holiday)
	{
		constexpr auto h = weekday_last_holiday{ May / Monday[last] }; // Spring Bank Holiday

		static_assert(2023y / May / 29d == h.make_holiday(2023y));
	}


	TEST(annual_holiday, make_holiday_schedule1)
	{
		const auto p = years_period{ 2023y, 2023y };

		const auto no_rules = annual_holiday_storage{};

		const auto s = make_holiday_schedule(p, no_rules);

		const auto no_holidays = schedule{
			days_period{ 2023y / January / 1d, 2023y / December / 31d },
			{}
		};

		EXPECT_EQ(no_holidays, s);
	}

}
