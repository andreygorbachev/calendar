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

#include <preceding.h>

#include <gtest/gtest.h>

#include <chrono>
#include <exception>
#include <memory>

#include "setup.h"

using namespace std;
using namespace std::chrono;
using namespace gregorian;


namespace business_day_convention
{

	TEST(preceding, adjust1)
	{
		const auto bdc = preceding{};

		const auto& c = make_calendar_england();

		const auto d1 = 2023y / January / 1d;
		const auto r1 = 2022y / December / 30d;
		EXPECT_EQ(r1, bdc.adjust(d1, c));
		const auto d2 = 2022y / December / 30d;
		const auto r2 = 2022y / December / 30d;
		EXPECT_EQ(r2, bdc.adjust(d2, c));
	}

	TEST(preceding, adjust2)
	{
		const auto bdc = preceding{};

		const auto& c = make_calendar_england();

		const auto d1 = sys_days{ 2023y / January / 1d };
		const auto r1 = sys_days{ 2022y / December / 30d };
		EXPECT_EQ(r1, bdc.adjust(d1, c));
		const auto d2 = sys_days{ 2022y / December / 30d };
		const auto r2 = sys_days{ 2022y / December / 30d };
		EXPECT_EQ(r2, bdc.adjust(d2, c));
	}

	TEST(preceding, adjust3)
	{
		// what if we adjust past the end of the calendar?

		const auto bdc = preceding{};

		const auto& c = make_calendar_starts_ends_with_holidays();

		EXPECT_THROW(bdc.adjust(c.get_schedule().get_from_until().get_from(), c), out_of_range);
	}

	TEST(preceding, adjust4)
	{
		// what if we have a calendar without any business days?

		const auto bdc = preceding{};

		const auto& c = make_calendar_all_holidays();

		EXPECT_THROW(bdc.adjust(c.get_schedule().get_from_until().get_from(), c), out_of_range);
	}

}
