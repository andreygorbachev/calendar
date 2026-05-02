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
#include <weekend.h>
#include <annual_holiday_interface.h>
#include <annual_holidays.h>
#include <business_day_adjusters.h>
#include <calendar.h>

#include <chrono>
#include <utility>

using namespace std;
using namespace std::chrono;


namespace gregorian
{

	using namespace util;

	namespace static_data
	{

		// from Bank of Mexico website:
		// 
		// 2026 bank holidays
		// 
		// • January 1.
		// • The first Monday of February in commemoration of February 5.
		// • The third Monday of March in commemoration of March 21.
		// • April 2 and 3.
		// • May 1.
		// • September 16.
		// • November 2 and the third Monday of the month in commemoration of November 20.
		// • December 12 and 25.
		// • Saturdays and Sundays.



		// there was also some changes announced in 2005 about shifting holidays to make long weekends - we might not be handliong them correctly
		const auto _ConstitutionDay = weekday_indexed_holiday{ February / Monday[1] }; // Observance
		const auto _BenitoJuarezsBirthday = weekday_indexed_holiday{ March / Monday[3] }; // Observance
		const auto _HolyThursday = offset_holiday{ &_Easter, std::chrono::days{ -3 } }; // should it be in the main library?
		const auto _LabourDay = named_holiday{ May / 1d };
		const auto _IndependenceDay = named_holiday{ September / 16d };
		const auto _AllSoulsDay = named_holiday{ November / 2d }; // should it be in the main library?
		const auto _RevolutionDay = weekday_indexed_holiday{ November / Monday[3] }; // Observance
		const auto _FeastOfOurLadyOfGuadalupe = named_holiday{ December / 12d };



		static auto _make_CNBV_known_schedule_part0() -> schedule // is it a correct name? (CNBV)
		{
			auto holidays = schedule::dates{

				// from https://sidof.segob.gob.mx/notas/2102331

				2006y / January / 1d,
				2006y / February / 5d,
				2006y / March / 21d,
				2006y / April / 13d,
				2006y / April / 14d,
				2006y / May / 1d,
				2006y / September / 16d,
				2006y / November / 2d,
				2006y / November / 20d,
				2006y / December / 1d,
				2006y / December / 12d,
				2006y / December / 25d,

//				2026y / January / 1d, // Ano Nuevo
//				2026y / February / 2d, // Día de la Constitución
//				2026y / March / 16d, // Natalicio de Benito Juárez
//				2026y / April / 2d, // Jueves Santo
//				2026y / April / 3d, // Viernes Santo
//				2026y / May / 1d, // Día del Trabajo
//				2026y / September / 16d, // Día de la Independencia
//				2026y / November / 2d, // Día de los Fieles Difuntos (Día de Muertos)
//				2026y / November / 16d, // Día de la Revolución
//				2026y / December / 12d, // Día de la Virgen de Guadalupe
//				2026y / December / 25d, // Navidad
			};

			auto s = schedule{
				days_period{ 2006y / FirstDayOfJanuary, 2006y / LastDayOfDecember },
				std::move(holidays)
			};

			auto cal = calendar{ SaturdaySundayWeekend, std::move(s) };
			cal.substitute(Nearest); // it seems that the SEGOB's publications are not adjusted

			return cal.get_schedule();
		}



		static auto _make_CNBV_generated_schedule_part0() -> schedule
		{
			const auto rules = annual_holiday_storage{
				&NewYearsDay,
				&_ConstitutionDay,
				&_BenitoJuarezsBirthday,
				&_HolyThursday,
				&GoodFriday,
				&_LabourDay,
				&_IndependenceDay,
				&_AllSoulsDay,
				&_RevolutionDay,
				&_FeastOfOurLadyOfGuadalupe,
				&ChristmasDay
			};

			auto s = make_holiday_schedule(
				util::years_period{ 2007y, Epoch.get_until().year() },
				rules
			);

			auto cal = calendar{ SaturdaySundayWeekend, std::move(s) };
			cal.substitute(Nearest);

			return cal.get_schedule();
		}

		auto make_CNBV_calendar_versions() -> _calendar_versions
		{
			auto cal0 = calendar{
				SaturdaySundayWeekend,
				_make_CNBV_known_schedule_part0() +
				_make_CNBV_generated_schedule_part0()
			};

			return {
				{ cal0.get_schedule().get_period().get_from(), std::move(cal0) },
			};
		}

	}

}
