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

		static auto _England_schedule() -> schedule // or should it be a "proper" function (without _)?
		{
			auto holidays = schedule::dates{ // should we include day of the week into comments?
				2012y / January / 2d, // New Year’s Day (substitute day)
				2012y / April / 6d, // Good Friday
				2012y / April / 9d, // Easter Monday
				2012y / May / 7d, // Early May bank holiday
				2012y / June / 4d, // Spring bank holiday (substitute day)
				2012y / June / 5d, // Queen's Diamond Jubilee (extra bank holiday)
				2012y / August / 27d, // Summer bank holiday
				2012y / December / 25d, // Christmas Day
				2012y / December / 26d, // Boxing Day

				2013y / January / 1d, // New Year’s Day
				2013y / March / 29d, // Good Friday
				2013y / April / 1d, // Easter Monday
				2013y / May / 6d, // Early May bank holiday
				2013y / May / 27d, // Spring bank holiday
				2013y / August / 26d, // Summer bank holiday
				2013y / December / 25d, // Christmas Day
				2013y / December / 26d, // Boxing Day

				2014y / January / 1d, // New Year’s Day
				2014y / April / 18d, // Good Friday
				2014y / April / 21d, // Easter Monday
				2014y / May / 5d, // Early May bank holiday
				2014y / May / 26d, // Spring bank holiday
				2014y / August / 25d, // Summer bank holiday
				2014y / December / 25d, // Christmas Day
				2014y / December / 26d, // Boxing Day

				2015y / January / 1d, // New Year’s Day
				2015y / April / 3d, // Good Friday
				2015y / April / 6d, // Easter Monday
				2015y / May / 4d, // Early May bank holiday
				2015y / May / 25d, // Spring bank holiday
				2015y / August / 31d, // Summer bank holiday
				2015y / December / 25d, // Christmas Day
				2015y / December / 28d, // Boxing Day (substitute day)

				2016y / January / 1d, // New Year’s Day
				2016y / March / 25d, // Good Friday
				2016y / March / 28d, // Easter Monday
				2016y / May / 2d, // Early May bank holiday
				2016y / May / 30d, // Spring bank holiday
				2016y / August / 29d, // Summer bank holiday
				2016y / December / 26d, // Boxing Day
				2016y / December / 27d, // Christmas Day (substitute day)

				2017y / January / 2d, // New Year’s Day (substitute day)
				2017y / April / 14d, // Good Friday
				2017y / April / 17d, // Easter Monday
				2017y / May / 1d, // Early May bank holiday
				2017y / May / 29d, // Spring bank holiday
				2017y / August / 28d, // Summer bank holiday
				2017y / December / 25d, // Christmas Day
				2017y / December / 26d, // Boxing Day

				2018y / January / 1d, // New Year’s Day
				2018y / March / 30d, // Good Friday
				2018y / April / 2d, // Easter Monday
				2018y / May / 7d, // Early May bank holiday
				2018y / May / 28d, // Spring bank holiday
				2018y / August / 27d, // Summer bank holiday
				2018y / December / 25d, // Christmas Day
				2018y / December / 26d, // Boxing Day

				2019y / January / 1d, // New Year’s Day
				2019y / April / 19d, // Good Friday
				2019y / April / 22d, // Easter Monday
				2019y / May / 6d, // Early May bank holiday
				2019y / May / 27d, // Spring bank holiday
				2019y / August / 26d, // Summer bank holiday
				2019y / December / 25d, // Christmas Day
				2019y / December / 26d, // Boxing Day

				2020y / January / 1d, // New Year’s Day
				2020y / April / 10d, // Good Friday
				2020y / April / 13d, // Easter Monday
				2020y / May / 8d, // Early May bank holiday (VE day)
				2020y / May / 25d, // Spring bank holiday
				2020y / August / 31d, // Summer bank holiday
				2020y / December / 25d, // Christmas Day
				2020y / December / 28d, // Boxing Day (substitute day)

				2021y / January / 1d, // New Year’s Day
				2021y / April / 2d, // Good Friday
				2021y / April / 5d, // Easter Monday
				2021y / May / 3d, // Early May bank holiday
				2021y / May / 31d, // Spring bank holiday
				2021y / August / 30d, // Summer bank holiday
				2021y / December / 27d, // Christmas Day (substitute day)
				2021y / December / 28d, // Boxing Day (substitute day)

				2022y / January / 3d, // New Year’s Day (substitute day)
				2022y / April / 15d, // Good Friday
				2022y / April / 18d, // Easter Monday
				2022y / May / 2d, // Early May bank holiday
				2022y / June / 2d, // Spring bank holiday
				2022y / June / 3d, // Platinum Jubilee bank holiday
				2022y / August / 29d, // Summer bank holiday
				2022y / September / 19d, // Bank Holiday for the State Funeral of Queen Elizabeth II
				2022y / December / 26d, // Boxing Day
				2022y / December / 27d, // Christmas Day (substitute day)

				2023y / January / 2d, // New Year’s Day (substitute day)
				2023y / April / 7d, // Good Friday
				2023y / April / 10d, // Easter Monday
				2023y / May / 1d, // Early May bank holiday
				2023y / May / 8d, // Bank holiday for the coronation of King Charles III
				2023y / May / 29d, // Spring bank holiday
				2023y / August / 28d, // Summer bank holiday
				2023y / December / 25d, // Christmas Day
				2023y / December / 26d, // Boxing Day

				2024y / January / 1d, // New Year’s Day
				2024y / March / 29d, // Good Friday
				2024y / April / 1d, // Easter Monday
				2024y / May / 6d, // Early May bank holiday
				2024y / May / 27d, // Spring bank holiday
				2024y / August / 26d, // Summer bank holiday
				2024y / December / 25d, // Christmas Day
				2024y / December / 26d, // Boxing Day

				2025y / January / 1d, // New Year’s Day
				2025y / April / 18d, // Good Friday
				2025y / April / 21d, // Easter Monday
				2025y / May / 5d, // Early May bank holiday
				2025y / May / 26d, // Spring bank holiday
				2025y / August / 25d, // Summer bank holiday
				2025y / December / 25d, // Christmas Day
				2025y / December / 26d, // Boxing Day

				2026y / January / 1d, // New Year’s Day
				2026y / April / 3d, // Good Friday
				2026y / April / 6d, // Easter Monday
				2026y / May / 4d, // Early May bank holiday
				2026y / May / 25d, // Spring bank holiday
				2026y / August / 31d, // Summer bank holiday
				2026y / December / 25d, // Christmas Day
				2026y / December / 28d, // Boxing Day (substitute day)

				2027y / January / 1d, // New Year’s Day
				2027y / March / 26d, // Good Friday
				2027y / March / 29d, // Easter Monday
				2027y / May / 3d, // Early May bank holiday
				2027y / May / 31d, // Spring bank holiday
				2027y / August / 30d, // Summer bank holiday
				2027y / December / 27d, // Christmas Day (substitute day)
				2027y / December / 28d, // Boxing Day (substitute day)

				2028y / January / 3d, // New Year’s Day (substitute day)
				2028y / April / 14d, // Good Friday
				2028y / April / 17d, // Easter Monday
				2028y / May / 1d, // Early May bank holiday
				2028y / May / 29d, // Spring bank holiday
				2028y / August / 28d, // Summer bank holiday
				2028y / December / 25d, // Christmas Day
				2028y / December / 26d, // Boxing Day
			};

			return schedule{
				days_period{ Epoch.get_from(), 2028y / LastDayOfDecember },
				move(holidays)
			};
		}

		static auto _make_England_calendar() -> calendar
		{
			const auto known_part = _England_schedule();

			const auto generated_part_from = known_part.get_period().get_until().year() + years{ 1 };
			const auto generated_part_until = Epoch.get_until().year();

			const auto EarlyMayBankHoliday = weekday_indexed_holiday{ May / Monday[1] };
			const auto SpringBankHoliday = weekday_last_holiday{ May / Monday[last] };
			const auto SummerBankHoliday = weekday_last_holiday{ August / Monday[last] };

			const auto rules = annual_holiday_storage{
				&NewYearsDay,
				&GoodFriday,
				&EasterMonday,
				&EarlyMayBankHoliday,
				&SpringBankHoliday,
				&SummerBankHoliday,
				&ChristmasDay,
				&BoxingDay
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
			cal.substitute(Following);

			return calendar{
				SaturdaySundayWeekend,
				known_part + cal.get_schedule()
			};
		}



		static auto _Scotland_schedule() -> schedule
		{
			auto holidays = schedule::dates{
				2012y / January / 2d, // 2nd January
				2012y / January / 3d, // New Year’s Day (substitute day)
				2012y / April / 6d, // Good Friday
				2012y / May / 7d, // Early May bank holiday
				2012y / June / 4d, // Spring bank holiday (substitute day)
				2012y / June / 5d, // Queen's Diamond Jubilee (extra bank holiday)
				2012y / August / 6d, // Summer bank holiday
				2012y / November / 30d, // St Andrew’s Day
				2012y / December / 25d, // Christmas Day
				2012y / December / 26d, // Boxing Day

				2013y / January / 1d, // New Year’s Day
				2013y / January / 2d, // 2nd January
				2013y / March / 29d, // Good Friday
				2013y / May / 6d, // Early May bank holiday
				2013y / May / 27d, // Spring bank holiday
				2013y / August / 5d, // Summer bank holiday
				2013y / December / 2d, // St Andrew’s Day (substitute day)
				2013y / December / 25d, // Christmas Day
				2013y / December / 26d, // Boxing Day

				2014y / January / 1d, // New Year’s Day
				2014y / January / 2d, // 2nd January
				2014y / April / 18d, // Good Friday
				2014y / May / 5d, // Early May bank holiday
				2014y / May / 26d, // Spring bank holiday
				2014y / August / 4d, // Summer bank holiday
				2014y / December / 1d, // St Andrew’s Day (substitute day)
				2014y / December / 25d, // Christmas Day
				2014y / December / 26d, // Boxing Day

				2015y / January / 1d, // New Year’s Day
				2015y / January / 2d, // 2nd January
				2015y / April / 3d, // Good Friday
				2015y / May / 4d, // Early May bank holiday
				2015y / May / 25d, // Spring bank holiday
				2015y / August / 3d, // Summer bank holiday
				2015y / November / 30d, // St Andrew’s Day
				2015y / December / 25d, // Christmas Day
				2015y / December / 28d, // Boxing Day (substitute day)

				2016y / January / 1d, // New Year’s Day
				2016y / January / 4d, // 2nd January (subsitute day)
				2016y / March / 25d, // Good Friday
				2016y / May / 2d, // Early May bank holiday
				2016y / May / 30d, // Spring bank holiday
				2016y / August / 1d, // Summer bank holiday
				2016y / November / 30d, // St Andrew’s Day
				2016y / December / 26d, // Boxing Day
				2016y / December / 27d, // Christmas Day (substitute day)

				2017y / January / 2d, // 2nd January
				2017y / January / 3d, // New Year’s Day (subsitute day)
				2017y / April / 14d, // Good Friday
				2017y / May / 1d, // Early May bank holiday
				2017y / May / 29d, // Spring bank holiday
				2017y / August / 7d, // Summer bank holiday
				2017y / November / 30d, // St Andrew’s Day
				2017y / December / 25d, // Christmas Day
				2017y / December / 26d, // Boxing Day

				2018y / January / 1d, // New Year’s Day
				2018y / January / 2d, // 2nd January
				2018y / March / 30d, // Good Friday
				2018y / May / 7d, // Early May bank holiday
				2018y / May / 28d, // Spring bank holiday
				2018y / August / 6d, // Summer bank holiday
				2018y / November / 30d, // St Andrew’s Day
				2018y / December / 25d, // Christmas Day
				2018y / December / 26d, // Boxing Day

				2019y / January / 1d, // New Year’s Day
				2019y / January / 2d, // 2nd January
				2019y / April / 19d, // Good Friday
				2019y / May / 6d, // Early May bank holiday
				2019y / May / 27d, // Spring bank holiday
				2019y / August / 5d, // Summer bank holiday
				2019y / December / 2d, // St Andrew’s Day (substitute day)
				2019y / December / 25d, // Christmas Day
				2019y / December / 26d, // Boxing Day

				2020y / January / 1d, // New Year’s Day
				2020y / January / 2d, // 2nd January
				2020y / April / 10d, // Good Friday
				2020y / May / 8d, // Early May bank holiday (VE day)
				2020y / May / 25d, // Spring bank holiday
				2020y / August / 3d, // Summer bank holiday
				2020y / November / 30d, // St Andrew’s Day
				2020y / December / 25d, // Christmas Day
				2020y / December / 28d, // Boxing Day (substitute day)

				2021y / January / 1d, // New Year’s Day
				2021y / January / 4d, // 2nd January (substitute day)
				2021y / April / 2d, // Good Friday
				2021y / May / 3d, // Early May bank holiday
				2021y / May / 31d, // Spring bank holiday
				2021y / August / 2d, // Summer bank holiday
				2021y / November / 30d, // St Andrew’s Day
				2021y / December / 27d, // Christmas Day (substitute day)
				2021y / December / 28d, // Boxing Day (substitute day)

				2022y / January / 3d, // New Year’s Day (substitute day)
				2022y / January / 4d, // 2nd January (substitute day)
				2022y / April / 15d, // Good Friday
				2022y / May / 2d, // Early May bank holiday
				2022y / June / 2d, // Spring bank holiday
				2022y / June / 3d, // Platinum Jubilee bank holiday
				2022y / August / 1d, // Summer bank holiday
				2022y / September / 19d, // Bank Holiday for the State Funeral of Queen Elizabeth II
				2022y / November / 30d, // St Andrew’s Day
				2022y / December / 26d, // Boxing Day
				2022y / December / 27d, // Christmas Day (substitute day)

				2023y / January / 2d, // New Year’s Day (substitute day)
				2023y / January / 3d, // 2nd January (substitute day)
				2023y / April / 7d, // Good Friday
				2023y / May / 1d, // Early May bank holiday
				2023y / May / 8d, // Bank holiday for the coronation of King Charles III
				2023y / May / 29d, // Spring bank holiday
				2023y / August / 7d, // Summer bank holiday
				2023y / November / 30d, // St Andrew’s Day
				2023y / December / 25d, // Christmas Day
				2023y / December / 26d, // Boxing Day

				2024y / January / 1d, // New Year’s Day
				2024y / January / 2d, // 2nd January
				2024y / March / 29d, // Good Friday
				2024y / May / 6d, // Early May bank holiday
				2024y / May / 27d, // Spring bank holiday
				2024y / August / 5d, // Summer bank holiday
				2024y / December / 2d, // St Andrew’s Day (substitute day)
				2024y / December / 25d, // Christmas Day
				2024y / December / 26d, // Boxing Day

				2025y / January / 1d, // New Year’s Day
				2025y / January / 2d, // 2nd January
				2025y / April / 18d, // Good Friday
				2025y / May / 5d, // Early May bank holiday
				2025y / May / 26d, // Spring bank holiday
				2025y / August / 4d, // Summer bank holiday
				2025y / December / 1d, // St Andrew’s Day (substitute day)
				2025y / December / 25d, // Christmas Day
				2025y / December / 26d, // Boxing Day

				2026y / January / 1d, // New Year’s Day
				2026y / January / 2d, // 2nd January
				2026y / April / 3d, // Good Friday
				2026y / May / 4d, // Early May bank holiday
				2026y / May / 25d, // Spring bank holiday
				2026y / August / 3d, // Summer bank holiday
				2026y / November / 30d, // St Andrew’s Day
				2026y / December / 25d, // Christmas Day
				2026y / December / 28d, // Boxing Day (substitute day)

				2027y / January / 1d, // New Year’s Day
				2027y / January / 4d, // 2nd January (substitute day)
				2027y / March / 26d, // Good Friday
				2027y / May / 3d, // Early May bank holiday
				2027y / May / 31d, // Spring bank holiday
				2027y / August / 2d, // Summer bank holiday
				2027y / November / 30d, // St Andrew’s Day
				2027y / December / 27d, // Christmas Day (substitute day)
				2027y / December / 28d, // Boxing Day (substitute day)

				2028y / January / 3d, // New Year’s Day (substitute day)
				2028y / January / 4d, // 2nd January (substitute day)
				2028y / April / 14d, // Good Friday
				2028y / May / 1d, // Early May bank holiday
				2028y / May / 29d, // Spring bank holiday
				2028y / August / 7d, // Summer bank holiday
				2028y / November / 30d, // St Andrew’s Day
				2028y / December / 25d, // Christmas Day
				2028y / December / 26d, // Boxing Day
			};

			return schedule{
				days_period{ Epoch.get_from(), 2028y / LastDayOfDecember },
				move(holidays)
			};
		}

		static auto _make_Scotland_calendar() -> calendar
		{
			const auto known_part = _Scotland_schedule();

			const auto generated_part_from = known_part.get_period().get_until().year() + years{ 1 };
			const auto generated_part_until = Epoch.get_until().year();

			const auto SecondJanuary = offset_holiday{ &NewYearsDay, days{ 1 } };
			const auto EarlyMayBankHoliday = weekday_indexed_holiday{ May / Monday[1] };
			const auto SpringBankHoliday = weekday_last_holiday{ May / Monday[last] };
			const auto SummerBankHoliday = weekday_indexed_holiday{ August / Monday[1] };
			const auto StAndrewsDay = named_holiday{ November / 30d };

			const auto rules = annual_holiday_storage{
				&NewYearsDay,
				&SecondJanuary,
				&GoodFriday,
				&EarlyMayBankHoliday,
				&SpringBankHoliday,
				&SummerBankHoliday,
				&StAndrewsDay,
				&ChristmasDay,
				&BoxingDay
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
			cal.substitute(Following);

			return calendar{
				SaturdaySundayWeekend,
				known_part + cal.get_schedule()
			};
		}



		static auto _Northern_Ireland_schedule() -> schedule
		{
			auto holidays = schedule::dates{
				2012y / January / 2d, // New Year’s Day (substitute day)
				2012y / March / 19d, // St Patrick’s Day (substitute day)
				2012y / April / 6d, // Good Friday
				2012y / April / 9d, // Easter Monday
				2012y / May / 7d, // Early May bank holiday
				2012y / June / 4d, // Spring bank holiday (substitute day)
				2012y / June / 5d, // Queen's Diamond Jubilee (extra bank holiday)
				2012y / July / 12d, // Battle of the Boyne (Orangemen’s Day)
				2012y / August / 27d, // Summer bank holiday
				2012y / December / 25d, // Christmas Day
				2012y / December / 26d, // Boxing Day

				2013y / January / 1d, // New Year’s Day
				2013y / March / 18d, // St Patrick’s Day (substitute day)
				2013y / March / 29d, // Good Friday
				2013y / April / 1d, // Easter Monday
				2013y / May / 6d, // Early May bank holiday
				2013y / May / 27d, // Spring bank holiday
				2013y / July / 12d, // Battle of the Boyne (Orangemen’s Day)
				2013y / August / 26d, // Summer bank holiday
				2013y / December / 25d, // Christmas Day
				2013y / December / 26d, // Boxing Day

				2014y / January / 1d, // New Year’s Day
				2014y / March / 17d, // St Patrick’s Day
				2014y / April / 18d, // Good Friday
				2014y / April / 21d, // Easter Monday
				2014y / May / 5d, // Early May bank holiday
				2014y / May / 26d, // Spring bank holiday
				2014y / July / 14d, // Battle of the Boyne (Orangemen’s Day) (substitute day)
				2014y / August / 25d, // Summer bank holiday
				2014y / December / 25d, // Christmas Day
				2014y / December / 26d, // Boxing Day

				2015y / January / 1d, // New Year’s Day
				2015y / March / 17d, // St Patrick’s Day
				2015y / April / 3d, // Good Friday
				2015y / April / 6d, // Easter Monday
				2015y / May / 4d, // Early May bank holiday
				2015y / May / 25d, // Spring bank holiday
				2015y / July / 13d, // Battle of the Boyne (Orangemen’s Day) (substitute day)
				2015y / August / 31d, // Summer bank holiday
				2015y / December / 25d, // Christmas Day
				2015y / December / 28d, // Boxing Day (substitite day)

				2016y / January / 1d, // New Year’s Day
				2016y / March / 17d, // St Patrick’s Day
				2016y / March / 25d, // Good Friday
				2016y / March / 28d, // Easter Monday
				2016y / May / 2d, // Early May bank holiday
				2016y / May / 30d, // Spring bank holiday
				2016y / July / 12d, // Battle of the Boyne (Orangemen’s Day)
				2016y / August / 29d, // Summer bank holiday
				2016y / December / 26d, // Boxing Day
				2016y / December / 27d, // Christmas Day (substitute day)

				2017y / January / 2d, // New Year’s Day (substitute day)
				2017y / March / 17d, // St Patrick’s Day
				2017y / April / 14d, // Good Friday
				2017y / April / 17d, // Easter Monday
				2017y / May / 1d, // Early May bank holiday
				2017y / May / 29d, // Spring bank holiday
				2017y / July / 12d, // Battle of the Boyne (Orangemen’s Day)
				2017y / August / 28d, // Summer bank holiday
				2017y / December / 25d, // Christmas Day
				2017y / December / 26d, // Boxing Day

				2018y / January / 1d, // New Year’s Day
				2018y / March / 19d, // St Patrick’s Day (substitute day)
				2018y / March / 30d, // Good Friday
				2018y / April / 2d, // Easter Monday
				2018y / May / 7d, // Early May bank holiday
				2018y / May / 28d, // Spring bank holiday
				2018y / July / 12d, // Battle of the Boyne (Orangemen’s Day)
				2018y / August / 27d, // Summer bank holiday
				2018y / December / 25d, // Christmas Day
				2018y / December / 26d, // Boxing Day

				2019y / January / 1d, // New Year’s Day
				2019y / March / 18d, // St Patrick’s Day (substitute day)
				2019y / April / 19d, // Good Friday
				2019y / April / 22d, // Easter Monday
				2019y / May / 6d, // Early May bank holiday
				2019y / May / 27d, // Spring bank holiday
				2019y / July / 12d, // Battle of the Boyne (Orangemen’s Day)
				2019y / August / 26d, // Summer bank holiday
				2019y / December / 25d, // Christmas Day
				2019y / December / 26d, // Boxing Day

				2020y / January / 1d, // New Year’s Day
				2020y / March / 17d, // St Patrick’s Day
				2020y / April / 10d, // Good Friday
				2020y / April / 13d, // Easter Monday
				2020y / May / 8d, // Early May bank holiday (VE day)
				2020y / May / 25d, // Spring bank holiday
				2020y / July / 13d, // Battle of the Boyne (Orangemen’s Day) (substitute day)
				2020y / August / 31d, // Summer bank holiday
				2020y / December / 25d, // Christmas Day
				2020y / December / 28d, // Boxing Day (substitute day)

				2021y / January / 1d, // New Year’s Day
				2021y / March / 17d, // St Patrick’s Day
				2021y / April / 2d, // Good Friday
				2021y / April / 5d, // Easter Monday
				2021y / May / 3d, // Early May bank holiday
				2021y / May / 31d, // Spring bank holiday
				2021y / July / 12d, // Battle of the Boyne (Orangemen’s Day)
				2021y / August / 30d, // Summer bank holiday
				2021y / December / 27d, // Christmas Day (substitute day)
				2021y / December / 28d, // Boxing Day (substitute day)

				2022y / January / 3d, // New Year’s Day (substitute day)
				2022y / March / 17d, // St Patrick’s Day
				2022y / April / 15d, // Good Friday
				2022y / April / 18d, // Easter Monday
				2022y / May / 2d, // Early May bank holiday
				2022y / June / 2d, // Spring bank holiday
				2022y / June / 3d, // Platinum Jubilee bank holiday
				2022y / July / 12d, // Battle of the Boyne (Orangemen’s Day)
				2022y / August / 29d, // Summer bank holiday
				2022y / September / 19d, // Bank Holiday for the State Funeral of Queen Elizabeth II
				2022y / December / 26d, // Boxing Day
				2022y / December / 27d, // Christmas Day (substitute day)

				2023y / January / 2d, // New Year’s Day (substitute day)
				2023y / March / 17d, // St Patrick’s Day
				2023y / April / 7d, // Good Friday
				2023y / April / 10d, // Easter Monday
				2023y / May / 1d, // Early May bank holiday
				2023y / May / 8d, // Bank holiday for the coronation of King Charles III
				2023y / May / 29d, // Spring bank holiday
				2023y / July / 12d, // Battle of the Boyne (Orangemen’s Day)
				2023y / August / 28d, // Summer bank holiday
				2023y / December / 25d, // Christmas Day
				2023y / December / 26d, // Boxing Day

				2024y / January / 1d, // New Year’s Day
				2024y / March / 18d, // St Patrick’s Day (substitute day)
				2024y / March / 29d, // Good Friday
				2024y / April / 1d, // Easter Monday
				2024y / May / 6d, // Early May bank holiday
				2024y / May / 27d, // Spring bank holiday
				2024y / July / 12d, // Battle of the Boyne (Orangemen’s Day)
				2024y / August / 26d, // Summer bank holiday
				2024y / December / 25d, // Christmas Day
				2024y / December / 26d, // Boxing Day

				2025y / January / 1d, // New Year’s Day
				2025y / March / 17d, // St Patrick’s Day
				2025y / April / 18d, // Good Friday
				2025y / April / 21d, // Easter Monday
				2025y / May / 5d, // Early May bank holiday
				2025y / May / 26d, // Spring bank holiday
				2025y / July / 14d, // Battle of the Boyne (Orangemen’s Day) (substitute day)
				2025y / August / 25d, // Summer bank holiday
				2025y / December / 25d, // Christmas Day
				2025y / December / 26d, // Boxing Day

				2026y / January / 1d, // New Year’s Day
				2026y / March / 17d, // St Patrick’s Day
				2026y / April / 3d, // Good Friday
				2026y / April / 6d, // Easter Monday
				2026y / May / 4d, // Early May bank holiday
				2026y / May / 25d, // Spring bank holiday
				2026y / July / 13d, // Battle of the Boyne (Orangemen’s Day) (substitute day)
				2026y / August / 31d, // Summer bank holiday
				2026y / December / 25d, // Christmas Day
				2026y / December / 28d, // Boxing Day (substitute day)

				2027y / January / 1d, // New Year’s Day
				2027y / March / 17d, // St Patrick’s Day
				2027y / March / 26d, // Good Friday
				2027y / March / 29d, // Easter Monday
				2027y / May / 3d, // Early May bank holiday
				2027y / May / 31d, // Spring bank holiday
				2027y / July / 12d, // Battle of the Boyne (Orangemen’s Day)
				2027y / August / 30d, // Summer bank holiday
				2027y / December / 27d, // Christmas Day (substitute day)
				2027y / December / 28d, // Boxing Day (substitute day)

				2028y / January / 3d, // New Year’s Day (substitute day)
				2028y / March / 17d, // St Patrick’s Day
				2028y / April / 14d, // Good Friday
				2028y / April / 17d, // Easter Monday
				2028y / May / 1d, // Early May bank holiday
				2028y / May / 29d, // Spring bank holiday
				2028y / July / 12d, // Battle of the Boyne (Orangemen’s Day)
				2028y / August / 28d, // Summer bank holiday
				2028y / December / 25d, // Christmas Day
				2028y / December / 26d, // Boxing Day
			};

			return schedule{
				days_period{ Epoch.get_from(), 2028y / LastDayOfDecember },
				move(holidays)
			};
		}

		static auto _make_Northern_Ireland_calendar() -> calendar
		{
			const auto known_part = _Northern_Ireland_schedule();

			const auto generated_part_from = known_part.get_period().get_until().year() + years{ 1 };
			const auto generated_part_until = Epoch.get_until().year();

			const auto StPatricsDay = named_holiday{ March / 18d };
			const auto EarlyMayBankHoliday = weekday_indexed_holiday{ May / Monday[1] };
			const auto SpringBankHoliday = weekday_last_holiday{ May / Monday[last] };
			const auto OrangemensDay = named_holiday{ July / 12d };
			const auto SummerBankHoliday = weekday_last_holiday{ August / Monday[last] };

			const auto rules = annual_holiday_storage{
				&NewYearsDay,
				&StPatricsDay,
				&GoodFriday,
				&EasterMonday,
				&EarlyMayBankHoliday,
				&SpringBankHoliday,
				&OrangemensDay,
				&SummerBankHoliday,
				&ChristmasDay,
				&BoxingDay
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
			cal.substitute(Following);

			return calendar{
				SaturdaySundayWeekend,
				known_part + cal.get_schedule()
			};
		}


		static auto _MPC_dates() -> schedule // actual MPC dates (not MPC holiday dates)
		{
			// below are confimed dates but also the latest provisional dates
			auto meeting_dates = schedule::dates{ // I think these are always Thursday's
				2012y / January / 12d,
				2012y / February / 9d,
				2012y / March / 8d,
				2012y / April / 5d,
				2012y / May / 10d,
				2012y / June / 7d,
				2012y / July / 5d,
				2012y / August / 2d,
				2012y / September / 6d,
				2012y / October / 4d,
				2012y / November / 8d,
				2012y / December / 6d,

				2013y / January / 10d,
				2013y / February / 7d,
				2013y / March / 7d,
				2013y / April / 4d,
				2013y / May / 9d,
				2013y / June / 6d,
				2013y / July / 4d,
				2013y / August / 1d,
				2013y / September / 5d,
				2013y / October / 9d,
				2013y / November / 7d,
				2013y / December / 5d,

				2014y / January / 9d,
				2014y / February / 6d,
				2014y / March / 6d,
				2014y / April / 9d,
				2014y / May / 8d,
				2014y / June / 5d,
				2014y / July / 10d,
				2014y / August / 7d,
				2014y / September / 4d,
				2014y / October / 8d,
				2014y / November / 6d,
				2014y / December / 4d,

				// From "Monetary Policy Committee dates for 2015 and provisional dates for 2016":
				// 
				// (**) Because the scheduled date for the May 2015 general election falls on a day when the MPC meeting would usually
				// take place, the meeting will be deferred by 24 hours to Thursday afternoon and Friday morning. The decision would be
				// announced at 12 noon on the Monday after the election, as previously published.
				2015y / January / 8d,
				2015y / February / 5d,
				2015y / March / 5d,
				2015y / April / 9d,
				2015y / May / 11d, // **
				2015y / June / 4d,
				2015y / July / 9d,
				2015y / August / 6d,
				2015y / September / 10d,
				2015y / October / 8d,
				2015y / November / 5d,
				2015y / December / 10d,

				// From "Monetary Policy Committee publication dates for 2016 and provisional dates for 2017":
				// 
				// Under current legislation, the MPC must meet and announce a policy decision at least once a month. Therefore,
				// as shown, the MPC has provisionally scheduled twelve meetings for both 2016 and 2017.
				// 
				// However, the Government has announced that it proposes to introduce to Parliament in this session
				// a Bank of England Bill which will include a provision to move the MPC to a schedule of eight regular meetings a year.
				// To provide scope for such a change, the MPC published last December a provisional schedule for 2016
				// in which eight of the twelve annual meetings are spaced roughly evenly through the year with the intention that,
				// if Parliament passes the proposed legislation to make the change, the MPC could drop the remaining four meetings
				// once the law has changed. Those four meetings are provisionally scheduled for January, April, July and October.
				// The remaining eight meeting dates would be unaffected by the switch.
				// The provisional schedule for 2017 preserves this structure.
				//
				// The MPC will meet on the first three of these provisional dates, in January, April and July 2016.
				// Following the July 2016 meeting, the MPC will move promptly to the eight meeting schedule as and when the Bill
				// has received Royal Assent and the provisions have come into force. So if that were to happen at any point before October 2016,
				// then the meeting currently scheduled for that month would be dropped, as would the meetings currently scheduled for
				// January, April, July and October 2017, as highlighted (*) in the table below.
				2016y / January / 14d,
				2016y / February / 4d,
				2016y / March / 17d,
				2016y / April / 14d,
				2016y / May / 12d,
				2016y / June / 16d,
				2016y / July / 14d,
				2016y / August / 4d,
				2016y / September / 15d,
				2016y / October / 13d, // *
				2016y / November / 3d,
				2016y / December / 15d,

				2017y / February / 2d,
				2017y / March / 16d,
				2017y / May / 11d,
				2017y / June / 15d,
				2017y / August / 3d,
				2017y / September / 14d,
				2017y / November / 2d,
				2017y / December / 14d,

				2018y / February / 8d,
				2018y / March / 22d,
				2018y / May / 10d,
				2018y / June / 21d,
				2018y / August / 2d,
				2018y / September / 13d,
				2018y / November / 1d,
				2018y / December / 20d,

				2019y / February / 7d,
				2019y / March / 21d,
				2019y / May / 2d,
				2019y / June / 20d,
				2019y / August / 1d,
				2019y / September / 19d,
				2019y / November / 7d,
				2019y / December / 19d,

				2020y / January / 30d,
				2020y / March / 26d,
				2020y / May / 7d,
				2020y / June / 18d,
				2020y / August / 6d,
				2020y / September / 17d,
				2020y / November / 5d,
				2020y / December / 17d,

				2021y / February / 4d, // February MPC Summary and minutes and February Monetary Policy Report
				2021y / March / 18d, // March MPC Summary and minutes
				2021y / May / 6d, // May MPC Summary and minutes and May Monetary Policy Report
				2021y / June / 24d, // June MPC Summary and minutes
				2021y / August / 5d, // August MPC Summary and minutes and August Monetary Policy Report
				2021y / September / 23d, // September MPC Summary and minutes
				2021y / November / 4d, // November MPC Summary and minutes and November Monetary Policy Report
				2021y / December / 16d, // December MPC Summary and minutes 

				2022y / February / 3d, // February MPC Summary and minutes and February Monetary Policy Report
				2022y / March / 17d, // March MPC Summary and minutes
				2022y / May / 5d, // May MPC Summary and minutes and May Monetary Policy Report
				2022y / June / 16d, // June MPC Summary and minutes
				2022y / August / 4d, // August MPC Summary and minutes and August Monetary Policy Report
				2022y / September / 15d, // September MPC Summary and minutes
				2022y / November / 3d, // November MPC Summary and minutes and November Monetary Policy Report
				2022y / December / 15d, // December MPC Summary and minutes

				2023y / February / 2d, // February MPC Summary and minutes and February Monetary Policy Report
				2023y / March / 23d, // March MPC Summary and minutes
				2023y / May / 11d, // May MPC Summary and minutes and May Monetary Policy Report
				2023y / June / 22d, // June MPC Summary and minutes
				2023y / August / 3d, // August MPC Summary and minutes and August Monetary Policy Report
				2023y / September / 21d, // September MPC Summary and minutes
				2023y / November / 2d, // November MPC Summary and minutes and November Monetary Policy Report
				2023y / December / 14d, // December MPC Summary and minutes

				2024y / February / 1d, //February MPC Summary and minutes and February Monetary Policy Report
				2024y / March / 21d, // March MPC Summary and minutes
				2024y / May / 9d, // May MPC Summary and minutes and May Monetary Policy Report
				2024y / June / 20d, // June MPC Summary and minutes
				2024y / August / 1d, // August MPC Summary and minutes and August Monetary Policy Report
				2024y / September / 19d, // September MPC Summary and minutes
				2024y / November / 7d, // November MPC Summary and minutes and November Monetary Policy Report
				2024y / December / 19d, // December MPC Summary and minutes

				2025y / February / 6d, // February MPC Summary and minutes and February Monetary Policy Report
				2025y / March / 20d, // March MPC Summary and minutes
				2025y / May / 8d, // May MPC Summary and minutes and May Monetary Policy Report
				2025y / June / 19d, // June MPC Summary and minutes
				2025y / August / 7d, // August MPC Summary and minutes and August Monetary Policy Report
				2025y / September / 18d, // September MPC Summary and minutes
				2025y / November / 6d, // November MPC Summary and minutes and November Monetary Policy Report
				2025y / December / 18d, // December MPC Summary and minutes

				2026y / February / 5d, // February MPC Summary and minutes and February Monetary Policy Report
				2026y / March / 19d, // March MPC Summary and minutes
				2026y / April / 30d, // April MPC Summary and minutes and April Monetary Policy Report
				2026y / June / 18d, // June MPC Summary and minutes
				2026y / July/ 30d, // July MPC Summary and minutes and July Monetary Policy Report
				2026y / September / 17d, // September MPC Summary and minutes
				2026y / November / 5d, // November MPC Summary and minutes and November Monetary Policy Report
				2026y / December / 17d, // December MPC Summary and minutes 

				// provisional dates
				2027y / February / 4d, // February MPC Summary and minutes and February Monetary Policy Report
				2027y / March / 18d, // March MPC Summary and minutes
				2027y / April / 29d, // April MPC Summary and minutes and April Monetary Policy Report
				2027y / June / 17d, // June MPC Summary and minutes
				2027y / July / 29d, // July MPC Summary and minutes and July Monetary Policy Report
				2027y / September / 16d, // September MPC Summary and minutes
				2027y / November / 4d, // November MPC Summary and minutes and November Monetary Policy Report
				2027y / December / 16d, // December MPC Summary and minutes 
			};

			return schedule{
				util::days_period{ Epoch.get_from(), 2027y / LastDayOfDecember},
				move(meeting_dates)
			};
		}

		static auto _MPC_schedule() -> schedule // MPC holiday dates
		{
			return ~_MPC_dates();
		}

		static auto _make_MPC_calendar() -> calendar
		{
			const auto known_part = _MPC_schedule();

			// should provisional dates as of publication time should be historical rules?

			return calendar{
				NoWeekend,
				known_part
			};
		}



		auto make_England_calendar() -> const calendar&
		{
			static const auto s = _make_England_calendar();
			return s;
		}

		auto make_Wales_calendar() -> const calendar&
		{
			return make_England_calendar();
		}

		auto make_Scotland_calendar() -> const calendar&
		{
			static const auto s = _make_Scotland_calendar();
			return s;
		}

		auto make_Northern_Ireland_calendar() -> const calendar&
		{
			static const auto s = _make_Northern_Ireland_calendar();
			return s;
		}


		auto make_MPC_calendar() -> const calendar&
		{
			static const auto s = _make_MPC_calendar();
			return s;
		}

	}

}
