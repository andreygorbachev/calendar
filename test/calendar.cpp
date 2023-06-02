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

#include <weekend.h>
#include <schedule.h>
#include <calendar.h>
#include <business_day_conventions.h>

#include <gtest/gtest.h>

#include <cstddef>
#include <memory>
#include <chrono>

#include "setup.h"

using namespace std;
using namespace std::chrono;


namespace calendar
{

	TEST(calendar, substitute)
	{
		const auto expected = calendar{
			SaturdaySundayWeekend,
			schedule{
				period{ 2023y / January / 1d, 2023y / January / 31d },
				schedule::storage{
					2023y / January / 2d,
				}
			}
		};

		auto c = calendar{
			SaturdaySundayWeekend,
			schedule{
				period{ 2023y / January / 1d, 2023y / January / 31d },
				schedule::storage{
					2023y / January / 1d,
				}
			}
		};
		c.substitute(&Following);

		EXPECT_EQ(expected, c);
	}

	TEST(calendar, is_business_day)
	{
		const auto c = make_calendar_england();

		EXPECT_FALSE(c.is_business_day(2023y / May / 1d));
		EXPECT_TRUE(c.is_business_day(2023y / May / 2d));
		EXPECT_THROW(c.is_business_day(1y / May / 1d), out_of_range);
		EXPECT_THROW(c.is_business_day(9999y / May / 1d), out_of_range);
	}

	TEST(calendar, count_business_days)
	{
		const auto c = make_calendar_england();

		const auto bd1 = c.count_business_days({ 2023y / May / 1d, 2023y / May / 1d });
		const auto bd2 = c.count_business_days({ 2023y / May / 31d, 2023y / May / 31d });
		const auto bd3 = c.count_business_days({ 2023y / May / 1d, 2023y / May / 31d });

		EXPECT_EQ(0/*uz*/, bd1);
		EXPECT_EQ(1/*uz*/, bd2);
		EXPECT_EQ(20/*uz*/, bd3);
	}

}
