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
#include <annual_holiday_interface.h>
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


		static auto _make_sub_epochs(
			const _annual_holiday_period_storage& storage,
			const days_period& epoch,
			const year_month_day& as_of_date
		)
		{
			const auto contains_as_of_date = [&as_of_date](const auto& x) noexcept {
				return as_of_date >= x.announced;
			};

			auto result = vector<days_period>{ epoch }; // should it be std::set? // but I guess we maintain sorted order naturally anyway

			for (const auto& holiday : storage | views::filter(contains_as_of_date))
			{
//				assert(Epoch.contains(holiday.period));
				// we can probably make an optimistion and skip all the Epoch holidays

				auto it2_begin = result.begin();

				// does current "from" splits any of the existing periods?
				const auto it1 = std::lower_bound(
					result.rbegin(),
					result.rend(),
					holiday.period,
					[](const auto& rf, const auto& hf) { return rf.get_from() > hf.get_from(); }
				);
				assert(it1 != result.crend());
				if (it1->get_from() != holiday.period.get_from())
				{
					const auto p1_from = it1->get_from();
					const auto p1_until = holiday.period.get_from() - years{ 1 };
					const auto p2_from = holiday.period.get_from();
					const auto p2_until = it1->get_until();

					*it1 = days_period{ p1_from, p1_until };

					it2_begin = result.insert(it1.base(), days_period{ p2_from, p2_until }); // might not be the best with std::vector
				}

				// does current "until" splits any of the existing periods?
				const auto it2 = std::lower_bound(
					it2_begin,
					result.end(),
					holiday.period,
					[](const auto& ru, const auto& hu) { return ru.get_until() < hu.get_until(); }
				);
				assert(it2 != result.cend());
				if (it2->get_until() != holiday.period.get_until())
				{
					const auto it = std::prev(it2); // assert that it is valid?

					const auto p1_from = it1->get_from();
					const auto p1_until = holiday.period.get_until() - years{ 1 };
					const auto p2_from = holiday.period.get_until();
					const auto p2_until = it1->get_until();

					*it = days_period{ p1_from, p1_until };

					result.insert(std::next(it), days_period{ p2_from, p2_until }); // might not be the best with std::vector
				}

				// there might be already an STL algorithm (or their combination) to do the above
			}

			return result;
		}


		static auto _make_holiday_schedule(
			const _annual_holiday_period_storage& storage,
			const years_period& epoch
		) -> schedule
		{
			const auto get_holiday = [](const auto& x) noexcept { return x.holiday; };

			const auto _epoch = days_period{
				epoch.get_from() / FirstDayOfJanuary,
				Epoch.get_until()
			};

			const auto contains_epoch = [&_epoch](const auto& x) noexcept {
				return x.period.contains(_epoch);
			};

#ifdef _MSC_BUILD
			const auto rules = storage
				| views::filter(contains_epoch)
				| views::transform(get_holiday) // is there a way to use projections here?
				| to<annual_holiday_storage>();
#else
			auto _rules = storage
				| views::filter(contains_epoch)
				| views::transform(get_holiday);

			auto rules = annual_holiday_storage{};
			for (const auto& r : _rules)
				rules.push_back(r);
#endif

			return make_holiday_schedule(
				epoch,
				rules
			);
		}


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
			// temporary ignore the cancelled part of announced_cancelled

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
