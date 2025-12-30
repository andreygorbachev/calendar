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
#include <calendar.h>
#include <annual_holidays.h>
#include <weekend.h>

#include <chrono>
#include <vector>
#include <ranges>
#include <cassert>
#include <algorithm>
#include <iterator>

using namespace std;
using namespace std::chrono;
using namespace std::ranges;
using namespace std::ranges::views;


namespace gregorian
{

	using namespace util;

	namespace static_data
	{

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

		constexpr auto _ANBIMA_Epoch = period{
			year{ 2001 } / FirstDayOfJanuary, // starts before Epoch.get_from().year()
			Epoch.get_until()
		};

		const auto _ANBINA_annual_holiday_period_storage = _annual_holiday_period_storage{
			{ &NewYearsDay, _ANBIMA_Epoch, _ANBIMA_Epoch.get_from() },
			{ &_ShroveMonday, _ANBIMA_Epoch, _ANBIMA_Epoch.get_from() },
			{ &_ShroveTuesday, _ANBIMA_Epoch, _ANBIMA_Epoch.get_from() },
			{ &GoodFriday, _ANBIMA_Epoch, _ANBIMA_Epoch.get_from() },
			{ &_TiradentesDay, _ANBIMA_Epoch, _ANBIMA_Epoch.get_from() },
			{ &_LabourDay, _ANBIMA_Epoch, _ANBIMA_Epoch.get_from() },
			{ &_CorpusChristi, _ANBIMA_Epoch, _ANBIMA_Epoch.get_from() },
			{ &_IndependenceDay, _ANBIMA_Epoch, _ANBIMA_Epoch.get_from() },
			{ &_OurLadyOfAparecida, _ANBIMA_Epoch, _ANBIMA_Epoch.get_from() },
			{ &_AllSoulsDay, _ANBIMA_Epoch, _ANBIMA_Epoch.get_from() },
			{ &_RepublicProclamationDay, _ANBIMA_Epoch, _ANBIMA_Epoch.get_from() },
			{
				&_BlackConsciousnessDay,
				period{ 2024y / FirstDayOfJanuary, Epoch.get_until() }, // or should it be the first day it was celebrated? (are we dealing in whole years here?)
				2023y / December / 21d // was enacted as Law No. 14,759 on 21 December 2023
			},
			{ &ChristmasDay, _ANBIMA_Epoch, _ANBIMA_Epoch.get_from() }
		};


		static auto _make_ANBIMA_calendar(const year_month_day& as_of_date) -> calendar
		{
			const auto sub_epochs = _make_sub_epochs(
				_ANBINA_annual_holiday_period_storage,
				_ANBIMA_Epoch,
				as_of_date
			);
	
			assert(!sub_epochs.empty());
			const auto& se = sub_epochs.front();
			auto s = _make_holiday_schedule(
				_ANBINA_annual_holiday_period_storage,
				years_period{ se.get_from().year(), se.get_until().year() }
			);
			std::for_each(
				std::next(sub_epochs.cbegin()),
				sub_epochs.cend(),
				[&s](const auto& se){
					s += _make_holiday_schedule(
						_ANBINA_annual_holiday_period_storage,
						years_period{ se.get_from().year(), se.get_until().year() }
					);
				}
			);
			// there might be already an STL algorithm (or their combination) to do the above

			return calendar{
				SaturdaySundayWeekend,
				s
			};
			// please note that holidays are not adjusted in ANBIMA
		}


		auto make_ANBIMA_calendar_versions() -> _calendar_versions
		{
			const auto get_announced = [](const auto& x) noexcept {
				return x.announced;
			};

			// make below pretier?
#ifdef _MSC_BUILD
			auto versions = _ANBINA_annual_holiday_period_storage
				| views::transform(get_announced)
				| to<vector>();
#else
			auto _versions = _ANBINA_annual_holiday_period_storage
				| views::transform(get_announced);

			auto versions = vector<year_month_day>{};
			for (const auto& v : _versions)
				versions.push_back(v);
#endif
			ranges::sort(versions);
			const auto ret = ranges::unique(versions);
			versions.erase(ret.begin(), ret.end());

			auto result = _calendar_versions{};
			for (const auto& as_of_date : versions)
				result.emplace(as_of_date, _make_ANBIMA_calendar(as_of_date));
			return result;
		}

	}

}
