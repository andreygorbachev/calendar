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

#include <utility>

using namespace std;
using namespace std::chrono;


namespace gregorian
{

	using namespace util;

	namespace static_data
	{

		auto _England_schedule() -> schedule // or should it be a "proper" function (without _)?
		{
			auto holidays = schedule::dates{
				2018y / January / 1d,
				2018y / March / 30d,
				2018y / April / 2d,
				2018y / May / 7d,
				2018y / May / 28d,
				2018y / August / 27d,
				2018y / December / 25d,
				2018y / December / 26d,

				2019y / January / 1d,
				2019y / April / 19d,
				2019y / April / 22d,
				2019y / May / 6d,
				2019y / May / 27d,
				2019y / August / 26d,
				2019y / December / 25d,
				2019y / December / 26d,

				2020y / January / 1d,
				2020y / April / 10d,
				2020y / April / 13d,
				2020y / May / 8d,
				2020y / May / 25d,
				2020y / August / 31d,
				2020y / December / 25d,
				2020y / December / 28d,

				2021y / January / 1d,
				2021y / April / 2d,
				2021y / April / 5d,
				2021y / May / 3d,
				2021y / May / 31d,
				2021y / August / 30d,
				2021y / December / 27d,
				2021y / December / 28d,

				2022y / January / 3d,
				2022y / April / 15d,
				2022y / April / 18d,
				2022y / May / 2d,
				2022y / June / 2d,
				2022y / June / 3d,
				2022y / August / 29d,
				2022y / September / 19d,
				2022y / December / 26d,
				2022y / December / 27d,

				2023y / January / 2d,
				2023y / April / 7d,
				2023y / April / 10d,
				2023y / May / 1d,
				2023y / May / 8d,
				2023y / May / 29d,
				2023y / August / 28d,
				2023y / December / 25d,
				2023y / December / 26d,

				2024y / January / 1d,
				2024y / March / 29d,
				2024y / April / 1d,
				2024y / May / 6d,
				2024y / May / 27d,
				2024y / August / 26d,
				2024y / December / 25d,
				2024y / December / 26d,

				2025y / January / 1d,
				2025y / April / 18d,
				2025y / April / 21d,
				2025y / May / 5d,
				2025y / May / 26d,
				2025y / August / 25d,
				2025y / December / 25d,
				2025y / December / 26d,

				2026y / January / 1d,
				2026y / April / 3d,
				2026y / April / 6d,
				2026y / May / 4d,
				2026y / May / 25d,
				2026y / August / 31d,
				2026y / December / 25d,
				2026y / December / 28d,

				2027y / January / 1d,
				2027y / March / 26d,
				2027y / March / 29d,
				2027y / May / 3d,
				2027y / May / 31d,
				2027y / August / 30d,
				2027y / December / 27d,
				2027y / December / 28d,
			};

			return schedule{
				days_period{ Epoch.get_from(), 2027y / LastDayOfDecember },
				move(holidays)
			};
		}

		auto _make_England_calendar() -> calendar
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



		auto _Scotland_schedule() -> schedule
		{
			auto holidays = schedule::dates{
				2018y / January / 1d,
				2018y / January / 2d,
				2018y / March / 30d,
				2018y / May / 7d,
				2018y / May / 28d,
				2018y / August / 6d,
				2018y / November / 30d,
				2018y / December / 25d,
				2018y / December / 26d,

				2019y / January / 1d,
				2019y / January / 2d,
				2019y / April / 19d,
				2019y / May / 6d,
				2019y / May / 27d,
				2019y / August / 5d,
				2019y / December / 2d,
				2019y / December / 25d,
				2019y / December / 26d,

				2020y / January / 1d,
				2020y / January / 2d,
				2020y / April / 10d,
				2020y / May / 8d,
				2020y / May / 25d,
				2020y / August / 3d,
				2020y / November / 30d,
				2020y / December / 25d,
				2020y / December / 28d,

				2021y / January / 1d,
				2021y / January / 4d,
				2021y / April / 2d,
				2021y / May / 3d,
				2021y / May / 31d,
				2021y / August / 2d,
				2021y / November / 30d,
				2021y / December / 27d,
				2021y / December / 28d,

				2022y / January / 3d,
				2022y / January / 4d,
				2022y / April / 15d,
				2022y / May / 2d,
				2022y / June / 2d,
				2022y / June / 3d,
				2022y / August / 1d,
				2022y / September / 19d,
				2022y / November / 30d,
				2022y / December / 26d,
				2022y / December / 27d,

				2023y / January / 2d,
				2023y / January / 3d,
				2023y / April / 7d,
				2023y / May / 1d,
				2023y / May / 8d,
				2023y / May / 29d,
				2023y / August / 7d,
				2023y / November / 30d,
				2023y / December / 25d,
				2023y / December / 26d,

				2024y / January / 1d,
				2024y / January / 2d,
				2024y / March / 29d,
				2024y / May / 6d,
				2024y / May / 27d,
				2024y / August / 5d,
				2024y / December / 2d,
				2024y / December / 25d,
				2024y / December / 26d,

				2025y / January / 1d,
				2025y / January / 2d,
				2025y / April / 18d,
				2025y / May / 5d,
				2025y / May / 26d,
				2025y / August / 4d,
				2025y / December / 1d,
				2025y / December / 25d,
				2025y / December / 26d,

				2026y / January / 1d,
				2026y / January / 2d,
				2026y / April / 3d,
				2026y / May / 4d,
				2026y / May / 25d,
				2026y / August / 3d,
				2026y / November / 30d,
				2026y / December / 25d,
				2026y / December / 28d,

				2027y / January / 1d,
				2027y / January / 4d,
				2027y / March / 26d,
				2027y / May / 3d,
				2027y / May / 31d,
				2027y / August / 2d,
				2027y / November / 30d,
				2027y / December / 27d,
				2027y / December / 28d,
			};

			return schedule{
				days_period{ Epoch.get_from(), 2027y / LastDayOfDecember },
				move(holidays)
			};
		}

		auto _make_Scotland_calendar() -> calendar
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



		auto _Northern_Ireland_schedule() -> schedule
		{
			auto holidays = schedule::dates{
				2018y / January / 1d,
				2018y / March / 19d,
				2018y / March / 30d,
				2018y / April / 2d,
				2018y / May / 7d,
				2018y / May / 28d,
				2018y / July / 12d,
				2018y / August / 27d,
				2018y / December / 25d,
				2018y / December / 26d,

				2019y / January / 1d,
				2019y / March / 18d,
				2019y / April / 19d,
				2019y / April / 22d,
				2019y / May / 6d,
				2019y / May / 27d,
				2019y / July / 12d,
				2019y / August / 26d,
				2019y / December / 25d,
				2019y / December / 26d,

				2020y / January / 1d,
				2020y / March / 17d,
				2020y / April / 10d,
				2020y / April / 13d,
				2020y / May / 8d,
				2020y / May / 25d,
				2020y / July / 13d,
				2020y / August / 31d,
				2020y / December / 25d,
				2020y / December / 28d,

				2021y / January / 1d,
				2021y / March / 17d,
				2021y / April / 2d,
				2021y / April / 5d,
				2021y / May / 3d,
				2021y / May / 31d,
				2021y / July / 12d,
				2021y / August / 30d,
				2021y / December / 27d,
				2021y / December / 28d,

				2022y / January / 3d,
				2022y / March / 17d,
				2022y / April / 15d,
				2022y / April / 18d,
				2022y / May / 2d,
				2022y / June / 2d,
				2022y / June / 3d,
				2022y / July / 12d,
				2022y / August / 29d,
				2022y / September / 19d,
				2022y / December / 26d,
				2022y / December / 27d,

				2023y / January / 2d,
				2023y / March / 17d,
				2023y / April / 7d,
				2023y / April / 10d,
				2023y / May / 1d,
				2023y / May / 8d,
				2023y / May / 29d,
				2023y / July / 12d,
				2023y / August / 28d,
				2023y / December / 25d,
				2023y / December / 26d,

				2024y / January / 1d,
				2024y / March / 18d,
				2024y / March / 29d,
				2024y / April / 1d,
				2024y / May / 6d,
				2024y / May / 27d,
				2024y / July / 12d,
				2024y / August / 26d,
				2024y / December / 25d,
				2024y / December / 26d,

				2025y / January / 1d,
				2025y / March / 17d,
				2025y / April / 18d,
				2025y / April / 21d,
				2025y / May / 5d,
				2025y / May / 26d,
				2025y / July / 14d,
				2025y / August / 25d,
				2025y / December / 25d,
				2025y / December / 26d,

				2026y / January / 1d,
				2026y / March / 17d,
				2026y / April / 3d,
				2026y / April / 6d,
				2026y / May / 4d,
				2026y / May / 25d,
				2026y / July / 13d,
				2026y / August / 31d,
				2026y / December / 25d,
				2026y / December / 28d,

				2027y / January / 1d,
				2027y / March / 17d,
				2027y / March / 26d,
				2027y / March / 29d,
				2027y / May / 3d,
				2027y / May / 31d,
				2027y / July / 12d,
				2027y / August / 30d,
				2027y / December / 27d,
				2027y / December / 28d,
			};

			return schedule{
				days_period{ Epoch.get_from(), 2027y / LastDayOfDecember },
				move(holidays)
			};
		}

		auto _make_Northern_Ireland_calendar() -> calendar
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


		auto _MPC_dates() -> schedule // actual MPC dates (not MPC holiday dates)
		{
			using namespace std::chrono;

			auto meeting_dates = schedule::dates{
				// 2023 confirmed dates
				2023y / February / 2d, // February MPC Summary and minutes and February Monetary Policy Report
				2023y / March / 23d, // March MPC Summary and minutes
				2023y / May / 11d, // May MPC Summary and minutes and May Monetary Policy Report
				2023y / June / 22d, // June MPC Summary and minutes
				2023y / August / 3d, // August MPC Summary and minutes and August Monetary Policy Report
				2023y / September / 21d, // September MPC Summary and minutes
				2023y / November / 2d, // November MPC Summary and minutes and November Monetary Policy Report
				2023y / December / 14d, // December MPC Summary and minutes
				// 2024 provisional dates
				2024y / February / 1d, //February MPC Summary and minutes and February Monetary Policy Report
				2024y / March / 21d, // March MPC Summary and minutes
				2024y / May / 9d, // May MPC Summary and minutes and May Monetary Policy Report
				2024y / June / 20d, // June MPC Summary and minutes
				2024y / August / 1d, // August MPC Summary and minutes and August Monetary Policy Report
				2024y / September / 19d, // September MPC Summary and minutes
				2024y / November / 7d, // November MPC Summary and minutes and November Monetary Policy Report
				2024y / December / 19d, // December MPC Summary and minutes
			};

			return schedule{ util::days_period{ 2023y / FirstDayOfJanuary, 2024y / LastDayOfDecember }, std::move(meeting_dates) };
		}

		auto _MPC_schedule() -> schedule // MPC holiday dates
		{
			return ~_MPC_dates();
		}

		auto _make_MPC_calendar() -> calendar
		{
			const auto known_part = _MPC_schedule();

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
