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
#include <calendar.h>
#include <weekend.h>

#include <utility>
#include <chrono>

using namespace std;
using namespace std::chrono;


namespace gregorian
{

	using namespace util;

	namespace static_data
	{

		static auto _make_Zurich_known_schedule_part0() -> schedule // or should it be a "proper" function (without _)?
		{
			auto holidays = schedule::dates{ // should we include day of the week into comments?
				2026y / January / 1d, // New Year's Day
				2026y / January / 2d, // Berchtholdstag
				2026y / April / 3d, // Good Friday
				2026y / April / 6d, // Easter Monday
				2026y / May / 1d, // Labour Day
				2026y / May / 14d, // Ascension Day
				2026y / May / 25d, // Whitmonday
				2026y / December / 24d, // Christmas Eve
				2026y / December / 25d, // Christmas
				2026y / December / 31d, // New Year's Eve
			};

			return schedule{
				days_period{ 2026y / FirstDayOfJanuary, 2026y / LastDayOfDecember },
				std::move(holidays)
			};
		}

		auto make_Zurich_calendar_versions() -> _calendar_versions
		{
			const auto known_part = _make_Zurich_known_schedule_part0();

			auto cal0 = calendar{
				SaturdaySundayWeekend,
				known_part
			};

			return {
				{ cal0.get_schedule().get_period().get_from(), std::move(cal0) },
			};
		}

	}

}