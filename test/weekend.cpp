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

#include <gtest/gtest.h>

#include <chrono>

using namespace std::chrono;


namespace gregorian
{

	TEST(weekend, is_weekend)
	{
		// Friday
		EXPECT_FALSE(SaturdaySundayWeekend.is_weekend(2023y / March / 24d));
		EXPECT_TRUE(FridaySaturdayWeekend.is_weekend(2023y / March / 24d));
		EXPECT_FALSE(SundayWeekend.is_weekend(2023y / March / 24d));
		EXPECT_FALSE(NoWeekend.is_weekend(2023y / March / 24d));

		// Saturday
		EXPECT_TRUE(SaturdaySundayWeekend.is_weekend(2023y / March / 25d));
		EXPECT_TRUE(FridaySaturdayWeekend.is_weekend(2023y / March / 25d));
		EXPECT_FALSE(SundayWeekend.is_weekend(2023y / March / 25d));
		EXPECT_FALSE(NoWeekend.is_weekend(2023y / March / 25d));

		// Sunday
		EXPECT_TRUE(SaturdaySundayWeekend.is_weekend(2023y / March / 26d));
		EXPECT_FALSE(FridaySaturdayWeekend.is_weekend(2023y / March / 26d));
		EXPECT_TRUE(SundayWeekend.is_weekend(2023y / March / 26d));
		EXPECT_FALSE(NoWeekend.is_weekend(2023y / March / 26d));

		// Monday
		EXPECT_FALSE(SaturdaySundayWeekend.is_weekend(2023y / March / 27d));
		EXPECT_FALSE(FridaySaturdayWeekend.is_weekend(2023y / March / 27d));
		EXPECT_FALSE(SundayWeekend.is_weekend(2023y / March / 27d));
		EXPECT_FALSE(NoWeekend.is_weekend(2023y / March / 27d));
	}


	TEST(weekend, operator_or)
	{
		const auto w = FridaySaturdayWeekend | SaturdaySundayWeekend;

		// Friday
		EXPECT_TRUE(w.is_weekend(2023y / March / 24d));

		// Saturday
		EXPECT_TRUE(w.is_weekend(2023y / March / 25d));

		// Sunday
		EXPECT_TRUE(w.is_weekend(2023y / March / 26d));

		// Monday
		EXPECT_FALSE(w.is_weekend(2023y / March / 27d));
	}


	TEST(weekend, operator_and)
	{
		const auto w = FridaySaturdayWeekend & SaturdaySundayWeekend;

		// Friday
		EXPECT_FALSE(w.is_weekend(2023y / March / 24d));

		// Saturday
		EXPECT_TRUE(w.is_weekend(2023y / March / 25d));

		// Sunday
		EXPECT_FALSE(w.is_weekend(2023y / March / 26d));

		// Monday
		EXPECT_FALSE(w.is_weekend(2023y / March / 27d));
	}


	TEST(weekend, operator_equal)
	{
		EXPECT_TRUE(SaturdaySundayWeekend == SaturdaySundayWeekend);
	}


	TEST(weekend, operator_not_equal)
	{
		EXPECT_TRUE(SaturdaySundayWeekend != SundayWeekend);
	}


	TEST(weekend, get_we)
	{
		const auto we = SaturdaySundayWeekend.get_we();

		EXPECT_EQ(SaturdaySundayWeekend, weekend{ we });
	}

}
