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

#include <gtest/gtest.h>

#include <util.h>
#include <static_data.h>

#include <period.h>
#include <schedule.h>

#include <chrono>

using namespace std;
using namespace std::chrono;


namespace gregorian
{

	namespace static_data
	{

		TEST(util, known_period_generated_period1)
		{
			// common case: we have both known and generated periods
			// known period starts at the same time as Epoch starts
			// and ends before the Epoch ends

			const auto schedule_period = util::days_period{
				Epoch.get_from(),
				2025y / LastDayOfDecember
			};

			const auto [known_period, generated_period] = known_period_generated_period(
				schedule_period,
				Epoch
			);

			EXPECT_TRUE(known_period.has_value());
			EXPECT_TRUE(generated_period.has_value());
			EXPECT_EQ(Epoch, *known_period + *generated_period);
		}

	}

}
