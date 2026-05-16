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
#include <annual_holiday_interface.h>
#include <annual_holidays.h>

#include <utility>
#include <chrono>

using namespace std;
using namespace std::chrono;


namespace gregorian
{

	using namespace util;

	namespace static_data
	{

		// https://www.zuerich.com/en/inform-plan/useful-information-and-services/opening-hours-and-public-holidays/feiertage

		// should these be in their own namespace?
		const auto _BerchtoldsDay = named_holiday{ January / 2d };
		const auto _LabourDay = named_holiday{ May / 1d };
		const auto _SwissNationalDay = named_holiday{ August / 1d };

		static auto _make_Zurich_known_schedule_part0() -> schedule // or should it be a "proper" function (without _)?
		{
			auto holidays = schedule::dates{ // should we include day of the week into comments?
				2024y / January / 1d, // New Year's Day
				2024y / January / 2d, // Berchtholdstag
				2024y / March / 29d, // Good Friday
				2024y / April / 1d, // Easter Monday
				2024y / May / 1d, // Labour Day
				2024y / May / 9d, // Ascension Day
				2024y / May / 20d, // Whitmonday
				2024y / August / 1d, // National Day
				2024y / December / 24d, // Christmas Eve
				2024y / December / 25d, // Christmas
				2024y / December / 26d, // St. Stephen's Day
				2024y / December / 31d, // New Year's Eve

				2025y / January / 1d, // New Year's Day
				2025y / January / 2d, // Berchtholdstag
				2025y / April / 18d, // Good Friday
				2025y / April / 21d, // Easter Monday
				2025y / May / 1d, // Labour Day
				2025y / May / 29d, // Ascension Day
				2025y / June / 9d, // Whitmonday
				2025y / December / 24d, // Christmas Eve
				2025y / December / 25d, // Christmas
				2025y / December / 26d, // St. Stephen's Day
				2025y / December / 31d, // New Year's Eve

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
				days_period{ 2024y / FirstDayOfJanuary, 2026y / LastDayOfDecember },
				std::move(holidays)
			};
		}

		static auto _make_Zurich_generated_schedule_part0() -> schedule
		{
			const auto rules = annual_holiday_storage{
				&NewYearsDay,
				&_BerchtoldsDay,
				&GoodFriday,
				&EasterMonday,
				// Sechseläuten (afternoon only)
				&_LabourDay,
				&AscensionDay,
				&WhitMonday,
				&_SwissNationalDay,
				// Knabenschiessen (afternoon only)
				&ChristmasEve, // maybe need a separate calendar for SARON as this one is labelled as "afternoon only" and hence might not be a full day off for everyone
				&ChristmasDay,
				&BoxingDay, // St.Stephen’s Day
				&NewYearsEve // Most businesses in Zurich are open on New Year’s Eve but usually shut between 4 PM and 6 PM.
			};

			return make_holiday_schedule(
				util::years_period{ 2027y, Epoch.get_until().year() },
				rules
			);
		}


		auto make_Zurich_calendar_versions() -> _calendar_versions
		{
			auto cal0 = calendar{
				SaturdaySundayWeekend,
				_make_Zurich_known_schedule_part0() +
				_make_Zurich_generated_schedule_part0()
			};

			return {
				{ cal0.get_schedule().get_period().get_from(), std::move(cal0) },
			};
		}

	}

}