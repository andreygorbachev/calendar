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

#include <period.h>

#include <gtest/gtest.h>

#include <chrono>
#include <stdexcept>

using namespace std;
using namespace std::chrono;


namespace gregorian
{

	namespace util
	{

		TEST(period, default_constructor)
		{
			constexpr auto p = period<year_month_day>{};

			static_assert(year_month_day{} == p.get_from());
			static_assert(year_month_day{} == p.get_until());
		}

		TEST(period, constructor_1)
		{
			constexpr auto p = period{ 2023y / May / 1d, 2023y / May / 31d };

			static_assert(2023y / May / 1d == p.get_from());
			static_assert(2023y / May / 31d == p.get_until());

			EXPECT_THROW(period(2023y / May / 31d, 2023y / May / 1d), out_of_range);
		}

		TEST(period, constructor_2)
		{
			constexpr auto p = period{ 2023y / April, 2023y / May };

			static_assert(2023y / April == p.get_from());
			static_assert(2023y / May == p.get_until());

			EXPECT_THROW(period(2023y / May, 2023y / April), out_of_range);
		}

		TEST(period, constructor_3)
		{
			constexpr auto p = period{ 2023y, 2024y };

			static_assert(2023y == p.get_from());
			static_assert(2024y == p.get_until());

			EXPECT_THROW(period(2024y, 2023y), out_of_range);
		}

		TEST(period, constructor_4)
		{
			constexpr auto f = sys_days{ 2023y / May / 1d };
			constexpr auto u = sys_days{ 2023y / May / 31d };

			constexpr auto p = period{ f, u };

			static_assert(f == p.get_from());
			static_assert(u == p.get_until());

			EXPECT_THROW(period(u, f), out_of_range);
		}

		TEST(period, constructor_5)
		{
			constexpr auto p = period{ pair{ 2023y / May / 1d, 2023y / May / 31d } };

			static_assert(2023y / May / 1d == p.get_from());
			static_assert(2023y / May / 31d == p.get_until());

			EXPECT_THROW(period(2023y / May / 31d, 2023y / May / 1d), out_of_range);
		}


		TEST(period, get_from)
		{
			constexpr auto p = period{ 2023y / May / 1d, 2023y / May / 31d };

			static_assert(2023y / May / 1d == p.get_from());
		}

		TEST(period, get_unti)
		{
			constexpr auto p = period{ 2023y / May / 1d, 2023y / May / 31d };

			static_assert(2023y / May / 31d == p.get_until());
		}

		TEST(period, from_until)
		{
			constexpr auto p = period{ pair{ 2023y / May / 1d, 2023y / May / 31d } };

			constexpr auto expected = pair{ 2023y / May / 1d, 2023y / May / 31d };
			static_assert(expected == p.from_until());
		}

		TEST(period, operator_addition_1)
		{
			constexpr auto p1 = period{ 2023y / April / 1d, 2023y / April / 30d };
			constexpr auto p2 = period{ 2023y / May / 1d, 2023y / May / 31d };

			constexpr auto p = p1 + p2;

			static_assert(2023y / April / 1d == p.get_from());
			static_assert(2023y / May / 31d == p.get_until());

			EXPECT_THROW(static_cast<void>(p2 + p1), out_of_range);

			EXPECT_THROW(static_cast<void>(period(2023y / March / 1d, 2023y / March / 31d) + p2), out_of_range);
		}

		TEST(period, operator_addition_2)
		{
			constexpr auto p1 = period{ 2023y / February, 2023y / March };
			constexpr auto p2 = period{ 2023y / April, 2023y / May };

			constexpr auto p = p1 + p2;

			static_assert(2023y / February == p.get_from());
			static_assert(2023y / May == p.get_until());

			EXPECT_THROW(static_cast<void>(p2 + p1), out_of_range);

			EXPECT_THROW(static_cast<void>(period(2023y / January, 2023y / February) + p2), out_of_range);
		}

		TEST(period, operator_addition_3)
		{
			constexpr auto p1 = period{ 2021y, 2022y };
			constexpr auto p2 = period{ 2023y, 2024y };

			constexpr auto p = p1 + p2;

			static_assert(2021y == p.get_from());
			static_assert(2024y == p.get_until());

			EXPECT_THROW(static_cast<void>(p2 + p1), out_of_range);

			EXPECT_THROW(static_cast<void>(period(2020y, 2021y) + p2), out_of_range);
		}


		TEST(period, operator_bitwise_and)
		{
			constexpr auto p1 = period{ 2023y / March / 1d, 2023y / April / 30d };
			constexpr auto p2 = period{ 2023y / April / 1d, 2023y / May / 31d };

			constexpr auto p = p1 & p2;

			static_assert(p == (p2 & p1));

			static_assert(2023y / April / 1d == p.get_from());
			static_assert(2023y / April / 30d == p.get_until());

			EXPECT_THROW(static_cast<void>(period(2023y / January / 1d, 2023y / February / 28d) & p2), out_of_range);
		}

		TEST(period, operator_bitwise_or)
		{
			constexpr auto p1 = period{ 2023y / March / 1d, 2023y / April / 30d };
			constexpr auto p2 = period{ 2023y / April / 1d, 2023y / May / 31d };

			constexpr auto p = p1 | p2;

			static_assert(p == (p2 | p1));

			static_assert(2023y / March / 1d == p.get_from());
			static_assert(2023y / May / 31d == p.get_until());

			EXPECT_THROW(static_cast<void>(period(2023y / January / 1d, 2023y / February / 28d) | p2), out_of_range);
		}


		TEST(period, operator_equal_to)
		{
			constexpr auto p1 = period{ 2023y / May / 1d, 2023y / May / 31d };
			constexpr auto p2 = period{ 2023y / May / 1d, 2023y / May / 31d };

			static_assert(p1 == p2);
		}

		TEST(period, operator_not_equal_to)
		{
			constexpr auto p1 = period{ 2023y / May / 1d, 2023y / May / 31d };
			constexpr auto p2 = period{ 2024y / May / 1d, 2024y / May / 31d };

			static_assert(p1 != p2);
		}


		TEST(period, contains1)
		{
			constexpr auto p = period{ 2023y / May / 1d, 2023y / May / 31d };

			static_assert(p.contains(2023y / May / 1d));
			static_assert(p.contains(2023y / May / 2d));
			static_assert(p.contains(2023y / May / 31d));

			static_assert(!p.contains(2023y / April / 30d));
			static_assert(!p.contains(2023y / June / 1d));
		}

		TEST(period, contains2)
		{
			constexpr auto p = period{ sys_days{ 2023y / May / 1d }, sys_days{ 2023y / May / 31d } };

			static_assert(p.contains(2023y / May / 1d));
			static_assert(p.contains(sys_days{ 2023y / May / 1d }));
			static_assert(p.contains(2023y / May / 2d));
			static_assert(p.contains(sys_days{ 2023y / May / 2d }));
			static_assert(p.contains(2023y / May / 31d));
			static_assert(p.contains(sys_days{ 2023y / May / 31d }));

			static_assert(!p.contains(2023y / April / 30d));
			static_assert(!p.contains(sys_days{ 2023y / April / 30d }));
			static_assert(!p.contains(2023y / June / 1d));
			static_assert(!p.contains(sys_days{ 2023y / June / 1d }));
		}

		// add a test for contains(period)

	}

}