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

#include <holiday_schedule.h>

#include <gtest/gtest.h>

#include <memory>
#include <chrono>
#include <algorithm>

#include "setup.h"

using namespace std;
using namespace std::chrono;


namespace calendar
{

	auto make_April_London_holiday_schedule() -> holiday_schedule
	{
		auto hols = holiday_schedule::storage{
			2023y / April / 7d,
			2023y / April / 10d,
		};

		return holiday_schedule{ 2023y / April / 1d, 2023y / April / 30d, move(hols) };
	}

	auto make_May_London_holiday_schedule() -> holiday_schedule
	{
		auto hols = holiday_schedule::storage{
			2023y / May / 1d,
			2023y / May / 8d,
			2023y / May / 29d,
		};

		return holiday_schedule{ 2023y / May / 1d, 2023y / May / 31d, move(hols) };
	}

	auto make_May_NewYork_holiday_schedule() -> holiday_schedule
	{
		auto hols = holiday_schedule::storage{
			2023y / May / 29d,
		};

		return holiday_schedule{ 2023y / May / 1d, 2023y / May / 31d, move(hols) };
	}


	TEST(holiday_schedule, constructor)
	{
		auto hols = holiday_schedule::storage{};

		EXPECT_THROW(holiday_schedule(2023y / May / 31d, 2023y / May / 1d, move(hols)), out_of_range);
	}


	TEST(holiday_schedule, operator_or)
	{
		const auto& h1 = parse_ics_england();
		const auto& h2 = parse_ics_united_states();

		const auto h = h1 | h2;

		EXPECT_EQ(max(h1.get_front(), h2.get_front()), h.get_front());
		EXPECT_EQ(min(h1.get_back(), h2.get_back()), h.get_back());
	}

	TEST(holiday_schedule, operator_and)
	{
		const auto& h1 = parse_ics_england();
		const auto& h2 = parse_ics_united_states();

		const auto h = h1 & h2;

		EXPECT_EQ(max(h1.get_front(), h2.get_front()), h.get_front());
		EXPECT_EQ(min(h1.get_back(), h2.get_back()), h.get_back());
	}

	TEST(holiday_schedule, operator_equal)
	{
		const auto h1 = parse_ics_england();
		const auto h2 = parse_ics_england();

		EXPECT_EQ(true, h1 == h2);
	}

	TEST(holiday_schedule, operator_not_equal)
	{
		const auto& h1 = parse_ics_england();
		const auto& h2 = parse_ics_united_states();

		EXPECT_EQ(true, h1 != h2);
	}

	TEST(holiday_schedule, operator_plus)
	{
		const auto& h1 = parse_ics_england();
		const auto& h2 = parse_ics_united_states();

		const auto h3 = h1 + h2;
		const auto h4 = h2 + h1;

		EXPECT_EQ(h3.get_front(), h4.get_front());
		EXPECT_EQ(h3.get_back(), h4.get_back());
	}

	TEST(holiday_schedule, get_hols)
	{
		const auto h1 = make_May_London_holiday_schedule();
		const auto h2 = holiday_schedule{ h1.get_front(), h1.get_back(), h1.get_hols() };

		EXPECT_EQ(h2.get_front(), h1.get_front());
		EXPECT_EQ(h2.get_back(), h1.get_back());
	}

	TEST(holiday_schedule, is_holiday)
	{
		const auto h1 = make_May_London_holiday_schedule();
		const auto h3 = make_May_NewYork_holiday_schedule() | h1;
		const auto h4 = make_May_NewYork_holiday_schedule() & h1;
		const auto h5 = make_April_London_holiday_schedule() + h1;

		EXPECT_EQ(true, h1.is_holiday(2023y / May / 1d));
		EXPECT_EQ(true, h3.is_holiday(2023y / May / 1d));
		EXPECT_EQ(false, h4.is_holiday(2023y / May / 1d));
		EXPECT_EQ(true, h3.is_holiday(2023y / May / 1d));
	}

}
