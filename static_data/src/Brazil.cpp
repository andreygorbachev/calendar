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
#include <annual_holidays.h>
#include <weekend.h>
#include <business_day_adjusters.h>

#include <vector>
#include <ranges>

using namespace std;
using namespace std::chrono;
using namespace std::ranges;
using namespace std::ranges::views;


namespace gregorian
{

	using namespace util;

	namespace static_data
	{

		struct _annual_holiday_period final
		{
			const annual_holiday* holiday;
			days_period period{ Epoch }; // we probably need a separate epochs for announcements and applicability
		};

		using _annual_holiday_period_storage = vector<_annual_holiday_period>;

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

		const auto _ANBINA_annual_holiday_period_storage = _annual_holiday_period_storage{
			{ &NewYearsDay, Epoch },
			{ &_ShroveMonday, Epoch },
			{ &_ShroveTuesday, Epoch },
			{ &GoodFriday, Epoch },
			{ &_TiradentesDay, Epoch },
			{ &_LabourDay, Epoch },
			{ &_CorpusChristi, Epoch },
			{ &_IndependenceDay, Epoch },
			{ &_OurLadyOfAparecida, Epoch },
			{ &_AllSoulsDay, Epoch },
			{ &_RepublicProclamationDay, Epoch },
			{ &_BlackConsciousnessDay, period{ 2024y / FirstDayOfJanuary, Epoch.get_until() } },
			{ &ChristmasDay, Epoch }
		};


		auto _make_ANBIMA_calendar() -> calendar
		{
			constexpr auto from = 2001y;
			constexpr auto until = Epoch.get_until().year();
			static_assert(from <= Epoch.get_from().year(), "Non-standard [from, until] should cover Epoch");

			const auto getter = [](const auto& x) noexcept { return x.holiday; };

			const auto filter1 = [](const auto& x) noexcept { return x.period.get_from().year() <= 2023y; };

			const auto rules1 = _ANBINA_annual_holiday_period_storage
				| views::filter(filter1)
				| views::transform(getter)
				| to<annual_holiday_storage>();

			const auto s1 = make_holiday_schedule(
				years_period{ from, 2023y },
				rules1
			);

			const auto filter2 = [](const auto& x) noexcept { return x.period.get_from().year() <= Epoch.get_until().year(); };

			const auto rules2 = _ANBINA_annual_holiday_period_storage
				| views::filter(filter2)
				| views::transform(getter)
				| to<annual_holiday_storage>();

			const auto s2 = make_holiday_schedule(
				years_period{ 2024y, until },
				rules2
			);

			return calendar{
				SaturdaySundayWeekend,
				s1 + s2
			};
			// please note that holidays are not adjusted in ANBIMA
		}



		auto make_ANBIMA_calendar() -> const calendar& // do we need the historic part explicitly?
		{
			static const auto s = _make_ANBIMA_calendar();
			return s;
		}

	}

}
