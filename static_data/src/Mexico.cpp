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

#include "static_data.h"
#include "makers.h"

#include <period.h>
#include <schedule.h>
#include <weekend.h>
#include <annual_holiday_interface.h>
#include <annual_holidays.h>
#include <calendar.h>

#include <chrono>
#include <utility>

using namespace std;
using namespace std::chrono;


namespace gregorian
{

	using namespace util;

	namespace static_data
	{

		// from Bank of Mexico website:
		// 
		// 2026 bank holidays
		// 
		// • January 1.
		// • The first Monday of February in commemoration of February 5.
		// • The third Monday of March in commemoration of March 21.
		// • April 2 and 3.
		// • May 1.
		// • September 16.
		// • November 2 and the third Monday of the month in commemoration of November 20.
		// • December 12 and 25.
		// • Saturdays and Sundays.


		static auto _make_CNBV_known_schedule_part0() -> schedule // is it a correct name? (CNBV)
		{
			auto holidays = schedule::dates{ // should we include day of the week into comments?
			};

			return schedule{
				days_period{ 2026y / FirstDayOfJanuary, 2026y / LastDayOfDecember },
				std::move(holidays)
			};
		}



		static auto _make_CNBV_generated_schedule_part0() -> schedule
		{
			const auto rules = annual_holiday_storage{
			};

			return make_holiday_schedule(
				util::years_period{ 2027y, Epoch.get_until().year() },
				rules
			);
		}

		auto make_CNBV_calendar_versions() -> _calendar_versions
		{
			auto cal0 = calendar{
				SaturdaySundayWeekend,
				_make_CNBV_known_schedule_part0() +
				_make_CNBV_generated_schedule_part0()
			};

			return {
				{ cal0.get_schedule().get_period().get_from(), std::move(cal0) },
			};
		}

	}

}
