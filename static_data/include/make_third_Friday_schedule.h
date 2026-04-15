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

#pragma once

#include <period.h>
#include <calendar.h>
#include <schedule.h>
#include <business_day_adjusters.h>

#include <chrono>


namespace gregorian
{

	namespace static_data
	{

		inline auto _make_third_Friday_schedule(
			const util::years_period& period,
			const calendar& cal
		) -> schedule
		{
			auto dates = schedule::dates{};

			for (auto month = period.get_from() / std::chrono::January - std::chrono::months{ 1 }; // reference week is in the previous month of the release date
				month <= period.get_until() / std::chrono::December - std::chrono::months{ 1 };
				month += std::chrono::months{ 1 } // data is released monthly
			) // do we look over reference months or over release months?
			{
				const auto _12th = month / std::chrono::day{ 12u };

				const auto start_of_reference_week =
					std::chrono::sys_days{ _12th } - std::chrono::days{ std::chrono::weekday{ _12th }.c_encoding() }; // week Sunday to Saturday

				const auto release_date = start_of_reference_week +
					std::chrono::days{ 5 } + // move to Friday of the reference week
					std::chrono::weeks{ 3 }; // move to the third Friday after reference week

				// it looks like sometimes there are 4 weeks wait for the release, rather than 3, so more is needed here

				const auto adjusted_release_date = Preceding.adjust(release_date, cal);

				dates.insert(adjusted_release_date);
			}

			return schedule{
				util::period{ period.get_from() / FirstDayOfJanuary, period.get_until() / LastDayOfDecember }, // this is unpleasant to go from years_period to days_period, maybe we should have a constructor of schedule which takes years_period and does the conversion itself, etc
				dates
			};
		}

	}

}
