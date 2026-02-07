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

#include "util.h"
#include "makers.h"
#include "static_data.h"

#include <period.h>
#include <annual_holiday_interface.h>

#include <optional>
#include <chrono>
#include <stdexcept>
#include <cassert>
#include <algorithm>
#include <iterator>
#include <ranges>

using namespace std;
using namespace std::chrono;


namespace gregorian
{

	using namespace util;

	namespace static_data
	{

		// is it too confusing to have util.h/util.cpp here and util namespace elewhere?

		// first thing we need is to generate a generated period
		// from known_period and from the Epoch
		// (maybe ignore as_of_date for now, and handle it later)
		auto make_generated_period(
			const optional<days_period>& known,
			const days_period& epoch
		) -> optional<days_period>
		{
			if (!known || known->get_until() < epoch.get_from())
				return epoch;

			if (known->get_from() < epoch.get_from())
				throw out_of_range{ "Known period from can't be after epoch from" };

			if (known->get_until() >= epoch.get_until())
				return nullopt;

			const auto generated_from = year_month_day{ sys_days{ known->get_until() } + days{1} };
			const auto generated_until = epoch.get_until();

			return days_period{ generated_from, generated_until };
		}


		auto make_generated_sub_periods_as_of_date(
			const _annual_holiday_period_storage& storage,
			const year_month_day& as_of_date
		) -> days_period_set
		{
			const auto contains_as_of_date = [&as_of_date](const auto& x) noexcept {
				return as_of_date >= x.announced;
			};

			auto result = days_period_set{ Epoch };

			for (const auto& holiday : storage | views::filter(contains_as_of_date))
			{
//				assert(Epoch.contains(holiday.period));
				// we can probably make an optimistion and skip all the Epoch holidays

				auto it2_begin = result.begin();

				// does current "from" splits any of the existing periods?
				const auto it1 = lower_bound(
					result.rbegin(),
					result.rend(),
					holiday.period,
					[](const auto& rf, const auto& hf) { return rf.get_from() > hf.get_from(); }
				); // reverse iterator is probably bad for std::set, so we might need to consider something else here
				assert(it1 != result.crend());
				if (it1->get_from() != holiday.period.get_from())
				{
					const auto p1_from = it1->get_from();
					const auto p1_until = year_month_day{ sys_days{ holiday.period.get_from() } - days{ 1 } };
					const auto p2_from = holiday.period.get_from();
					const auto p2_until = it1->get_until();

					it2_begin = result.erase(next(it1).base());
					it2_begin = result.emplace_hint(it2_begin, days_period{ p1_from, p1_until });
					it2_begin = result.emplace_hint(it2_begin, days_period{ p2_from, p2_until });
				}

				// does current "until" splits any of the existing periods?
				const auto it2 = lower_bound( // should we use .lower_bound here?
					it2_begin,
					result.end(),
					holiday.period,
					[](const auto& ru, const auto& hu) { return ru.get_until() < hu.get_until(); }
				);
				assert(it2 != result.cend());
				if (it2->get_until() != holiday.period.get_until())
				{
					const auto p1_from = it2->get_from();
					const auto p1_until = holiday.period.get_until();
					const auto p2_from = year_month_day{ sys_days{ holiday.period.get_until() } + days{ 1 } };
					const auto p2_until = it2->get_until();

					auto it = result.erase(it2);
					it = result.emplace_hint(it, days_period{ p1_from, p1_until });
					result.emplace_hint(it, days_period{ p2_from, p2_until });
				}

				// there might be already an STL algorithm (or their combination) to do the above
			}

			return result;
		}


		auto make_holiday_schedule_as_of_date(
			const _annual_holiday_period_storage& storage,
			const year_month_day& as_of_date
		) -> annual_holiday_storage
		{
			return {};
		}

	}

}
