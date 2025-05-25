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

#pragma once

#include "iota.h"
#include "time_series.h"

#include "weekend.h"
#include "schedule.h"
#include "business_day_adjuster_interface.h"

#include <cstddef>
#include <utility>
#include <chrono>
#include <vector>
#include <stdexcept>
#include <compare>
#include <ranges>


namespace gregorian
{

	class calendar
	{

	public:

		explicit calendar(weekend we, schedule hols);

	public:

		friend auto operator==(const calendar& cal1, const calendar& cal2) noexcept -> bool;
		friend auto operator<=>(const calendar& cal1, const calendar& cal2) noexcept -> std::strong_ordering = delete;

	public:

		auto is_non_business_day(const std::chrono::year_month_day& ymd) const -> bool;

		auto is_non_business_day(const std::chrono::sys_days& sd) const -> bool;

	public:

		auto is_business_day(const std::chrono::year_month_day& ymd) const -> bool;

		auto is_business_day(const std::chrono::sys_days& sd) const -> bool;

		auto count_business_days(const days_period& p) const -> std::size_t;

		auto count_business_days(const period<std::chrono::sys_days>& p) const -> std::size_t;

		// is returning schedule the right thing to do?
		auto make_business_days_schedule(const days_period& p) const -> schedule;

		auto make_business_days_schedule(const period<std::chrono::sys_days>& p) const -> schedule;

	public:

		void substitute(const business_day_adjuster& a);

	public:

		auto get_weekend() const noexcept -> const weekend&;
		auto get_schedule() const noexcept -> const schedule&;

	private:

		auto _is_non_business_day(const std::chrono::year_month_day& ymd) const noexcept -> bool;

	private:

		weekend _we;
		schedule _hols;

	private:

		struct cache
		{
			explicit cache(const calendar& cal);

			void substitute(
				const std::chrono::year_month_day& out,
				const std::chrono::year_month_day& in,
				const weekend& we
			);

			_time_series<bool> _non_business_days;
			// calendars follow a 28 year cycle (apart of Easter, which has its own, much longer cycle)
			// so maybe this could be done better (only cache a single cycle)
		};

		cache _cache;

	};



	inline auto operator==(const calendar& cal1, const calendar& cal2) noexcept -> bool
	{
		return cal1._cache._non_business_days == cal2._cache._non_business_days;
	}


	inline auto operator|(const calendar& cal1, const calendar& cal2) -> calendar
	{
		const auto p = cal1.get_schedule().get_period() & cal2.get_schedule().get_period();
		const auto s = cal1.get_schedule() | cal2.get_schedule();

		return calendar{
			cal1.get_weekend() | cal2.get_weekend(),
			schedule{ p, s.get_dates() }
		};
	}

	inline auto operator&(const calendar& cal1, const calendar& cal2) -> calendar
	{
		return calendar{
			cal1.get_weekend() & cal2.get_weekend(),
			cal1.get_schedule() & cal2.get_schedule()
		};
	}



	inline calendar::calendar(
		weekend we,
		schedule hols
	) :	_we{ std::move(we) },
		_hols{ std::move(hols) },
		_cache{ *this }
	{
	}


	inline auto calendar::_is_non_business_day(const std::chrono::year_month_day& ymd) const noexcept -> bool
	{
		return _we.is_weekend(ymd) || _hols.contains(ymd);
	}


	inline void calendar::substitute(const business_day_adjuster& a)
	{
		auto sub_cal = *this;

		for (const auto& holiday : _hols.get_dates())
		{
			sub_cal._hols -= holiday;
			if (sub_cal._is_non_business_day(holiday))
			{
				const auto substitute_day = a.adjust(holiday, *this);
				sub_cal._hols += substitute_day;
				sub_cal._cache.substitute(holiday, substitute_day, _we);
			}
			else
			{
				sub_cal._hols += holiday;
			}
		}

		*this = std::move(sub_cal);
	}


	inline auto calendar::is_non_business_day(const std::chrono::year_month_day& ymd) const -> bool
	{
		return _cache._non_business_days[ymd];
	}

	inline auto calendar::is_non_business_day(const std::chrono::sys_days& sd) const -> bool
	{
		return _cache._non_business_days[sd];
	}

	inline auto calendar::is_business_day(const std::chrono::year_month_day& ymd) const -> bool
	{
		return !is_non_business_day(ymd);
	}

	inline auto calendar::is_business_day(const std::chrono::sys_days& sd) const -> bool
	{
		return !is_non_business_day(sd);
	}

	// alternative implementation would be to cache the number of business days per month (and possibly per year)
	// like described in the following article:
	// https://www.clarusft.com/implementing-bus252-daycount-convention/
	// or to cache the substituted holidays in an ordered vector, so we know how many holidays are between
	// from and until, which we'll need to further adjust by the number of weekends between the same 2 dates
	inline auto calendar::count_business_days(const days_period& period) const -> std::size_t
	{
		const auto non_business_days = _cache._non_business_days.count(period);
		const auto calendar_days =
			std::chrono::sys_days{ period.get_until() } - std::chrono::sys_days{ period.get_from() };

		using namespace std::chrono;
		return calendar_days.count() - non_business_days + 1uz;
	}

	inline auto calendar::count_business_days(const period<std::chrono::sys_days>& p) const -> std::size_t
	{
		const auto non_business_days = _cache._non_business_days.count(p);
		const auto calendar_days = p.get_until() - p.get_from();

		using namespace std::chrono;
		return calendar_days.count() - non_business_days + 1uz;
	}

	inline auto calendar::make_business_days_schedule(const days_period& p) const -> schedule
	{
		// or implement directly?
		return make_business_days_schedule(period<std::chrono::sys_days>{
			p.get_from(),
			p.get_until()
		});
	}

	inline auto calendar::make_business_days_schedule(const period<std::chrono::sys_days>& p) const -> schedule
	{
		const auto& v = p.get_from();
		const auto b = p.get_until() + std::chrono::days{ 1 }; // iota::iota "boundary" below (non inclusive) is not the same as "period end" (inclusive)

		const auto is_bd = [this](const std::chrono::sys_days& d)
		{
			return is_business_day(d);
		};

		auto s =
			iota::iota(v, b) |
			std::views::filter(is_bd) |
			std::ranges::to<schedule::dates>();

		return schedule{
			days_period{ p.get_from(), p.get_until() },
			std::move(s)
		 };
	}


	inline auto calendar::get_weekend() const noexcept -> const weekend&
	{
		return _we;
	}

	inline auto calendar::get_schedule() const noexcept -> const schedule&
	{
		return _hols;
	}


	inline calendar::cache::cache(const calendar& cal)
		: _non_business_days{ cal.get_schedule().get_period() }
	{
		const auto [f, u] = cal.get_schedule().get_period().from_until();
		for (
			auto d = f;
			d <= u;
			d = std::chrono::sys_days{ d } + std::chrono::days{ 1 }
		)
			_non_business_days[d] = cal._is_non_business_day(d);
	}


	inline void calendar::cache::substitute(
		const std::chrono::year_month_day& out,
		const std::chrono::year_month_day& in,
		const weekend& we
	)
	{
		_non_business_days[out] = we.is_weekend(out); // we allow a holiday on a weekend
		_non_business_days[in] = true;
	}

}
