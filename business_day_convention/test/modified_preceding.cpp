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

#include <modified_preceding.h>

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

	TEST(modified_preceding, adjust1)
	{
		const auto bdc = modified_preceding{};

		const auto& c = make_calendar_england();

		const auto d1 = 2022y / December / 31d;
		const auto r1 = 2022y / December / 30d;
		EXPECT_EQ(r1, bdc.adjust(d1, c));
		const auto d2 = 2022y / December / 30d;
		const auto r2 = 2022y / December / 30d;
		EXPECT_EQ(r2, bdc.adjust(d2, c));

		const auto d3 = 2023y / January / 1d;
		const auto r3 = 2023y / January / 3d;
		EXPECT_EQ(r3, bdc.adjust(d3, c));
		const auto d4 = 2023y / January / 3d;
		const auto r4 = 2023y / January / 3d;
		EXPECT_EQ(r4, bdc.adjust(d4, c));
	}

	TEST(modified_preceding, adjust2)
	{
		const auto bdc = modified_preceding{};

		const auto& c = make_calendar_england();

		const auto d1 = sys_days{ 2022y / December / 31d };
		const auto r1 = sys_days{ 2022y / December / 30d };
		EXPECT_EQ(r1, bdc.adjust(d1, c));
		const auto d2 = sys_days{ 2022y / December / 30d };
		const auto r2 = sys_days{ 2022y / December / 30d };
		EXPECT_EQ(r2, bdc.adjust(d2, c));

		const auto d3 = sys_days{ 2023y / January / 1d };
		const auto r3 = sys_days{ 2023y / January / 3d };
		EXPECT_EQ(r3, bdc.adjust(d3, c));
		const auto d4 = sys_days{ 2023y / January / 3d };
		const auto r4 = sys_days{ 2023y / January / 3d };
		EXPECT_EQ(r4, bdc.adjust(d4, c));
	}

	TEST(modified_preceding, adjust3)
	{
		// what if we adjust past the end of the calendar?

		const auto bdc = modified_preceding{};

		const auto& c = make_calendar_starts_ends_with_holidays();

		const auto d = sys_days{ 2024y / January / 1d };
		const auto r = sys_days{ 2024y / January / 2d };
		EXPECT_EQ(r, bdc.adjust(d, c));
	}

	TEST(modified_preceding, adjust4)
	{
		// what if we have a calendar without any business days?

		const auto bdc = modified_preceding{};

		const auto& c = make_calendar_all_holidays();

		EXPECT_THROW(bdc.adjust(c.get_schedule().get_from_until().get_from(), c), out_of_range);
	}

}
