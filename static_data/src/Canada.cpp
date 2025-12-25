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
#include "victoria_day_holiday.h"

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
				2025y / January / 1d, // New Year // Nationwide statutory holiday
				2025y / April / 18d, // Good Friday // Nationwide statutory holiday
				2025y / April / 21d, // Easter Monday // Federal statutory holiday, also observed in some provinces // this one is not 100% clear to me from https://en.wikipedia.org/wiki/Public_holidays_in_Canada
				2025y / May / 19d, // Victoria Day // Federal statutory holiday, also observed in some provinces
				2025y / July / 1d, // Canada Day // Nationwide statutory holiday
				2025y / September / 1d, // Labour Day // Nationwide statutory holiday
				2025y / September / 30d, // National Day for Truth and Reconciliation // Federal statutory holiday, also observed in some provinces
				2025y / October / 13d, // Thanksgiving Day // Federal statutory holiday, also observed in some provinces
				2025y / November / 11d, // Remembrance Day // Federal statutory holiday, also observed in some provinces
				2025y / December / 25d, // Christmas Day // Nationwide statutory holiday
				2025y / December / 26d, // Boxing Day // Federal statutory holiday, also observed in some provinces
			};

			return schedule{
//				days_period{ Epoch.get_from(), 2030y / LastDayOfDecember },
				days_period{ 2025 / FirstDayOfJanuary, 2025y / LastDayOfDecember },
				move(holidays)
			};
		}

		static auto _Quebec_schedule() -> schedule // or should it be a "proper" function (without _)?
		{
			auto holidays = schedule::dates{
				2025y / June / 24d, // Saint-Jean-Baptiste Day
			};

			return schedule{
//				days_period{ Epoch.get_from(), 2030y / LastDayOfDecember },
				days_period{ 2025 / FirstDayOfJanuary, 2025y / LastDayOfDecember },
				move(holidays)
			};
		}

		// we should also deal with "Civic Holiday" - Monday, August 4, 2025 (excluding Quebec)


		static auto _make_Canada_Federal_calendar() -> calendar
		{
			const auto known_part = _Canada_Federal_schedule();

			const auto generated_part_from = known_part.get_period().get_until().year() + years{ 1 };
			const auto generated_part_until = Epoch.get_until().year();

			// from Wikipedia
			const auto CanadaDay = named_holiday{ July / 1d }; // celebrates the anniversary of Canadian Confederation which occurred on July 1, 1867
			const auto LabourDay = weekday_indexed_holiday{ September / Monday[1] }; // occurs on the first Monday in September
			const auto NDTR = named_holiday{ September / 30d }; // National Day for Truth and Reconciliation // day of memorial to recognize the atrocities and multi-generational effects of the Canadian Indian residential school system
			const auto ThanksgivingDay = weekday_indexed_holiday{ October / Monday[2] }; // held on the second Monday in October
			const auto RemembranceDay = named_holiday{ November / 11d }; // is observed on 11 November to recall the end of First World War hostilities

			const auto rules = annual_holiday_storage{
				&NewYearsDay,
				&GoodFriday,
				&EasterMonday,
				&_VictoriaDay,
				&CanadaDay,
				&LabourDay,
				&NDTR,
				&ThanksgivingDay,
				&RemembranceDay,
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
			cal.substitute(Nearest); // this needs to be checked

			return calendar{
				SaturdaySundayWeekend,
				known_part + cal.get_schedule()
			};
		}

//		// should it move to the main library (in a more generic form)?
//		static auto _make_Quebec_holiday_schedule(
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

		static auto _make_Quebec_calendar() -> calendar
		{
			const auto known_part = _Quebec_schedule();

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

			return 
				_make_Canada_Federal_calendar() |
				calendar{ SaturdaySundayWeekend, known_part /* + cal.get_schedule()*/};
		}



		auto make_Canada_Federal_calendar() -> const calendar&
		{
			static const auto s = _make_Canada_Federal_calendar();
			return s;
		}

		auto make_Quebec_calendar() -> const calendar&
		{
			static const auto s = _make_Quebec_calendar();
			return s;
		}

	}

}
