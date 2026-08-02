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

#include <intersect_flat_sets.h>

#include <gtest/gtest.h>

#include <flat_set>

using namespace std;


namespace gregorian
{

	namespace util
	{

		TEST(intersect_flat_sets, intersect_flat_sets1)
		{
			const auto set1 = flat_set{ 1, 2 };
			const auto set2 = flat_set{ 2, 3 };
			const auto set3 = flat_set{ 3, 4 };

			const auto expected1 = flat_set<int>{};
			EXPECT_EQ(expected1, intersect_flat_sets(set1, set3));

			const auto expected2 = flat_set{ 2 };
			EXPECT_EQ(expected2, intersect_flat_sets(set1, set2));

			const auto& expected3 = set1;
			EXPECT_EQ(expected3, intersect_flat_sets(set1, set1));
		}

	}

}
