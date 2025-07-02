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
			auto holidays = schedule::dates{
				2010y / December / 31d, // we actually do not keep it in the 2011 calendar
				2011y / January / 17d,
				2011y / February / 21d,
				2011y / May / 30d,
				2011y / July / 4d,
				2011y / September / 5d,
				2011y / October / 10d,
				2011y / November / 11d,
				2011y / November / 24d,
				2011y / December / 26d,

				2012y / January / 2d,
				2012y / January / 16d,
				2012y / February / 20d,
				2012y / May / 28d,
				2012y / July / 4d,
				2012y / September / 3d,
				2012y / October / 8d,
				2012y / November / 12d,
				2012y / November / 22d,
				2012y / December / 25d,

				2013y / January / 1d,
				2013y / January / 21d,
				2013y / February / 18d,
				2013y / May / 27d,
				2013y / July / 4d,
				2013y / September / 2d,
				2013y / October / 14d,
				2013y / November / 11d,
				2013y / November / 28d,
				2013y / December / 25d,

				2014y / January / 1d,
				2014y / January / 20d,
				2014y / February / 17d,
				2014y / May / 26d,
				2014y / July / 4d,
				2014y / September / 1d,
				2014y / October / 13d,
				2014y / November / 11d,
				2014y / November / 27d,
				2014y / December / 25d,

				2015y / January / 1d,
				2015y / January / 19d,
				2015y / February / 16d,
				2015y / May / 25d,
				2015y / July / 3d,
				2015y / September / 7d,
				2015y / October / 12d,
				2015y / November / 11d,
				2015y / November / 26d,
				2015y / December / 25d,

				2016y / January / 1d,
				2016y / January / 18d,
				2016y / February / 15d,
				2016y / May / 30d,
				2016y / July / 4d,
				2016y / September / 5d,
				2016y / October / 10d,
				2016y / November / 11d,
				2016y / November / 24d,
				2016y / December / 26d,

				2017y / January / 2d,
				2017y / January / 16d,
				2017y / February / 20d,
				2017y / May / 29d,
				2017y / July / 4d,
				2017y / September / 4d,
				2017y / October / 9d,
				2017y / November / 10d,
				2017y / November / 23d,
				2017y / December / 25d,

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

				2027y / December / 31d,
				2028y / January / 17d,
				2028y / February / 21d,
				2028y / May / 29d,
				2028y / June / 19d,
				2028y / July / 4d,
				2028y / September / 4d,
				2028y / October / 9d,
				2028y / November / 10d,
				2028y / November / 23d,
				2028y / December / 25d,

				2029y / January / 1d,
				2029y / January / 15d,
				2029y / February / 19d,
				2029y / May / 28d,
				2029y / June / 19d,
				2029y / July / 4d,
				2029y / September / 3d,
				2029y / October / 8d,
				2029y / November / 12d,
				2029y / November / 22d,
				2029y / December / 25d,

				2030y / January / 1d,
				2030y / January / 21d,
				2030y / February / 18d,
				2030y / May / 27d,
				2030y / June / 19d,
				2030y / July / 4d,
				2030y / September / 2d,
				2030y / October / 14d,
				2030y / November / 11d,
				2030y / November / 28d,
				2030y / December / 25d,
			};

			return schedule{
				days_period{ Epoch.get_from(), 2030y / LastDayOfDecember },
				move(holidays)
			};
		}

		auto _Washington_DC_Federal_schedule() -> schedule // or should it be a "proper" function (without _)?
		{
			auto holidays = schedule::dates{
				2013y / January / 21d,

				2017y / January / 20d,

				2021y / January / 20d,

				2025y / January / 20d,

				2029y / January / 19d,
			};

			return schedule{
				days_period{ Epoch.get_from(), 2030y / LastDayOfDecember },
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
			const auto Juneteenth = named_holiday{ June / 19d }; // Emancipation Day
			const auto IndependenceDay = named_holiday{ July / 4d };
			const auto LaborDay = weekday_indexed_holiday{ September / Monday[1] };
			const auto ColumbusDay = weekday_indexed_holiday{ October / Monday[2] };
			const auto VeteransDay = named_holiday{ November / 11d };
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

		auto _make_Washington_DC_Federal_calendar() -> calendar
		{
			const auto known_part = _Washington_DC_Federal_schedule();

			const auto generated_part_from = known_part.get_period().get_until().year() + years{ 1 };
			const auto generated_part_until = Epoch.get_until().year();

			const auto InaugurationDay = named_holiday{ January / 20d };

			const auto rules = annual_holiday_storage{
				&InaugurationDay
			};

			const auto generated_part = make_holiday_schedule(
				years_period{ generated_part_from, generated_part_until },
				rules // not right as this should be every 4th year only
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
			}; // add the USA part
		}



		auto make_USA_Federal_calendar() -> const calendar&
		{
			static const auto s = _make_USA_Federal_calendar();
			return s;
		}

		auto make_Washington_DC_Federal_calendar() -> const calendar&
		{
			static const auto s = _make_Washington_DC_Federal_calendar();
			return s;
		}

	}

}
