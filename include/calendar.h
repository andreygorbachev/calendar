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

#include "weekend.h"
#include "schedule.h"
#include "business_day_convention_interface.h"

#include <cstddef>
#include <memory>
#include <chrono>
#include <vector>
#include <stdexcept>


namespace calendar
{

	class calendar
	{

	public:

		explicit calendar(weekend we, schedule hols);

	public:

		friend auto operator==(const calendar& cal1, const calendar& cal2) noexcept -> bool;

	public:

		auto is_business_day(const std::chrono::year_month_day& ymd) const -> bool;

		auto count_business_days(
			const std::chrono::year_month_day& f,
			const std::chrono::year_month_day& u
		) const -> std::size_t;

		// would "*" and "[]" make some sense here?
		// iterators?
		// serial dates?

		// should we have a notion of a "wall calendar" - 1 year (for the current year as a default)

	public:

		auto from_until() const noexcept -> const period&; // are we duplicating functionality here?

	public:

		void substitute(const business_day_convention* const bdc);

	public:

		auto get_weekend() const noexcept -> const weekend&;
		auto get_holiday_schedule() const noexcept -> const schedule&;

	private:

		void _make_bd_cache();

		auto _get_index(const std::chrono::year_month_day& ymd) const -> std::size_t;

		auto _is_business_day(const std::chrono::year_month_day& ymd) const noexcept -> bool;

		// we can try to factor out the cache as an (inner) class
		// (to make it clear what is what)

	private:

		weekend _we;
		schedule _hols;

	private:

		using _business_day_storage = std::vector<bool>;
		// do we need some notion of a "time series"?
		// (where we have a value for each day, etc)

		_business_day_storage _bd_cache;

	};



	inline auto operator==(const calendar& cal1, const calendar& cal2) noexcept -> bool
	{
		return cal1._bd_cache == cal2._bd_cache;
	}


	inline auto operator|(const calendar& cal1, const calendar& cal2) -> calendar
	{
		return calendar{
			cal1.get_weekend() | cal2.get_weekend(),
			cal2.get_holiday_schedule() | cal2.get_holiday_schedule()
		};
	}

	inline auto operator&(const calendar& cal1, const calendar& cal2) -> calendar
	{
		return calendar{
			cal1.get_weekend() & cal2.get_weekend(),
			cal2.get_holiday_schedule() & cal2.get_holiday_schedule()
		}; // is this right?
	}



	inline calendar::calendar(
		weekend we,
		schedule hols
	) :
		_we{ we },
		_hols{ hols }
	{
		_make_bd_cache();
	}


	inline void calendar::_make_bd_cache()
	{
		const auto& fu = from_until();
		const auto size = _get_index(fu.get_until()) + 1/*uz*/;

		_bd_cache.resize(size);

		const auto& f = fu.get_from();

		for (auto i = std::size_t{ 0/*uz*/ }; i < size; ++i)
		{
			const auto d = std::chrono::sys_days{ f } + std::chrono::days{ i };
			_bd_cache[i] = _is_business_day(d);
		}
	}

	inline auto calendar::_get_index(const std::chrono::year_month_day& ymd) const -> std::size_t
	{
		const auto& fu = from_until();
		if (ymd < fu.get_from() || ymd > fu.get_until())
			throw std::out_of_range{ "Request is not consistent with front or back" };

		const auto days = std::chrono::sys_days{ ymd } - std::chrono::sys_days{ fu.get_from() };
		return days.count();
	}

	inline auto calendar::_is_business_day(const std::chrono::year_month_day& ymd) const noexcept -> bool
	{
		return !_we.is_weekend(ymd) && !_hols.contains(ymd);
		// we allow a holiday on a weekend
	}


	inline void calendar::substitute(const business_day_convention* const bdc)
	{
		const auto hols = _hols.get_dates();
		for (const auto& holiday : hols)
		{
			_hols -= holiday;
			if (!_is_business_day(holiday))
			{
				const auto substitute_day = bdc->adjust(holiday, *this);
				_hols += substitute_day;
				_make_bd_cache(); // we do not actually need to fully rebuild the cache, so this could be optimised
			}
			else
			{
				_hols += holiday;
			}
		}

		// what happens if we have an exception?
	}


	inline auto calendar::is_business_day(const std::chrono::year_month_day& ymd) const -> bool
	{
		return _bd_cache[_get_index(ymd)];
	}

	inline auto calendar::count_business_days(
		const std::chrono::year_month_day& f,
		const std::chrono::year_month_day& u
	) const -> std::size_t
	{
		if (f > u)
			throw std::out_of_range{ "Front and back are not consistent" };

		auto result = std::size_t{ 0 };

		// naive implementation to start with
		for (auto d = f; d <= u; d = std::chrono::sys_days{ d } + std::chrono::days{ 1 })
			if (is_business_day(d))
				result++;

		return result;
	}


	inline auto calendar::from_until() const noexcept -> const period&
	{
		return _hols.get_from_until();
	}


	inline auto calendar::get_weekend() const noexcept -> const weekend&
	{
		return _we;
	}

	inline auto calendar::get_holiday_schedule() const noexcept -> const schedule&
	{
		return _hols;
	}

}
