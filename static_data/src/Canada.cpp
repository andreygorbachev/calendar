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

		static auto _Canada_Federal_schedule() -> schedule // or should it be a "proper" function (without _)?
		{
			auto holidays = schedule::dates{
				2025y / January / 1d, // New Year
				2025y / April / 18d, // Good Friday
				2025y / April / 21d, // Easter Monday
				2025y / May / 19d, // Victoria Day
				2025y / July / 1d, // Canada Day
				2025y / September / 1d, // Labour Day
				2025y / September / 30d, // National Day for Truth and Reconciliation
				2025y / October / 13d, // Thanksgiving Day
				2025y / November / 11d, // Remembrance Day
				2025y / December / 25d, // Christmas Day
				2025y / December / 26d, // Boxing Day
			};

			return schedule{
//				days_period{ Epoch.get_from(), 2030y / LastDayOfDecember },
				days_period{ 2025 / FirstDayOfJanuary, 2025y / LastDayOfDecember },
				move(holidays)
			};
		}

//		static auto _Washington_DC_Federal_schedule() -> schedule // or should it be a "proper" function (without _)?
//		{
//			auto holidays = schedule::dates{
//				2013y / January / 21d,
//
//				2017y / January / 20d,
//
//				2021y / January / 20d,
//
//				2025y / January / 20d,
//
//				2029y / January / 19d,
//			};
//
//			return schedule{
//				days_period{ Epoch.get_from(), 2030y / LastDayOfDecember },
//				move(holidays)
//			};
//		}

		static auto _make_Canada_Federal_calendar() -> calendar
		{
			const auto known_part = _Canada_Federal_schedule();

//			const auto generated_part_from = known_part.get_period().get_until().year() + years{ 1 };
//			const auto generated_part_until = Epoch.get_until().year();
//
//			const auto MartinLutherKing = weekday_indexed_holiday{ January / Monday[3] }; // Birthday Of Martin Luther King, Jr.
//			const auto Washington = weekday_indexed_holiday{ February / Monday[3] }; // Washington's Birthday
//			const auto MemorialDay = weekday_last_holiday{ May / Monday[last] };
//			const auto Juneteenth = named_holiday{ June / 19d }; // Emancipation Day
//			const auto IndependenceDay = named_holiday{ July / 4d };
//			const auto LaborDay = weekday_indexed_holiday{ September / Monday[1] };
//			const auto ColumbusDay = weekday_indexed_holiday{ October / Monday[2] };
//			const auto VeteransDay = named_holiday{ November / 11d };
//			const auto ThanksgivingDay = weekday_indexed_holiday{ November / Thursday[4] };
//
//			const auto rules = annual_holiday_storage{
//				&NewYearsDay,
//				&MartinLutherKing,
//				&Washington,
//				&MemorialDay,
//				&Juneteenth,
//				&IndependenceDay,
//				&LaborDay,
//				&ColumbusDay,
//				&VeteransDay,
//				&ThanksgivingDay,
//				&ChristmasDay
//			};
//
//			const auto generated_part = make_holiday_schedule(
//				years_period{ generated_part_from, generated_part_until },
//				rules
//			);
//
//			// setup a calendar for the generated part only (to do substitution for the generated dates)
//			auto cal = calendar{
//				SaturdaySundayWeekend,
//				generated_part
//			};
//			cal.substitute(Nearest);

			return calendar{
				SaturdaySundayWeekend,
				known_part /* + cal.get_schedule()*/
			};
		}

//		// should it move to the main library (in a more generic form)?
//		static auto _make_Washington_DC_Federal_holiday_schedule(
//			const util::years_period& p,
//			const annual_holiday_storage& rules
//		) noexcept -> schedule
//		{
//			auto hols = schedule::dates{};
//
//			for (auto y = 2033y; y <= p.get_until(); y += years{ 4 })
//				for (const auto& rule : rules)
//					hols.insert(rule->make_holiday(y));
//
//			return schedule{
//				util::days_period{
//					p.get_from() / FirstDayOfJanuary,
//					p.get_until() / LastDayOfDecember
//				},
//				move(hols)
//			};
//		}
//
//		static auto _make_Washington_DC_Federal_calendar() -> calendar
//		{
//			const auto known_part = _Washington_DC_Federal_schedule();
//
//			const auto generated_part_from = known_part.get_period().get_until().year() + years{ 1 };
//			const auto generated_part_until = Epoch.get_until().year();
//
//			const auto InaugurationDay = named_holiday{ January / 20d };
//
//			const auto rules = annual_holiday_storage{
//				&InaugurationDay
//			};
//
//			const auto generated_part = _make_Washington_DC_Federal_holiday_schedule(
//				years_period{ generated_part_from, generated_part_until },
//				rules
//			);
//
//			// setup a calendar for the generated part only (to do substitution for the generated dates)
//			auto cal = calendar{
//				SaturdaySundayWeekend,
//				generated_part
//			};
//			cal.substitute(Nearest);
//
//			return 
//				_make_USA_Federal_calendar() |
//				calendar{ SaturdaySundayWeekend, known_part + cal.get_schedule() };
//		}



		auto make_Canada_Federal_calendar() -> const calendar&
		{
			static const auto s = _make_Canada_Federal_calendar();
			return s;
		}

//		auto make_Washington_DC_Federal_calendar() -> const calendar&
//		{
//			static const auto s = _make_Washington_DC_Federal_calendar();
//			return s;
//		}

	}

}
