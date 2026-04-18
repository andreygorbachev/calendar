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
			auto release_dates = schedule::dates{};

			for (auto m = period.get_from() / std::chrono::January - std::chrono::months{ 1 }; // reference week is in the previous month of the release date
				m <= period.get_until() / std::chrono::December - std::chrono::months{ 1 };
				m += std::chrono::months{ 1 } // data is released monthly
			)
			{
				const auto _12th_of_reference_month = m / std::chrono::day{ 12u };

				const auto _12th_of_reference_month_weekday = std::chrono::weekday{ _12th_of_reference_month }.c_encoding(); // week Sunday to Saturday
				const auto start_of_reference_period = std::chrono::sys_days{ _12th_of_reference_month } - std::chrono::days{ _12th_of_reference_month_weekday };

				auto release_date = start_of_reference_period +
					std::chrono::days{ 5 } + // move to the Friday of the reference week
					std::chrono::weeks{ 3 }; // move to the third Friday after the reference week

				// Generally, the Employment Situation publication date is the third Friday after the week that includes the 12th.
				// This usually results in the release being scheduled for the first Friday of the month following the reference month.
				// 
				// However, when the 12th of the month falls on a Sunday and there are 30 days or less in the month, the release date will be the second Friday of the month.
				// In addition, if the third Friday after the December reference period falls on January 1–3, the release date will be the second Friday of the month.
				//
				// If the normal release day Friday happens to be a federal holiday, such as July 4th, the release date will be the Thursday immediately preceding the holiday.
				// The Employment Situation release dates are adjusted only for designated federal holidays.
				//
				// The Employment Situation release dates are approved by the Office of Management and Budget and published in advance.

				const auto days_in_reference_month = static_cast<unsigned>(std::chrono::year_month_day_last{ m / std::chrono::last }.day());
					
				const auto release_year_month_day = std::chrono::year_month_day{ release_date };
				const auto release_month = release_year_month_day.month();
				const auto release_day = release_year_month_day.day();
				if (/*(_12th_of_reference_month_weekday == 0 && days_in_reference_month <= 30u) ||*/
					(release_month == std::chrono::January && (release_day == std::chrono::day{ 1u } || release_day == std::chrono::day{ 2u } || release_day == std::chrono::day{ 1u }))
				)
					release_date += std::chrono::weeks{ 1 };

				release_date = Preceding.adjust(release_date, cal);

				release_dates.insert(release_date);
			}

			return schedule{
				util::period{ period.get_from() / FirstDayOfJanuary, period.get_until() / LastDayOfDecember }, // this is unpleasant because we go from years_period to days_period, maybe we should have a constructor of schedule which takes years_period and does the conversion itself, etc
				release_dates
			};
		}

	}

}
