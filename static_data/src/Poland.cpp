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
#include <calendar.h>
#include <annual_holiday_interface.h>
#include <annual_holidays.h>
#include <weekend.h>
#include <schedule.h>

#include <utility>
#include <chrono>

using namespace std;
using namespace std::chrono;


namespace gregorian
{

	using namespace util;

	namespace static_data
	{

		// should these be in their own namespace?
		const auto _ThreeKingsDay = named_holiday{ January / 6d };
		const auto _LabourDay = named_holiday{ May / 1d };
		const auto _ConstitutionDay = named_holiday{ May / 3d };
		const auto _CorpusChristi = offset_holiday{ &_Easter, days{ 60 } }; // should it be in the main library?
		const auto _AssumptionDay = named_holiday{ August / 15d };
		const auto _AllSaintsDay = named_holiday{ November / 1d };
		const auto _IndependenceDay = named_holiday{ November / 11d };

		// Pursuant to the Act of 6 December 2024 amending the Act on Public Holidays, Christmas Eve has been a statutory public holiday since 2025.

		static auto _make_Warsaw_known_schedule_part0() -> schedule
		{
			auto holidays = schedule::dates{ // should we include day of the week into comments?

				// Implied from PolSTR history

				2021y / January / 1d, // New Year's Day
				2021y / January / 6d, // Epiphany
				2021y / April / 18d, // Easter Monday
				2021y / May / 1d, // Labor Day
				2021y / May / 3d, // Constitution Day
				2021y / June / 16d, // Corpus Christi
				2021y / August / 15d, // Assumption of the Blessed Virgin Mary
				2021y / November / 1d, // All Saints' Day
				2021y / November / 11d, // Independence Day
				2021y / December / 25d, // Christmas Day
				2021y / December / 26d, // St.Stephen's Day

				2022y / January / 1d, // New Year's Day
				2022y / January / 6d, // Epiphany
				2022y / April / 18d, // Easter Monday
				2022y / May / 1d, // Labor Day
				2022y / May / 3d, // Constitution Day
				2022y / June / 16d, // Corpus Christi
				2022y / August / 15d, // Assumption of the Blessed Virgin Mary
				2022y / November / 1d, // All Saints' Day
				2022y / November / 11d, // Independence Day
				2022y / December / 25d, // Christmas Day
				2022y / December / 26d, // St.Stephen's Day

				2023y / January / 1d, // New Year's Day
				2023y / January / 6d, // Epiphany
				2023y / April / 10d, // Easter Monday
				2023y / May / 1d, // Labor Day
				2023y / May / 3d, // Constitution Day
				2023y / June / 8d, // Corpus Christi
				2023y / August / 15d, // Assumption of the Blessed Virgin Mary
				2023y / November / 1d, // All Saints' Day
				2023y / November / 11d, // Independence Day
				2023y / December / 25d, // Christmas Day
				2023y / December / 26d, // St.Stephen's Day

				2024y / January / 1d, // New Year's Day
				2024y / January / 6d, // Epiphany
				2024y / April / 1d, // Easter Monday
				2024y / May / 1d, // Labor Day
				2024y / May / 3d, // Constitution Day
				2024y / May / 30d, // Corpus Christi
				2024y / August / 15d, // Assumption of the Blessed Virgin Mary
				2024y / November / 1d, // All Saints' Day
				2024y / November / 11d, // Independence Day
				2024y / December / 25d, // Christmas Day
				2024y / December / 26d, // St.Stephen's Day

				2025y / January / 1d, // New Year's Day
				2025y / January / 6d, // Epiphany
				2025y / April / 21d, // Easter Monday
				2025y / May / 1d, // Labor Day
				2025y / May / 3d, // Constitution Day
				2025y / June / 19d, // Corpus Christi
				2025y / August / 15d, // Assumption of the Blessed Virgin Mary
				2025y / November / 1d, // All Saints' Day
				2025y / November / 11d, // Independence Day
				2025y / December / 25d, // Christmas Day
				2025y / December / 26d // St.Stephen's Day
			};

			return schedule{
				days_period{ 2021y / FirstDayOfJanuary, 2025y / LastDayOfDecember },
				std::move(holidays)
			};
		}

		static auto _make_Warsaw_known_schedule_part1() -> schedule
		{
			auto holidays = schedule::dates{

				// Implied from PolSTR history

				2021y / January / 1d, // New Year's Day
				2021y / January / 6d, // Epiphany
				2021y / April / 18d, // Easter Monday
				2021y / May / 1d, // Labor Day
				2021y / May / 3d, // Constitution Day
				2021y / June / 16d, // Corpus Christi
				2021y / August / 15d, // Assumption of the Blessed Virgin Mary
				2021y / November / 1d, // All Saints' Day
				2021y / November / 11d, // Independence Day
				2021y / December / 25d, // Christmas Day
				2021y / December / 26d, // St.Stephen's Day

				2022y / January / 1d, // New Year's Day
				2022y / January / 6d, // Epiphany
				2022y / April / 18d, // Easter Monday
				2022y / May / 1d, // Labor Day
				2022y / May / 3d, // Constitution Day
				2022y / June / 16d, // Corpus Christi
				2022y / August / 15d, // Assumption of the Blessed Virgin Mary
				2022y / November / 1d, // All Saints' Day
				2022y / November / 11d, // Independence Day
				2022y / December / 25d, // Christmas Day
				2022y / December / 26d, // St.Stephen's Day

				2023y / January / 1d, // New Year's Day
				2023y / January / 6d, // Epiphany
				2023y / April / 10d, // Easter Monday
				2023y / May / 1d, // Labor Day
				2023y / May / 3d, // Constitution Day
				2023y / June / 8d, // Corpus Christi
				2023y / August / 15d, // Assumption of the Blessed Virgin Mary
				2023y / November / 1d, // All Saints' Day
				2023y / November / 11d, // Independence Day
				2023y / December / 25d, // Christmas Day
				2023y / December / 26d, // St.Stephen's Day

				2024y / January / 1d, // New Year's Day
				2024y / January / 6d, // Epiphany
				2024y / April / 1d, // Easter Monday
				2024y / May / 1d, // Labor Day
				2024y / May / 3d, // Constitution Day
				2024y / May / 30d, // Corpus Christi
				2024y / August / 15d, // Assumption of the Blessed Virgin Mary
				2024y / November / 1d, // All Saints' Day
				2024y / November / 11d, // Independence Day
				2024y / December / 25d, // Christmas Day
				2024y / December / 26d, // St.Stephen's Day

				2025y / January / 1d, // New Year's Day
				2025y / January / 6d, // Epiphany
				2025y / April / 21d, // Easter Monday
				2025y / May / 1d, // Labor Day
				2025y / May / 3d, // Constitution Day
				2025y / June / 19d, // Corpus Christi
				2025y / August / 15d, // Assumption of the Blessed Virgin Mary
				2025y / November / 1d, // All Saints' Day
				2025y / November / 11d, // Independence Day
				2025y / December / 24d, // Christmas Eve
				2025y / December / 25d, // Christmas Day
				2025y / December / 26d // St.Stephen's Day
			};

			return schedule{
				days_period{ 2021y / FirstDayOfJanuary, 2025y / LastDayOfDecember },
				std::move(holidays)
			};
		}


		static auto _make_Warsaw_generated_schedule_part0() -> schedule
		{
			const auto rules = annual_holiday_storage{
				&NewYearsDay,
				&_ThreeKingsDay,
				&_LabourDay,
				&_ConstitutionDay,
				&EasterMonday,
				&_CorpusChristi,
				&_AssumptionDay,
				&_AllSaintsDay,
				&_IndependenceDay,
				&ChristmasDay,
				&BoxingDay
			};

			return make_holiday_schedule(
				util::years_period{ 2026y, Epoch.get_until().year() },
				rules
			);
		}

		static auto _make_Warsaw_generated_schedule_part1() -> schedule
		{
			const auto rules = annual_holiday_storage{
				&NewYearsDay,
				&_ThreeKingsDay,
				&_LabourDay,
				&_ConstitutionDay,
				&EasterMonday,
				&_CorpusChristi,
				&_AssumptionDay,
				&_AllSaintsDay,
				&_IndependenceDay,
				&ChristmasEve,
				&ChristmasDay,
				&BoxingDay
			}; // we can make it from part0

			return make_holiday_schedule(
				util::years_period{ 2026y, Epoch.get_until().year() },
				rules
			);
		}


		auto make_Warsaw_calendar_versions() -> _calendar_versions
		{
			auto cal0 = calendar{
				SaturdaySundayWeekend,
				_make_Warsaw_known_schedule_part0() +
				_make_Warsaw_generated_schedule_part0()
			};

			auto cal1 = calendar{
				SaturdaySundayWeekend,
				_make_Warsaw_known_schedule_part1() +
				_make_Warsaw_generated_schedule_part1()
			};

			return {
				{ cal0.get_schedule().get_period().get_from(), std::move(cal0) },
				{ 2024y / December / 4d, std::move(cal1) },
			};
		}

	}

}