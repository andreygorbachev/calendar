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

#include <iota.h>
#include <period.h>

#include <gtest/gtest.h>

#include <chrono>
#include <ranges>
#include <vector>

using namespace std;
using namespace std::chrono;


namespace gregorian
{

	namespace util
	{

		TEST(iota, iota1)
		{
			const auto p = days_period{ 2025y / May / 25d, 2025y / May / 30d };

			const auto s =
				util::iota(p) |
				std::ranges::to<vector>();

			const auto expected = vector<sys_days>{
				2025y / May / 25d,
				2025y / May / 26d,
				2025y / May / 27d,
				2025y / May / 28d,
				2025y / May / 29d,
				2025y / May / 30d
			};

			EXPECT_EQ(expected, s);
		}

		TEST(iota, iota2)
		{
			const auto p = days_period{ 2025y / May / 25d, 2025y / May / 25d };

			const auto s =
				util::iota(p) |
				std::ranges::to<vector>();

			const auto expected = vector<sys_days>{
				2025y / May / 25d
			};

			EXPECT_EQ(expected, s);
		}

	}

}
