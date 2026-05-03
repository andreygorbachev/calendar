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
#include "cyclical_holiday.h"

#include <period.h>
#include <schedule.h>
#include <weekend.h>
#include <annual_holiday_interface.h>
#include <annual_holidays.h>
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

		// there was also some changes announced in 2005 about shifting holidays to make long weekends - we are not yet handling the histical calendars
		const auto _ConstitutionDay = weekday_indexed_holiday{ February / Monday[1] }; // Observance
		const auto _BenitoJuarezsBirthday = weekday_indexed_holiday{ March / Monday[3] }; // Observance
		const auto _HolyThursday = offset_holiday{ &_Easter, std::chrono::days{ -3 } }; // should it be in the main library?
		const auto _LabourDay = named_holiday{ May / 1d };
		const auto _IndependenceDay = named_holiday{ September / 16d };
		const auto _AllSoulsDay = named_holiday{ November / 2d }; // should it be in the main library?
		const auto _RevolutionDay = weekday_indexed_holiday{ November / Monday[3] }; // Observance
		const auto _FeastOfOurLadyOfGuadalupe = named_holiday{ December / 12d };

		const auto _InaugurationDay = _cyclical_holiday{
			named_holiday{ October / 1d },
			2024y, // before that it was December 1st, but moved to October 1st in 2024 - we are not yet handling the histical calendars
			years{ 6 }
		};



		static auto _make_CNBV_known_schedule_part0() -> schedule // is it a correct name? (CNBV?)
		{
			auto holidays = schedule::dates{

				// from https://sidof.segob.gob.mx/notas/2102331

				2006y / January / 1d,
				2006y / February / 6d, // 2006y / February / 5d,
				2006y / March / 21d, // not moved?
				2006y / April / 13d,
				2006y / April / 14d,
				2006y / May / 1d,
				2006y / September / 16d,
				2006y / November / 2d,
				2006y / November / 20d,
				2006y / December / 1d, // inauguration of Felipe Calderón
				2006y / December / 12d,
				2006y / December / 25d,

				// from "DISPOSICIONES DE CARÁCTER GENERAL QUE SEÑALAN LOS DÍAS DEL AÑO 2022, EN QUE LAS
				// ENTIDADES FINANCIERAS SUJETAS A LA SUPERVISIÓN DE LA COMISIÓN NACIONAL BANCARIA Y
				// DE VALORES, DEBERÁN CERRAR SUS PUERTAS Y SUSPENDER OPERACIONES"

				2022y / January / 1d, // I. El 1 de enero.
				2022y / February / 7d, // II. El primer lunes de febrero en conmemoración del 5 de febrero.
				2022y / March / 21d, // III. El tercer lunes de marzo en conmemoración del 21 de marzo.
				2022y / April / 14d, // IV. El 14 y 15 de abril.
				2022y / April / 15d,
				2022y / May / 1d, // V. El 1 de mayo.
				2022y / September / 16d, // VI. El 16 de septiembre.
				2022y / November / 2d, // VII. El 2 de noviembre y el tercer lunes de noviembre en conmemoración del 20 de noviembre.
				2022y / November / 21d,
				2022y / December / 12d, // VIII. El 12 y 25 de diciembre.
				2022y / December / 25d,

				// from "DISPOSICIONES DE CARÁCTER GENERAL QUE SEÑALAN LOS DÍAS DEL AÑO 2023 EN QUE LAS
				// ENTIDADES FINANCIERAS SUJETAS A LA SUPERVISIÓN DE LA COMISIÓN NACIONAL BANCARIA Y
				// DE VALORES DEBERÁN CERRAR SUS PUERTAS Y SUSPENDER OPERACIONES"

				2023y / January / 1d, // I. El 1 de enero.
				2023y / February / 6d, // II. El primer lunes de febrero en conmemoración del 5 de febrero.
				2023y / March / 20d, // III. El tercer lunes de marzo en conmemoración del 21 de marzo.
				2023y / April / 6d, // IV. El 6 y 7 de abril.
				2023y / April / 7d,
				2023y / May / 1d, // V. El 1 de mayo.
				2023y / September / 16d, // VI. El 16 de septiembre.
				2023y / November / 2d, // VII. El 2 de noviembre y el tercer lunes de noviembre en conmemoración del 20 de noviembre.
				2023y / November / 20d,
				2023y / December / 12d, // VIII. El 12 y 25 de diciembre.
				2023y / December / 25d,

				// from "DISPOSICIONES DE CARÁCTER GENERAL QUE SEÑALAN LOS DÍAS DEL AÑO 2024 EN QUE LAS
				// ENTIDADES FINANCIERAS SUJETAS A LA SUPERVISIÓN DE LA COMISIÓN NACIONAL BANCARIA Y
				// DE VALORES DEBERÁN CERRAR SUS PUERTAS Y SUSPENDER OPERACIONES"

				2024y / January / 1d, // I. El 1o. de enero.
				2024y / February / 5d, // II. El primer lunes de febrero en conmemoración del 5 de febrero.
				2024y / March / 18d, // III. El tercer lunes de marzo en conmemoración del 21 de marzo.
				2024y / March / 28d, // IV. El 28 y 29 de marzo.
				2024y / March / 29d,
				2024y / May / 1d, // V. El 1o. de mayo.
				2024y / September / 16d, // VI. El 16 de septiembre.
				2024y / October / 1d, // VII. El 1o. de octubre.
				2024y / November / 2d, // VIII. El 2 de noviembre y el tercer lunes de dicho mes en conmemoración del 20 de noviembre.
				2024y / November / 18d,
				2024y / December / 12d, // IX. El 12 y 25 de diciembre.
				2024y / December / 25d,

				// from "DISPOSICIONES DE CARÁCTER GENERAL QUE SEÑALAN LOS DÍAS DEL AÑO 2025 EN QUE LAS
				// ENTIDADES FINANCIERAS SUJETAS A LA SUPERVISIÓN DE LA COMISIÓN NACIONAL BANCARIA Y
				// DE VALORES DEBERÁN CERRAR SUS PUERTAS Y SUSPENDER OPERACIONES"

				2025y / January / 1d, // I. El 1o. de enero.
				2025y / February / 3d, // II. El primer lunes de febrero en conmemoración del 5 de febrero.
				2025y / March / 17d, // III. El tercer lunes de marzo en conmemoración del 21 de marzo.
				2025y / April / 17d, // IV. El 17 y 18 de abril.
				2025y / April / 18d,
				2025y / May / 1d, // V. El 1o. de mayo.
				2025y / September / 16d, // VI. El 16 de septiembre.
				2025y / November / 2d, // VII. El 2 de noviembre y el tercer lunes de dicho mes en conmemoración del 20 de noviembre.
				2025y / November / 17d,
				2025y / December / 12d, // VIII. El 12 y 25 de diciembre.
				2025y / December / 25d,

				// from "DISPOSICIONES DE CARÁCTER GENERAL QUE SEÑALAN LOS DÍAS DEL AÑO 2026 EN QUE LAS
				// ENTIDADES FINANCIERAS SUJETAS A LA SUPERVISIÓN DE LA COMISIÓN NACIONAL BANCARIA Y DE
				// VALORES DEBERÁN CERRAR SUS PUERTAS Y SUSPENDER OPERACIONES"

				2026y / January / 1d, // I. El 1o. de enero.
				2026y / February / 2d, // II. El primer lunes de febrero en conmemoración del 5 de febrero.
				2026y / March / 16d, // III. El tercer lunes de marzo en conmemoración del 21 de marzo.
				2026y / April / 2d, // IV. El 2 y 3 de abril.
				2026y / April / 3d,
				2026y / May / 1d, // V. El 1o. de mayo.
				2026y / September / 16d, // VI. El 16 de septiembre.
				2026y / November / 2d, // VII. El 2 de noviembre y el tercer lunes de dicho mes, este último en conmemoración del 20 de noviembre.
				2026y / November / 16d,
				2026y / December / 12d, // VIII. El 12 y 25 de diciembre.
				2026y / December / 25d,
			};

			return schedule{
				days_period{ 2025y / FirstDayOfJanuary, 2026y / LastDayOfDecember },
				std::move(holidays)
			};
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
				&_InaugurationDay,
				&_AllSoulsDay,
				&_RevolutionDay,
				&_FeastOfOurLadyOfGuadalupe,
				&ChristmasDay
			};

			return make_holiday_schedule(
				util::years_period{ 2027y, Epoch.get_until().year() },
				rules
			);
		}

		auto make_CNBV_calendar_versions() -> _calendar_versions
		{
			auto cal0 = calendar{
				SaturdaySundayWeekend,
				_make_CNBV_known_schedule_part0() +
				_make_CNBV_generated_schedule_part0()
			};

			return {
//				{ cal0.get_schedule().get_period().get_from(), std::move(cal0) },
				{ 2026y / FirstDayOfJanuary, std::move(cal0) },
			};
		}

	}

}
