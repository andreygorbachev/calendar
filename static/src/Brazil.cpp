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

#include "static.h"

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

		auto _make_ANBIMA_calendar() -> calendar
		{
			const auto TiradentesDay = named_holiday{ April / 21d };
			const auto LabourDay = named_holiday{ May / 1d };
			const auto ShroveMonday = offset_holiday{ &_Easter, std::chrono::days{ -47 - 1 } }; // should it be in the actual library?
			const auto ShroveTuesday = offset_holiday{ &_Easter, std::chrono::days{ -46 - 1 } }; // should it be in the actual library?
			const auto CorpusChristi = offset_holiday{ &_Easter, std::chrono::days{ 60 } }; // should it be in the actual library?
			const auto IndependenceDay = named_holiday{ September / 7d };
			const auto OurLadyOfAparecida = named_holiday{ October / 12d };
			const auto AllSoulsDay = named_holiday{ November / 2d }; // should it be in the actual library?
			const auto RepublicProclamationDay = named_holiday{ November / 15d };

			const auto rules1 = annual_holiday_storage{
				&NewYearsDay,
				&ShroveMonday,
				&ShroveTuesday,
				&GoodFriday,
				&TiradentesDay,
				&LabourDay,
				&CorpusChristi,
				&IndependenceDay,
				&OurLadyOfAparecida,
				&AllSoulsDay,
				&RepublicProclamationDay,
				&ChristmasDay
			};

			const auto s1 = make_holiday_schedule(
				years_period{ 2001y, 2023y },
				rules1
			);

			const auto BlackConsciousnessDay = named_holiday{ November / 20d };

			const auto rules2 = annual_holiday_storage{
				&NewYearsDay,
				&ShroveMonday,
				&ShroveTuesday,
				&GoodFriday,
				&TiradentesDay,
				&LabourDay,
				&CorpusChristi,
				&IndependenceDay,
				&OurLadyOfAparecida,
				&AllSoulsDay,
				&RepublicProclamationDay,
				&BlackConsciousnessDay,
				&ChristmasDay
			};

			const auto s2 = make_holiday_schedule(
				years_period{ 2024y, 2099y },
				rules2
			);

			return calendar{
				SaturdaySundayWeekend,
				s1 + s2
			};
			// please note that holidays are not adjusted in ANBIMA
		}

/*
		auto _B3_schedule() -> schedule
		{
			// from https://www.b3.com.br/en_us/solutions/platforms/puma-trading-system/for-members-and-traders/trading-calendar/holidays/

			const auto period = years_period{ 2001y, 2099y };

			const auto SaoPaulosFoundation = named_holiday{ January / 25d };
			const auto ConstitutionalistRevolution = named_holiday{ July / 9d };
			const auto BlackConsciousnessDay = named_holiday{ November / 20d };

			const auto rules1 = annual_holiday_storage{
				&SaoPaulosFoundation,
				&ConstitutionalistRevolution,
				&BlackConsciousnessDay,
				&ChristmasEve
			};

			const auto s1 = make_holiday_schedule(period, rules1);

			// finally add last business day of the year as a holiday

			const auto rules2 = annual_holiday_storage{
				&NewYearsEve
			};

			const auto s2 = make_holiday_schedule(period, rules1);

			auto c2 = calendar{ SaturdaySundayWeekend, s2 };
			c2.substitute(Preceding);

			return _ANBIMA_schedule() + s1 + c2.get_schedule();
		}
*/


		auto make_ANBIMA_calendar() -> const calendar&
		{
			static const auto s = _make_ANBIMA_calendar();
			return s;
		}
/*
		auto make_B3_calendar() -> const calendar&
		{
			static const auto s = _make_B3_calendar();
			return s;
		}
*/
	}

}
