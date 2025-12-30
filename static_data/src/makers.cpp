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

#include "makers.h"
#include "static_data.h"

#include <calendar.h>
#include <schedule.h>
#include <weekend.h>
#include <period.h>
#include <annual_holiday_interface.h>
#include <business_day_adjuster_interface.h>

#include <string>
#include <string_view>
#include <stdexcept>
#include <chrono>
#include <cassert>
#include <vector>
#include <ranges>
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

		static auto _make_sub_epochs(
			const _annual_holiday_period_storage& rules,
			const days_period& epoch,
			const year_month_day& as_of_date
		) -> vector<days_period>
		{
			const auto contains_as_of_date = [&as_of_date](const auto& x) noexcept {
				return as_of_date >= x.announced;
			};

			auto result = vector<days_period>{ epoch }; // should it be std::set? // but I guess we maintain sorted order naturally anyway

			for (const auto& holiday : rules | views::filter(contains_as_of_date))
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
			const _annual_holiday_period_storage& rules,
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
			const auto rules2 = rules // we need a better name
				| views::filter(contains_epoch)
				| views::transform(get_holiday) // is there a way to use projections here?
				| to<annual_holiday_storage>();
#else
			auto _rules2 = rules
				| views::filter(contains_epoch)
				| views::transform(get_holiday);

			auto rules2 = annual_holiday_storage{};
			for (const auto& r : _rules2)
				rules2.push_back(r);
#endif

			return make_holiday_schedule(
				epoch,
				rules2
			);
		}


		static auto _make_calendar(
			const _annual_holiday_period_storage& rules,
			const days_period& epoch,
			const weekend& we,
			const business_day_adjuster& adjuster,
			const year_month_day& as_of_date
		) -> calendar
		{
//			const auto known_part = schedule{};

			const auto sub_epochs = _make_sub_epochs(rules, epoch, as_of_date);

			assert(!sub_epochs.empty());
			const auto& se = sub_epochs.front();
			auto generated_part = _make_holiday_schedule(
				rules,
				years_period{ se.get_from().year(), se.get_until().year() }
			);
			std::for_each(
				std::next(sub_epochs.cbegin()),
				sub_epochs.cend(),
				[&rules, &generated_part](const auto& se) { // ideally we should capture rules by const reference
					generated_part += _make_holiday_schedule(
						rules,
						years_period{ se.get_from().year(), se.get_until().year() }
					);
				}
			);
			// there might be already an STL algorithm (or their combination) to do the above

			// setup a calendar for the generated part only (to do substitution for the generated dates)
			auto cal = calendar{ we, generated_part };
			cal.substitute(adjuster);

			return calendar{
				we,
				/*known_part +*/ cal.get_schedule()
			};
		}


		auto _make_calendar_versions(
			const _annual_holiday_period_storage& rules,
			const days_period& epoch,
			const weekend& we,
			const business_day_adjuster& adjuster
			) -> _calendar_versions
		{
			const auto get_announced = [](const auto& x) noexcept {
				return x.announced;
			};

			// make below pretier?
#ifdef _MSC_BUILD
			auto versions = rules
				| views::transform(get_announced)
				| to<vector>();
#else
			auto _versions = rules
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
				result.emplace(
					as_of_date,
					_make_calendar(rules, epoch, we, adjuster, as_of_date)
				);
			return result;
		}



		static auto _make_calendar_registry() -> _calendar_registry
		{
			// at the moment we create all calendars (needed or not), which might or might not be what we want
			// this could be changed to lazy creation if needed, but we'll have to deal with synchronization then
			return _calendar_registry{
				{ "Europe/London", _calendar_versions{ { 2026y / FirstDayOfJanuary, make_England_calendar() } } }, // from UK, only London is in tzdata
				{ "Europe/Cardif", _calendar_versions{ { 2026y / FirstDayOfJanuary, make_Wales_calendar() } } },
				{ "Europe/Edinburgh", _calendar_versions{ { 2026y / FirstDayOfJanuary, make_Scotland_calendar() } } },
				{ "Europe/Belfast", _calendar_versions{ { 2026y / FirstDayOfJanuary, make_Northern_Ireland_calendar() } } },
				{ "Europe/MPC", _calendar_versions{ { 2026y / FirstDayOfJanuary, make_MPC_calendar() } } }, // or should it be Europe/UK/MPC? or should it be in etcetera?

				{ "Europe/T2", _calendar_versions{ { 2026y / FirstDayOfJanuary, make_T2_calendar() } } }, // or should it be Europe/EU/TARGET2? or should it be in etcetera?

				{ "America/USA", _calendar_versions{ { 2026y / FirstDayOfJanuary, make_USA_Federal_calendar() } } },
				{ "America/Washington", _calendar_versions{ { 2026y / FirstDayOfJanuary, make_Washington_DC_Federal_calendar() } } }, // not a city, but federal holidays

				{ "America/Canada", _calendar_versions{ { 2026y / FirstDayOfJanuary, make_Canada_Federal_calendar() } } },
				{ "America/Ontario", _calendar_versions{ { 2026y / FirstDayOfJanuary, make_Ontario_calendar() } } },
				{ "America/Quebec", _calendar_versions{ { 2026y / FirstDayOfJanuary, make_Quebec_calendar() } } },

				{ "America/ANBIMA", make_ANBIMA_calendar_versions() }, // or should it be America/Brazil/ANBIMA? or should it be in etcetera?
			};
		}

		auto _get_calendar_registry() -> const _calendar_registry&
		{
			static const auto r = _make_calendar_registry(); // ideally all this will be generated at compile time
			return r;
		}


		static auto _locate_calendar_versions(string_view tz_name) -> const _calendar_versions&
		{
			const auto& reg = _get_calendar_registry();

			const auto it = reg.find(tz_name);
			if (it != reg.cend())
				return it->second;
			else
				throw runtime_error{ "calendar "s + string{ tz_name } + " could not be located"s };
		}

		auto locate_calendar(string_view tz_name, year_month_day as_of_date) -> const calendar&
		{
			const auto& cal_versions = _locate_calendar_versions(tz_name);
			assert(!cal_versions.empty());

			const auto earliest_as_of_date = cal_versions.cbegin()->first;
			if (as_of_date >= earliest_as_of_date)
			{
				const auto cal_iter = --cal_versions.upper_bound(as_of_date);

				return cal_iter->second;
			}
			else
				throw runtime_error{ "calendar's version as of date "s + string{ tz_name } + " could not be located"s };
		}

		// not 100% sure about following tz-data, but it seems to be ok for now
		// (not sure if continent is important to calendars)

		// we'll probably end up with a separate data file like tz-data (maybe in a similar format)
		// or an sqlite database

		// #embed could also be considered, at least for the known dates

	}

}
