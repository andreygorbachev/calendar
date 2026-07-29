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

	TEST(weekend, is_weekend1)
	{
		// Friday
		static_assert(!SaturdaySundayWeekend.is_weekend(2023y / March / 24d));
		static_assert(FridaySaturdayWeekend.is_weekend(2023y / March / 24d));
		static_assert(!SundayWeekend.is_weekend(2023y / March / 24d));
		static_assert(!NoWeekend.is_weekend(2023y / March / 24d));

		// Saturday
		static_assert(SaturdaySundayWeekend.is_weekend(2023y / March / 25d));
		static_assert(FridaySaturdayWeekend.is_weekend(2023y / March / 25d));
		static_assert(!SundayWeekend.is_weekend(2023y / March / 25d));
		static_assert(!NoWeekend.is_weekend(2023y / March / 25d));

		// Sunday
		static_assert(SaturdaySundayWeekend.is_weekend(2023y / March / 26d));
		static_assert(!FridaySaturdayWeekend.is_weekend(2023y / March / 26d));
		static_assert(SundayWeekend.is_weekend(2023y / March / 26d));
		static_assert(!NoWeekend.is_weekend(2023y / March / 26d));

		// Monday
		static_assert(!SaturdaySundayWeekend.is_weekend(2023y / March / 27d));
		static_assert(!FridaySaturdayWeekend.is_weekend(2023y / March / 27d));
		static_assert(!SundayWeekend.is_weekend(2023y / March / 27d));
		static_assert(!NoWeekend.is_weekend(2023y / March / 27d));
	}

	TEST(weekend, is_weekend2)
	{
		// Friday
		static_assert(!SaturdaySundayWeekend.is_weekend(sys_days{ 2023y / March / 24d }));
		static_assert(FridaySaturdayWeekend.is_weekend(sys_days{ 2023y / March / 24d }));
		static_assert(!SundayWeekend.is_weekend(sys_days{ 2023y / March / 24d }));
		static_assert(!NoWeekend.is_weekend(sys_days{ 2023y / March / 24d }));

		// Saturday
		static_assert(SaturdaySundayWeekend.is_weekend(sys_days{ 2023y / March / 25d }));
		static_assert(FridaySaturdayWeekend.is_weekend(sys_days{ 2023y / March / 25d }));
		static_assert(!SundayWeekend.is_weekend(sys_days{ 2023y / March / 25d }));
		static_assert(!NoWeekend.is_weekend(sys_days{ 2023y / March / 25d }));

		// Sunday
		static_assert(SaturdaySundayWeekend.is_weekend(sys_days{ 2023y / March / 26d }));
		static_assert(!FridaySaturdayWeekend.is_weekend(sys_days{ 2023y / March / 26d }));
		static_assert(SundayWeekend.is_weekend(sys_days{ 2023y / March / 26d }));
		static_assert(!NoWeekend.is_weekend(sys_days{ 2023y / March / 26d }));

		// Monday
		static_assert(!SaturdaySundayWeekend.is_weekend(sys_days{ 2023y / March / 27d }));
		static_assert(!FridaySaturdayWeekend.is_weekend(sys_days{ 2023y / March / 27d }));
		static_assert(!SundayWeekend.is_weekend(sys_days{ 2023y / March / 27d }));
		static_assert(!NoWeekend.is_weekend(sys_days{ 2023y / March / 27d }));
	}


	TEST(weekend, operator_bitwise_or)
	{
		constexpr auto w = FridaySaturdayWeekend | SaturdaySundayWeekend;

		// Friday
		static_assert(w.is_weekend(2023y / March / 24d));

		// Saturday
		static_assert(w.is_weekend(2023y / March / 25d));

		// Sunday
		static_assert(w.is_weekend(2023y / March / 26d));

		// Monday
		static_assert(!w.is_weekend(2023y / March / 27d));
	}


	TEST(weekend, operator_bitwise_and)
	{
		constexpr auto w = FridaySaturdayWeekend & SaturdaySundayWeekend;

		// Friday
		static_assert(!w.is_weekend(2023y / March / 24d));

		// Saturday
		static_assert(w.is_weekend(2023y / March / 25d));

		// Sunday
		static_assert(!w.is_weekend(2023y / March / 26d));

		// Monday
		static_assert(!w.is_weekend(2023y / March / 27d));
	}


	TEST(weekend, operator_equal_to)
	{
		static_assert(SaturdaySundayWeekend == SaturdaySundayWeekend);
	}


	TEST(weekend, operator_not_equal_to)
	{
		static_assert(SaturdaySundayWeekend != SundayWeekend);
	}


	TEST(weekend, get_we)
	{
		constexpr auto we = SaturdaySundayWeekend.get_we();

		static_assert(SaturdaySundayWeekend == weekend{ we });
	}

}
