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

	TEST(period, constructor_1)
	{
		const auto p = period{ 2023y / May / 1d, 2023y / May / 31d };

		EXPECT_EQ(2023y / May / 1d, p.get_from());
		EXPECT_EQ(2023y / May / 31d, p.get_until());

		EXPECT_THROW(period(2023y / May / 31d, 2023y / May / 1d), out_of_range);
	}

	TEST(period, constructor_2)
	{
		const auto p = period{ 2023y / April, 2023y / May };

		EXPECT_EQ(2023y / April, p.get_from());
		EXPECT_EQ(2023y / May, p.get_until());

		EXPECT_THROW(period(2023y / May, 2023y / April), out_of_range);
	}

	TEST(period, constructor_3)
	{
		const auto p = period{ 2023y, 2024y };

		EXPECT_EQ(2023y, p.get_from());
		EXPECT_EQ(2024y, p.get_until());

		EXPECT_THROW(period(2024y, 2023y), out_of_range);
	}


	TEST(period, operator_addition_1)
	{
		const auto p1 = period{ 2023y / April / 1d, 2023y / April / 30d };
		const auto p2 = period{ 2023y / May / 1d, 2023y / May / 31d };

		const auto p = p1 + p2;

		EXPECT_EQ(2023y / April / 1d, p.get_from());
		EXPECT_EQ(2023y / May / 31d, p.get_until());

		EXPECT_THROW(p2 + p1, out_of_range);

		EXPECT_THROW(period(2023y / March / 1d, 2023y / March / 31d) + p2, out_of_range);
	}

	TEST(period, operator_addition_2)
	{
		const auto p1 = period{ 2023y / February, 2023y / March };
		const auto p2 = period{ 2023y / April, 2023y / May };

		const auto p = p1 + p2;

		EXPECT_EQ(2023y / February, p.get_from());
		EXPECT_EQ(2023y / May, p.get_until());

		EXPECT_THROW(p2 + p1, out_of_range);

		EXPECT_THROW(period(2023y / January, 2023y / February) + p2, out_of_range);
	}

	TEST(period, operator_addition_3)
	{
		const auto p1 = period{ 2021y, 2022y };
		const auto p2 = period{ 2023y, 2024y };

		const auto p = p1 + p2;

		EXPECT_EQ(2021y, p.get_from());
		EXPECT_EQ(2024y, p.get_until());

		EXPECT_THROW(p2 + p1, out_of_range);

		EXPECT_THROW(period(2020y, 2021y) + p2, out_of_range);
	}
}
