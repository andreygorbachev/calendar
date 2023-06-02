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
#include <ics_parser.h>

#include <gtest/gtest.h>

#include <chrono>

#include "setup.h"

using namespace std;
using namespace std::chrono;


namespace calendar
{

	namespace parser
	{

		auto test_parse_ics_holidays() -> const schedule::storage&
		{
			static auto fs = ifstream{ EnglandAndWalesICS };
			static auto hols = _parse_ics(fs);

			return hols;
		}


		TEST(parser, _make_from)
		{
			EXPECT_EQ(2018y / January / 1d, _make_from(test_parse_ics_holidays()));
		}

		TEST(parser, _make_until)
		{
			EXPECT_EQ(2025y / December / 31d, _make_until(test_parse_ics_holidays()));
		}

		TEST(parser, _make_from_until)
		{
			const auto expected = period{ 2018y / January / 1d, 2025y / December / 31d };

			EXPECT_EQ(expected, _make_from_until(test_parse_ics_holidays()));
		}


		TEST(parser, parce_ics1)
		{
			const auto expected = calendar{ SaturdaySundayWeekend, parse_ics_england() };

			auto c = calendar{ SaturdaySundayWeekend, make_holiday_schedule_england() };
			c.substitute(&Following);

			EXPECT_EQ(expected, c);
		}

		TEST(parser, parse_ics2)
		{
			const auto expected = calendar{ SaturdaySundayWeekend, parse_ics_united_states() };

			auto c = calendar{ SaturdaySundayWeekend, make_holiday_schedule_united_states() };
			c.substitute(&Nearest);

			EXPECT_EQ(expected, c);
		}

	}

}
