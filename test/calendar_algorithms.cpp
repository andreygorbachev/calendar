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

#include <calendar_algorithms.h>

#include <gtest/gtest.h>

#include <chrono>

#include "setup.h"

using namespace std::chrono;


namespace gregorian
{

	TEST(calendar_algorithms, shift_business_days1) // should we test shifting outside the calendar range?
	{
		const auto& c = make_calendar_england();

		// from a business day
		EXPECT_EQ(shift_business_days(2023y / May / 2d, days{ 1 }, c), 2023y / May / 3d);

		// from a non-business day (May 1 is a holiday)
		EXPECT_EQ(shift_business_days(2023y / May / 1d, days{ 1 }, c), 2023y / May / 2d);

		// negative shift from a business day
		EXPECT_EQ(shift_business_days(2023y / May / 2d, days{ -1 }, c), 2023y / April / 28d);

		// zero shift returns same date
		EXPECT_EQ(shift_business_days(2023y / May / 2d, days{ 0 }, c), 2023y / May / 2d);
	}

	TEST(calendar_algorithms, shift_business_days2) // should this be just sys_days?
	{
		const auto& c = make_calendar_england();

		// larger positive shift across weekends and holidays
		EXPECT_EQ(shift_business_days(2023y / April / 28d, days{ 5 }, c), 2023y / May / 9d);

		// sys_days overload: negative shift
		EXPECT_EQ(shift_business_days(sys_days{ 2023y / May / 1d }, days{ -1 }, c), sys_days{ 2023y / April / 28d });
	}

}
