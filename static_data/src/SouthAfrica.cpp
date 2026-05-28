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
#include <business_day_adjusters.h>

#include <utility>
#include <chrono>

using namespace std;
using namespace std::chrono;


namespace gregorian
{

	using namespace util;

	namespace static_data
	{

		// https://www.openhr.co.za/blog/1092-south-africa-s-2026-public-holidays

		// * Good Friday and Easter Sunday are determined by the ecclesiastical moon, falling between late March and late April.
		// ** In terms of the Public Holidays Act, when a holiday falls on a Sunday, the following Monday is observed.

		// should these be in their own namespace?
		const auto _HumanRightsDay = named_holiday{ March / 21d };
		const auto _FreedomDay = named_holiday{ April / 27d };
		const auto _WorkersDay = named_holiday{ May / 1d };
		const auto _YouthDay = named_holiday{ June / 16d };
		const auto _NationalWomensDay = named_holiday{ August / 9d };
		const auto _HeritageDay = named_holiday{ September / 24d };
		const auto _DayOfReconciliation = named_holiday{ December / 16d };

		static auto _make_Johannesburg_known_schedule_part0() -> schedule // or should it be a "proper" function (without _)?
		{
			auto holidays = schedule::dates{ // should we include day of the week into comments?

				// 2022 (Implied from ZARONIA history)
				// partial, as ZARONIA history starts from 2022-04-28
				2022y / May / 2d, // Workers' Day (Observed)
				2022y / June / 16d, // Youth Day
				2022y / August / 9d, // National Women's Day
				2022y / December / 16d, // Day of Reconciliation
				2022y / December / 26d, // Day of Goodwill
				2022y / December / 27d, // Christmas Day (Observed)

				// 2023 (Implied from ZARONIA history)
				2023y / January / 2d, // New Year's Day (Observed)
				2023y / March / 21d, // Human Rights Day
				2023y / April / 7d, // Good Friday
				2023y / April / 10d, // Family Day
				2023y / April / 27d, // Freedom Day
				2023y / May / 1d, // Workers' Day
				2023y / June / 16d, // Youth Day
				2023y / August / 9d, // National Women's Day
				2023y / September / 25d, // Heritage Day (Observed)
				2023y / December / 15d, // Special Public Holiday (Rugby World Cup Win)
				2023y / December / 25d, // Christmas Day
				2023y / December / 26d, // Day of Goodwill

				// 2024 (Implied from ZARONIA history)
				2024y / January / 1d, // New Year's Day
				2024y / March / 21d, // Human Rights Day
				2024y / March / 29d, // Good Friday
				2024y / April / 1d, // Family Day
				2024y / May / 1d, // Workers' Day
				2024y / May / 29d, // National Elections
				2024y / June / 17d, // Youth Day (Observed)
				2024y / August / 9d, // National Women's Day
				2024y / September / 24d, // Heritage Day
				2024y / December / 16d, // Day of Reconciliation
				2024y / December / 25d, // Christmas Day
				2024y / December / 26d, // Day of Goodwill

				// 2025 (Implied from ZARONIA history)
				2025y / January / 1d, // New Year's Day
				2025y / March / 21d, // Human Rights Day
				2025y / April / 18d, // Good Friday
				2025y / April / 21d, // Family Day
				2025y / April / 28d, // Freedom Day (Observed)
				2025y / May / 1d, // Workers' Day
				2025y / June / 16d, // Youth Day
				2025y / September / 24d, // Heritage Day
				2025y / December / 16d, // Day of Reconciliation
				2025y / December / 25d, // Christmas Day
				2025y / December / 26d, // Day of Goodwill

				2026y / January / 1d, // New Year's Day
				2026y / March / 21d, // Human Rights Day
				2026y / April / 3d, // Good Friday
				2026y / April / 6d, // Family Day
				2026y / April / 27d, // Freedom Day
				2026y / May / 1d, // Workers' Day
				2026y / June / 16d, // Youth Day
				2026y / August / 10d, // Public holiday (Women's Day observed)
				2026y / September / 24d, // Heritage Day
				2026y / December / 16d, // Day of Reconciliation
				2026y / December / 25d, // Christmas Day
				2026y / December / 26d, // Day of Goodwill
			};

			return schedule{
				days_period{ 2022y / FirstDayOfJanuary, 2026y / LastDayOfDecember },
				std::move(holidays)
			};
		}

		static auto _make_Johannesburg_generated_schedule_part0() -> schedule
		{
			const auto rules = annual_holiday_storage{
				&NewYearsDay,
				&_HumanRightsDay,
				&GoodFriday,
				&EasterMonday,
				&_FreedomDay,
				&_WorkersDay,
				&_YouthDay,
				&_NationalWomensDay,
				&_HeritageDay,
				&_DayOfReconciliation,
				&ChristmasDay,
				&BoxingDay
			};

			const auto s = make_holiday_schedule(
				util::years_period{ 2027y, Epoch.get_until().year() },
				rules
			);

			auto cal = calendar{
				SundayWeekend, // to move Sunday holidays to Monday, as per the documentation
				s
			};
			cal.substitute(Following);

			return cal.get_schedule();
		}


		auto make_Johannesburg_calendar_versions() -> _calendar_versions
		{
			auto cal0 = calendar{
				SaturdaySundayWeekend,
				_make_Johannesburg_known_schedule_part0() +
				_make_Johannesburg_generated_schedule_part0()
			};

			return {
				{ cal0.get_schedule().get_period().get_from(), std::move(cal0) },
				// 23 February 2024 https://www.thepresidency.gov.za/president-proclaims-election-date-and-public-holiday#:~:text=The%20proclamation%20on%20the%20election,public%20holiday%20throughout%20the%20Republic.
				// 28 November 2023 PROCLAMATION 143 OF 2023
			};
		}

	}

}
