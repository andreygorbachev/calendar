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

#include "setup.h"

using namespace std::chrono;


namespace calendar
{

	TEST(business_day_convention, no_adjustment)
	{
		const auto c = calendar{ SaturdaySundayWeekend, parse_ics_england() };

		EXPECT_EQ(2023y / January / 1d, NoAdjustment.adjust(2023y / January / 1d, c));
	}

	TEST(business_day_convention, following)
	{
		const auto c = calendar{ SaturdaySundayWeekend, parse_ics_england() };

		EXPECT_EQ(2023y / January / 3d, Following.adjust(2023y / January / 1d, c));
		EXPECT_EQ(2023y / January / 3d, Following.adjust(2023y / January / 3d, c));
	}

	TEST(business_day_convention, modified_following)
	{
		const auto c = calendar{ SaturdaySundayWeekend, parse_ics_england() };

		EXPECT_EQ(2023y / January / 3d, ModifiedFollowing.adjust(2023y / January / 1d, c));
		EXPECT_EQ(2023y / January / 3d, ModifiedFollowing.adjust(2023y / January / 3d, c));
		// add a test for "modifed"
	}

	TEST(business_day_convention, preceding)
	{
		const auto c = calendar{ SaturdaySundayWeekend, parse_ics_england() };

		EXPECT_EQ(2022y / December / 30d, Preceding.adjust(2023y / January / 1d, c));
		EXPECT_EQ(2022y / December / 30d, Preceding.adjust(2022y / December / 30d, c));
	}

	TEST(business_day_convention, nearest)
	{
		const auto c = calendar{ SaturdaySundayWeekend, parse_ics_england() };

		// Friday
		EXPECT_EQ(2023y / March / 24d, Nearest.adjust(2023y / March / 24d, c));

		// Saturday
		EXPECT_EQ(2023y / March / 24d, Nearest.adjust(2023y / March / 25d, c));

		// Sunday
		EXPECT_EQ(2023y / March / 27d, Nearest.adjust(2023y / March / 26d, c));

		// Monday
		EXPECT_EQ(2023y / March / 27d, Nearest.adjust(2023y / March / 27d, c));
	}

}
