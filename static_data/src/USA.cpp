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

#include <period.h>
#include <schedule.h>
#include <calendar.h>
#include <annual_holiday_interface.h>
#include <annual_holidays.h>
#include <weekend.h>
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

		static auto _USA_Federal_schedule() -> schedule // or should it be a "proper" function (without _)?
		{
			auto holidays = schedule::dates{
				2010y / December / 31d, // New Year's Day // we actually do not keep it in the 2011 calendar
				2011y / January / 17d, // Birthday of Martin Luther King, Jr.
				2011y / February / 21d, // Washington’s Birthday
				2011y / May / 30d, // Memorial Day
				2011y / July / 4d, // Independence Day
				2011y / September / 5d, // Labor Day
				2011y / October / 10d, // Columbus Day
				2011y / November / 11d, // Veterans Day
				2011y / November / 24d, // Thanksgiving Day
				2011y / December / 26d, // Christmas Day

				2012y / January / 2d, // New Year's Day
				2012y / January / 16d, // Birthday of Martin Luther King, Jr.
				2012y / February / 20d, // Washington’s Birthday
				2012y / May / 28d, // Memorial Day
				2012y / July / 4d, // Independence Day
				2012y / September / 3d, // Labor Day
				2012y / October / 8d, // Columbus Day
				2012y / November / 12d, // Veterans Day
				2012y / November / 22d, // Thanksgiving Day
				2012y / December / 25d, // Christmas Day

				2013y / January / 1d, // New Year's Day
				2013y / January / 21d, // Birthday of Martin Luther King, Jr.
				2013y / February / 18d, // Washington’s Birthday
				2013y / May / 27d, // Memorial Day
				2013y / July / 4d, // Independence Day
				2013y / September / 2d, // Labor Day
				2013y / October / 14d, // Columbus Day
				2013y / November / 11d, // Veterans Day
				2013y / November / 28d, // Thanksgiving Day
				2013y / December / 25d, // Christmas Day

				2014y / January / 1d, // New Year's Day
				2014y / January / 20d, // Birthday of Martin Luther King, Jr.
				2014y / February / 17d, // Washington’s Birthday
				2014y / May / 26d, // Memorial Day
				2014y / July / 4d, // Independence Day
				2014y / September / 1d, // Labor Day
				2014y / October / 13d, // Columbus Day
				2014y / November / 11d, // Veterans Day
				2014y / November / 27d, // Thanksgiving Day
				2014y / December / 25d, // Christmas Day

				2015y / January / 1d, // New Year's Day
				2015y / January / 19d, // Birthday of Martin Luther King, Jr.
				2015y / February / 16d, // Washington’s Birthday
				2015y / May / 25d, // Memorial Day
				2015y / July / 3d, // Independence Day
				2015y / September / 7d, // Labor Day
				2015y / October / 12d, // Columbus Day
				2015y / November / 11d, // Veterans Day
				2015y / November / 26d, // Thanksgiving Day
				2015y / December / 25d, // Christmas Day

				2016y / January / 1d, // New Year's Day
				2016y / January / 18d, // Birthday of Martin Luther King, Jr.
				2016y / February / 15d, // Washington’s Birthday
				2016y / May / 30d, // Memorial Day
				2016y / July / 4d, // Independence Day
				2016y / September / 5d, // Labor Day
				2016y / October / 10d, // Columbus Day
				2016y / November / 11d, // Veterans Day
				2016y / November / 24d, // Thanksgiving Day
				2016y / December / 26d, // Christmas Day

				2017y / January / 2d, // New Year's Day
				2017y / January / 16d, // Birthday of Martin Luther King, Jr.
				2017y / February / 20d, // Washington’s Birthday
				2017y / May / 29d, // Memorial Day
				2017y / July / 4d, // Independence Day
				2017y / September / 4d, // Labor Day
				2017y / October / 9d, // Columbus Day
				2017y / November / 10d, // Veterans Day
				2017y / November / 23d, // Thanksgiving Day
				2017y / December / 25d, // Christmas Day

				2018y / January / 1d, // New Year's Day
				2018y / January / 15d, // Birthday of Martin Luther King, Jr.
				2018y / February / 19d, // Washington’s Birthday
				2018y / May / 28d, // Memorial Day
				2018y / July / 4d, // Independence Day
				2018y / September / 3d, // Labor Day
				2018y / October / 8d, // Columbus Day
				2018y / November / 12d, // Veterans Day
				2018y / November / 22d, // Thanksgiving Day
				2018y / December / 25d, // Christmas Day

				2019y / January / 1d, // New Year's Day
				2019y / January / 21d, // Birthday of Martin Luther King, Jr.
				2019y / February / 18d, // Washington’s Birthday
				2019y / May / 27d, // Memorial Day
				2019y / July / 4d, // Independence Day
				2019y / September / 2d, // Labor Day
				2019y / October / 14d, // Columbus Day
				2019y / November / 11d, // Veterans Day
				2019y / November / 28d, // Thanksgiving Day
				2019y / December / 25d, // Christmas Day

				2020y / January / 1d, // New Year's Day
				2020y / January / 20d, // Birthday of Martin Luther King, Jr.
				2020y / February / 17d, // Washington’s Birthday
				2020y / May / 25d, // Memorial Day
				2020y / July / 3d, // Independence Day
				2020y / September / 7d, // Labor Day
				2020y / October / 12d, // Columbus Day
				2020y / November / 11d, // Veterans Day
				2020y / November / 26d, // Thanksgiving Day
				2020y / December / 25d, // Christmas Day

				2021y / January / 1d, // New Year's Day
				2021y / January / 18d, // Birthday of Martin Luther King, Jr.
				2021y / February / 15d, // Washington’s Birthday
				2021y / May / 31d, // Memorial Day
				2021y / June / 18d, // Juneteenth National Independence Day
				2021y / July / 5d, // Independence Day
				2021y / September / 6d, // Labor Day
				2021y / October / 11d, // Columbus Day
				2021y / November / 11d, // Veterans Day
				2021y / November / 25d, // Thanksgiving Day
				2021y / December / 24d, // Christmas Day

				2021y / December / 31d, // New Year's Day
				2022y / January / 17d, // Birthday of Martin Luther King, Jr.
				2022y / February / 21d, // Washington’s Birthday
				2022y / May / 30d, // Memorial Day
				2022y / June / 20d, // Juneteenth National Independence Day
				2022y / July / 4d, // Independence Day
				2022y / September / 5d, // Labor Day
				2022y / October / 10d, // Columbus Day
				2022y / November / 11d, // Veterans Day
				2022y / November / 24d, // Thanksgiving Day
				2022y / December / 26d, // Christmas Day

				2023y / January / 2d, // New Year's Day
				2023y / January / 16d, // Birthday of Martin Luther King, Jr.
				2023y / February / 20d, // Washington’s Birthday
				2023y / May / 29d, // Memorial Day
				2023y / June / 19d, // Juneteenth National Independence Day
				2023y / July / 4d, // Independence Day
				2023y / September / 4d, // Labor Day
				2023y / October / 9d, // Columbus Day
				2023y / November / 10d, // Veterans Day
				2023y / November / 23d, // Thanksgiving Day
				2023y / December / 25d, // Christmas Day

				2024y / January / 1d, // New Year's Day
				2024y / January / 15d, // Birthday of Martin Luther King, Jr.
				2024y / February / 19d, // Washington’s Birthday
				2024y / May / 27d, // Memorial Day
				2024y / June / 19d, // Juneteenth National Independence Day
				2024y / July / 4d, // Independence Day
				2024y / September / 2d, // Labor Day
				2024y / October / 14d, // Columbus Day
				2024y / November / 11d, // Veterans Day
				2024y / November / 28d, // Thanksgiving Day
				2024y / December / 25d, // Christmas Day

				2025y / January / 1d, // New Year's Day
				2025y / January / 20d, // Birthday of Martin Luther King, Jr.
				2025y / February / 17d, // Washington’s Birthday
				2025y / May / 26d, // Memorial Day
				2025y / June / 19d, // Juneteenth National Independence Day
				2025y / July / 4d, // Independence Day
				2025y / September / 1d, // Labor Day
				2025y / October / 13d, // Columbus Day
				2025y / November / 11d, // Veterans Day
				2025y / November / 27d, // Thanksgiving Day
				2025y / December / 25d, // Christmas Day

				2026y / January / 1d, // New Year's Day
				2026y / January / 19d, // Birthday of Martin Luther King, Jr.
				2026y / February / 16d, // Washington’s Birthday
				2026y / May / 25d, // Memorial Day
				2026y / June / 19d, // Juneteenth National Independence Day
				2026y / July / 3d, // Independence Day
				2026y / September / 7d, // Labor Day
				2026y / October / 12d, // Columbus Day
				2026y / November / 11d, // Veterans Day
				2026y / November / 26d, // Thanksgiving Day
				2026y / December / 25d, // Christmas Day

				2027y / January / 1d, // New Year's Day
				2027y / January / 18d, // Birthday of Martin Luther King, Jr.
				2027y / February / 15d, // Washington’s Birthday
				2027y / May / 31d, // Memorial Day
				2027y / June / 18d, // Juneteenth National Independence Day
				2027y / July / 5d, // Independence Day
				2027y / September / 6d, // Labor Day
				2027y / October / 11d, // Columbus Day
				2027y / November / 11d, // Veterans Day
				2027y / November / 25d, // Thanksgiving Day
				2027y / December / 24d, // Christmas Day

				2027y / December / 31d, // New Year's Day
				2028y / January / 17d, // Birthday of Martin Luther King, Jr.
				2028y / February / 21d, // Washington’s Birthday
				2028y / May / 29d, // Memorial Day
				2028y / June / 19d, // Juneteenth National Independence Day
				2028y / July / 4d, // Independence Day
				2028y / September / 4d, // Labor Day
				2028y / October / 9d, // Columbus Day
				2028y / November / 10d, // Veterans Day
				2028y / November / 23d, // Thanksgiving Day
				2028y / December / 25d, // Christmas Day

				2029y / January / 1d, // New Year's Day
				2029y / January / 15d, // Birthday of Martin Luther King, Jr.
				2029y / February / 19d, // Washington’s Birthday
				2029y / May / 28d, // Memorial Day
				2029y / June / 19d, // Juneteenth National Independence Day
				2029y / July / 4d, // Independence Day
				2029y / September / 3d, // Labor Day
				2029y / October / 8d, // Columbus Day
				2029y / November / 12d, // Veterans Day
				2029y / November / 22d, // Thanksgiving Day
				2029y / December / 25d, // Christmas Day

				2030y / January / 1d, // New Year's Day
				2030y / January / 21d, // Birthday of Martin Luther King, Jr.
				2030y / February / 18d, // Washington’s Birthday
				2030y / May / 27d, // Memorial Day
				2030y / June / 19d, // Juneteenth National Independence Day
				2030y / July / 4d, // Independence Day
				2030y / September / 2d, // Labor Day
				2030y / October / 14d, // Columbus Day
				2030y / November / 11d, // Veterans Day
				2030y / November / 28d, // Thanksgiving Day
				2030y / December / 25d, // Christmas Day
			};

			// from the same documentation:
			// 
			// *This holiday is designated as "Washington’s Birthday" in section 6103(a)of title 5 of the United States Code,
			// which is the law that specifies holidays for Federal employees.Though other institutions such as state and
			// local governments and private businesses may use other names, it is our policy to always refer to holidays
			// by the names designated in the law.
			//
			// ** If a holiday falls on a Saturday, for most Federal employees, the preceding Friday will be treated as a holiday
			// for pay and leave purposes. (See 5 U.S.C. 6103(b).) If a holiday falls on a Sunday, for most Federal employees,
			// the following Monday will be treated as a holiday for pay and leave purposes.
			// (See Section 3(a)of Executive Order 11582, February 11, 1971.)
			// See also our Federal Holidays – "In Lieu Of" Determination Fact Sheet at
			// https ://www.opm.gov/policy-data-oversight/pay-leave/work-schedules/fact-sheets/Federal-Holidays-In-Lieu-Of-Determination.

			return schedule{
				days_period{ Epoch.get_from(), 2030y / LastDayOfDecember },
				move(holidays)
			};
		}

		static auto _Washington_DC_Federal_schedule() -> schedule // or should it be a "proper" function (without _)?
		{
			auto holidays = schedule::dates{
				2013y / January / 21d,

				2017y / January / 20d,

				2021y / January / 20d,

				2025y / January / 20d,

				2029y / January / 19d,
			};

			// from the same documentation:
			//
			// *This holiday is designated as "Inauguration Day" in section 6103(c) of title 5 of the United States Code,
			// which is the law that specifies holidays for Federal employees.
			// Federal employees in the Washington, DC, area are entitled to a holiday on the day a President is inaugurated
			// on January 20th for each fourth year after 1965.

			return schedule{
				days_period{ Epoch.get_from(), 2030y / LastDayOfDecember },
				move(holidays)
			};
		}

		static auto _make_USA_Federal_calendar() -> calendar
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

		// should it move to the main library (in a more generic form)?
		static auto _make_Washington_DC_Federal_holiday_schedule( // Victoria Day sits in it own file ...
			const util::years_period& p,
			const annual_holiday_storage& rules
		) noexcept -> schedule
		{
			auto hols = schedule::dates{};

			for (auto y = 2033y; y <= p.get_until(); y += years{ 4 })
				for (const auto& rule : rules)
					hols.insert(rule->make_holiday(y));

			return schedule{
				util::days_period{
					p.get_from() / FirstDayOfJanuary,
					p.get_until() / LastDayOfDecember
				},
				move(hols)
			};
		}

		static auto _make_Washington_DC_Federal_calendar() -> calendar
		{
			const auto known_part = _Washington_DC_Federal_schedule();

			const auto generated_part_from = known_part.get_period().get_until().year() + years{ 1 };
			const auto generated_part_until = Epoch.get_until().year();

			const auto InaugurationDay = named_holiday{ January / 20d };

			const auto rules = annual_holiday_storage{
				&InaugurationDay
			};

			const auto generated_part = _make_Washington_DC_Federal_holiday_schedule(
				years_period{ generated_part_from, generated_part_until },
				rules
			);

			// setup a calendar for the generated part only (to do substitution for the generated dates)
			auto cal = calendar{
				SaturdaySundayWeekend,
				generated_part
			};
			cal.substitute(Nearest);

			return 
				_make_USA_Federal_calendar() |
				calendar{ SaturdaySundayWeekend, known_part + cal.get_schedule() };
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
