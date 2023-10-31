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

#include "time_series.h"

#include "weekend.h"
#include "schedule.h"
#include "business_day_convention_interface.h"

#include <cstddef>
#include <memory>
#include <chrono>
#include <vector>
#include <stdexcept>
#include <compare>


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

		auto is_business_day(const std::chrono::year_month_day& ymd) const -> bool;

		auto count_business_days(const days_period& from_until) const -> std::size_t;

	public:

		void substitute(const business_day_convention* const bdc);

	public:

		auto get_weekend() const noexcept -> const weekend&;
		auto get_schedule() const noexcept -> const schedule&;

	private:

		auto _is_business_day(const std::chrono::year_month_day& ymd) const noexcept -> bool;

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

			_time_series<bool> _business_days;
		};

		cache _cache;

	};



	inline auto operator==(const calendar& cal1, const calendar& cal2) noexcept -> bool
	{
		return cal1._cache._business_days == cal2._cache._business_days;
	}


	inline auto operator|(const calendar& cal1, const calendar& cal2) -> calendar
	{
		const auto p = cal1.get_schedule().get_from_until() & cal2.get_schedule().get_from_until();
		const auto s = cal1.get_schedule() | cal2.get_schedule();

		return calendar{
			cal1.get_weekend() | cal2.get_weekend(),
			schedule{ p, s.get_dates() } // can we do a move here?
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


	inline auto calendar::_is_business_day(const std::chrono::year_month_day& ymd) const noexcept -> bool
	{
		return !_we.is_weekend(ymd) && !_hols.contains(ymd);
	}


	inline void calendar::substitute(const business_day_convention* const bdc)
	{
		auto sub_cal = *this;

		for (const auto& holiday : _hols.get_dates())
		{
			sub_cal._hols -= holiday;
			if (!sub_cal._is_business_day(holiday))
			{
				const auto substitute_day = bdc->adjust(holiday, *this);
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


	inline auto calendar::is_business_day(const std::chrono::year_month_day& ymd) const -> bool
	{
		return _cache._business_days[ymd];
	}

	inline auto calendar::count_business_days(const days_period& from_until) const -> std::size_t
	{
		auto result = std::size_t{ 0 };

		// naive implementation to start with
		for (
			auto d = from_until.get_from();
			d <= from_until.get_until();
			d = std::chrono::sys_days{ d } + std::chrono::days{ 1 }
		)
			if (is_business_day(d))
				result++;

		return result;
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
		: _business_days{ cal.get_schedule().get_from_until() }
	{
		const auto& fu = cal.get_schedule().get_from_until();
		for (auto d = fu.get_from(); d <= fu.get_until(); d = std::chrono::sys_days{ d } + std::chrono::days{ 1 })
			_business_days[d] = cal._is_business_day(d);
	}


	inline void calendar::cache::substitute(
		const std::chrono::year_month_day& out,
		const std::chrono::year_month_day& in,
		const weekend& we
	)
	{
		_business_days[out] = !we.is_weekend(out); // we allow a holiday on a weekend
		_business_days[in] = false;
	}

}
