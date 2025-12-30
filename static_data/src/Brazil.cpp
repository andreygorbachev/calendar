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
#include <annual_holidays.h>
#include <business_day_adjusters.h>

#include <chrono>

using namespace std;
using namespace std::chrono;


namespace gregorian
{

	using namespace util;

	namespace static_data
	{

		// should these be inside make_ANBIMA_calendar_versions?
		const auto _TiradentesDay = named_holiday{ April / 21d };
		const auto _LabourDay = named_holiday{ May / 1d };
		const auto _ShroveMonday = offset_holiday{ &_Easter, days{ -47 - 1 } }; // should it be in the main library?
		const auto _ShroveTuesday = offset_holiday{ &_Easter, days{ -46 - 1 } }; // should it be in the main library?
		const auto _CorpusChristi = offset_holiday{ &_Easter, days{ 60 } }; // should it be in the main library?
		const auto _IndependenceDay = named_holiday{ September / 7d };
		const auto _OurLadyOfAparecida = named_holiday{ October / 12d };
		const auto _AllSoulsDay = named_holiday{ November / 2d }; // should it be in the main library?
		const auto _RepublicProclamationDay = named_holiday{ November / 15d };
		const auto _BlackConsciousnessDay = named_holiday{ November / 20d };


		auto make_ANBIMA_calendar_versions() -> _calendar_versions
		{
			constexpr auto epoch = period{
				year{ 2001 } / FirstDayOfJanuary, // starts before Epoch.get_from().year()
				Epoch.get_until()
			};

			const auto rules = _annual_holiday_period_storage{
				{ &NewYearsDay, epoch, epoch.get_from() },
				{ &_ShroveMonday, epoch, epoch.get_from() },
				{ &_ShroveTuesday, epoch, epoch.get_from() },
				{ &GoodFriday, epoch, epoch.get_from() },
				{ &_TiradentesDay, epoch, epoch.get_from() },
				{ &_LabourDay, epoch, epoch.get_from() },
				{ &_CorpusChristi, epoch, epoch.get_from() },
				{ &_IndependenceDay, epoch, epoch.get_from() },
				{ &_OurLadyOfAparecida, epoch, epoch.get_from() },
				{ &_AllSoulsDay, epoch, epoch.get_from() },
				{ &_RepublicProclamationDay, epoch, epoch.get_from() },
				{
					&_BlackConsciousnessDay,
					period{ 2024y / FirstDayOfJanuary, Epoch.get_until() }, // or should it be the first day it was celebrated? (are we dealing in whole years here?)
					2023y / December / 21d // was enacted as Law No. 14,759 on 21 December 2023
				},
				{ &ChristmasDay, epoch, epoch.get_from() }
			};

			return _make_calendar_versions(
				rules,
				epoch,
				SaturdaySundayWeekend,
				NoAdjustment
			);
		}

	}

}
