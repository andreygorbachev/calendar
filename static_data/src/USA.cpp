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

#include <schedule.h>
#include <annual_holidays.h>
#include <weekend.h>
#include <business_day_adjusters.h>

using namespace std;
using namespace std::chrono;


namespace gregorian
{

	using namespace util;

	namespace static_data
	{

		auto _USA_Federal_schedule() -> schedule // or should it be a "proper" function (without _)?
		{
			auto holidays = schedule::dates{ // website has history going back to 2011
				2018y / January / 1d,
				2018y / January / 15d,
				2018y / February / 19d,
				2018y / May / 28d,
				2018y / July / 4d,
				2018y / September / 3d,
				2018y / October / 8d,
				2018y / November / 12d,
				2018y / November / 22d,
				2018y / December / 25d,

				2019y / January / 1d,
				2019y / January / 21d,
				2019y / February / 18d,
				2019y / May / 27d,
				2019y / July / 4d,
				2019y / September / 2d,
				2019y / October / 14d,
				2019y / November / 11d,
				2019y / November / 28d,
				2019y / December / 25d,

				2020y / January / 1d,
				2020y / January / 20d,
				2020y / February / 17d,
				2020y / May / 25d,
				2020y / July / 3d,
				2020y / September / 7d,
				2020y / October / 12d,
				2020y / November / 11d,
				2020y / November / 26d,
				2020y / December / 25d,

				2021y / January / 1d,
				2021y / January / 18d,
				2021y / February / 15d,
				2021y / May / 31d,
				2021y / June / 18d,
				2021y / July / 5d,
				2021y / September / 6d,
				2021y / October / 11d,
				2021y / November / 11d,
				2021y / November / 25d,
				2021y / December / 24d,

				2021y / December / 31d,
				2022y / January / 17d,
				2022y / February / 21d,
				2022y / May / 30d,
				2022y / June / 20d,
				2022y / July / 4d,
				2022y / September / 5d,
				2022y / October / 10d,
				2022y / November / 11d,
				2022y / November / 24d,
				2022y / December / 26d,

				2023y / January / 2d,
				2023y / January / 16d,
				2023y / February / 20d,
				2023y / May / 29d,
				2023y / June / 19d,
				2023y / July / 4d,
				2023y / September / 4d,
				2023y / October / 9d,
				2023y / November / 10d,
				2023y / November / 23d,
				2023y / December / 25d,

				2024y / January / 1d,
				2024y / January / 15d,
				2024y / February / 19d,
				2024y / May / 27d,
				2024y / June / 19d,
				2024y / July / 4d,
				2024y / September / 2d,
				2024y / October / 14d,
				2024y / November / 11d,
				2024y / November / 28d,
				2024y / December / 25d,

				2025y / January / 1d,
				2025y / January / 20d,
				2025y / February / 17d,
				2025y / May / 26d,
				2025y / June / 19d,
				2025y / July / 4d,
				2025y / September / 1d,
				2025y / October / 13d,
				2025y / November / 11d,
				2025y / November / 27d,
				2025y / December / 25d,

				2026y / January / 1d,
				2026y / January / 19d,
				2026y / February / 16d,
				2026y / May / 25d,
				2026y / June / 19d,
				2026y / July / 3d,
				2026y / September / 7d,
				2026y / October / 12d,
				2026y / November / 11d,
				2026y / November / 26d,
				2026y / December / 25d,

				2027y / January / 1d,
				2027y / January / 18d,
				2027y / February / 15d,
				2027y / May / 31d,
				2027y / June / 18d,
				2027y / July / 5d,
				2027y / September / 6d,
				2027y / October / 11d,
				2027y / November / 11d,
				2027y / November / 25d,
				2027y / December / 24d,

				// more available
			};

			return schedule{
				days_period{ Epoch.get_from(), year{ 2027 } / LastDayOfDecember },
				move(holidays)
			};
		}

		auto _make_USA_Federal_calendar() -> calendar
		{
			const auto known_part = _USA_Federal_schedule();

			const auto generated_part_from = known_part.get_period().get_until().year() + years{ 1 };
			const auto generated_part_until = Epoch.get_until().year();

			const auto MartinLutherKing = weekday_indexed_holiday{ January / Monday[3] }; // Birthday Of Martin Luther King, Jr.
			const auto Washington = weekday_indexed_holiday{ February / Monday[3] }; // Washington's Birthday
			const auto MemorialDay = weekday_last_holiday{ May / Monday[last] };
			const auto Juneteenth = named_holiday{ June / day{ 19u } }; // Emancipation Day
			const auto IndependenceDay = named_holiday{ July / day{ 4u } };
			const auto LaborDay = weekday_indexed_holiday{ September / Monday[1] };
			const auto ColumbusDay = weekday_indexed_holiday{ October / Monday[2] };
			const auto VeteransDay = named_holiday{ November / day{ 11u } };
			const auto ThanksgivingDay = weekday_indexed_holiday{ November / Thursday[4] };

			const auto rules = annual_holiday_storage{
				&NewYearsDay,
				&MartinLutherKing,
				&Washington,
				&MemorialDay,
				&Juneteenth,
				&IndependenceDay,
				&LaborDay,
				&ColumbusDay,
				&VeteransDay,
				&ThanksgivingDay,
				&ChristmasDay
			};

			const auto generated_part = make_holiday_schedule(
				years_period{ generated_part_from, generated_part_until },
				rules
			);

			// setup a calendar for the generated part only (to do substitution for the generated dates)
			auto cal = calendar{
				SaturdaySundayWeekend,
				generated_part
			};
			cal.substitute(Nearest);

			return calendar{
				SaturdaySundayWeekend,
				known_part + cal.get_schedule()
			};
		}



		auto make_USA_Federal_calendar() -> const calendar&
		{
			static const auto s = _make_USA_Federal_calendar();
			return s;
		}

	}

}
