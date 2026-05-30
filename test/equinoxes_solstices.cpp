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

#include <equinoxes_solstices.h>

#include <gtest/gtest.h>

#include <chrono>

using namespace std;
using namespace std::chrono;


namespace gregorian
{

	TEST(_calculate_date, _calculate_date)
	{
		const auto [d, m, y] = _calculate_date(2'436'116.31);
		EXPECT_EQ(1957, y);
		EXPECT_EQ(10, m); // October
		EXPECT_NEAR(4.81, d, 0.01);
	}
/*
	TEST(vernal_equinox, make_holiday)
	{
//		MarchEquinox.make_holiday(1962y);
	}
*/
	TEST(summer_solstice, make_holiday2)
	{
		EXPECT_EQ(1962y / June / 21d, JuneSolstice.make_holiday(1962y));
	}

}
