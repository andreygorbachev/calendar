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

#include <make_third_Friday_schedule.h>

#include <period.h>
#include <schedule.h>
#include <static_data.h>

#include <gtest/gtest.h>

#include <chrono>

using namespace std::chrono;


namespace gregorian
{

	namespace static_data
	{

		TEST(_make_third_Friday_schedule, make_third_Friday_schedule)
		{
			// from  https://www.bls.gov/schedule/news_release/empsit.htm

			const auto expected = schedule{
				util::days_period{ 2026y / FirstDayOfJanuary, 2026y / LastDayOfDecember },
				schedule::dates{
					2026y / January / 9d, // case when the Januiary's release falls on 1st, 2nd or 3rd
//					2026y / February / 11d, // probably government shutdown in 2026, so the release is later than usual
					2026y / February / 6d,
					2026y / March / 6d,
					2026y / April / 3d,
					2026y / May / 8d,
					2026y / June / 5d,
					2026y / July / 2d,
					2026y / August / 7d,
					2026y / September / 4d,
					2026y / October / 2d,
					2026y / November / 6d,
					2026y / December / 4d
				}
			};

			const auto jobs_report_schedule = _make_third_Friday_schedule(
				util::years_period{ 2026y, 2026y },
				locate_calendar("America/USA", 2026y / FirstDayOfJanuary)
			);

			EXPECT_EQ(expected, jobs_report_schedule);
		}

	}

	// we also need to test the case when the 12th falls on Sunday and there are 30 days or less in the month, so the release date will be the second Friday of the month, and the case when the third Friday after the December reference period falls on January 1–3, so the release date will be the second Friday of the month, and the case when the normal release day Friday happens to be a federal holiday, such as July 4th, so the release date will be the Thursday immediately preceding the holiday

}
