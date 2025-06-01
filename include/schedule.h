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

#include <period.h>

#include <cstddef>
#include <chrono>
#include <utility>
#include <set>
#include <algorithm>
#include <compare>

#define SCHEDULE_YEAR_MONTH_DAY_BASED
//#undef SCHEDULE_YEAR_MONTH_DAY_BASED



namespace gregorian
{

	class schedule
	{

	public:

#ifdef SCHEDULE_YEAR_MONTH_DAY_BASED
		using dates = std::set<std::chrono::year_month_day>;
#else
		using dates = std::set<std::chrono::sys_days>;
#endif

	public:

		explicit schedule(
			util::days_period p,
			dates ds
		);

		explicit schedule(
			dates ds
		);

	public:

		friend auto operator+(schedule s1, schedule s2) -> schedule;
			
		auto operator+=(schedule s) -> schedule&;

		auto operator+=(const std::chrono::year_month_day& ymd) -> schedule&;
		auto operator-=(const std::chrono::year_month_day& ymd) -> schedule&;

		friend auto operator==(const schedule& s1, const schedule& s2) noexcept -> bool = default;
		friend auto operator<=>(const schedule& s1, const schedule& s2) noexcept -> std::strong_ordering = delete;

		friend auto operator|(schedule s1, schedule s2) -> schedule;
		friend auto operator&(schedule s1, schedule s2) -> schedule;

	public:

		auto contains(const std::chrono::year_month_day& ymd) const noexcept -> bool;

		auto contains(const std::chrono::sys_days& sd) const noexcept -> bool;

	public:

		auto get_period() const noexcept -> const util::days_period&;

		auto get_dates() const noexcept -> const dates&;

	private:

		void _trim();

	private:

		util::days_period _period;

		dates _dates;

	};



	inline auto operator|(schedule s1, schedule s2) -> schedule
	{
		auto& ds = s1._dates;
		ds.merge(s2._dates);

		return schedule{
			s1.get_period() | s2.get_period(),
			std::move(ds)
		};
	}

	inline auto operator&(schedule s1, schedule s2) -> schedule
	{
		auto ds = schedule::dates{};
		for (const auto& d : s1._dates)
			if (s2.contains(d))
				ds.insert(d);

		return schedule{
			s1.get_period() & s2.get_period(),
			std::move(ds)
		};
	}

	inline auto operator~(const schedule& s) -> schedule
	{
		auto p = s.get_period();
		auto ds = schedule::dates{};

		for (
			auto d = p.get_from();
			d <= p.get_until();
			d = std::chrono::sys_days{ d } + std::chrono::days{ 1 }
		)
			if (!s.contains(d))
				ds.insert(d);

		return schedule{
			std::move(p),
			std::move(ds)
		};
	}


	inline auto operator+(schedule s1, schedule s2) -> schedule
	{
		auto& ds = s1._dates;
		ds.merge(std::move(s2._dates));

		return schedule{
			s1.get_period() + s2.get_period(),
			std::move(ds)
		};
	}


	constexpr auto FirstDayOfJanuary = std::chrono::January / std::chrono::day{ 1u };
	constexpr auto LastDayOfDecember = std::chrono::December / std::chrono::day{ 31u };

	inline auto _make_from(const schedule::dates& dates) noexcept -> std::chrono::year_month_day
	{
		const auto d = *dates.cbegin();

#ifdef SCHEDULE_YEAR_MONTH_DAY_BASED
		return d.year() / FirstDayOfJanuary;
#else
		return std::chrono::year_month_day{ d }.year() / FirstDayOfJanuary;
#endif
	}

	inline auto _make_until(const schedule::dates& dates) noexcept -> std::chrono::year_month_day
	{
		const auto d = *dates.crbegin();

#ifdef SCHEDULE_YEAR_MONTH_DAY_BASED
		return d.year() / LastDayOfDecember;
#else
		return std::chrono::year_month_day{ d }.year() / LastDayOfDecember;
#endif
	}

	inline auto _make_period(const schedule::dates& ds) noexcept -> util::days_period
	{
		if (!ds.empty())
		{
			return util::days_period{ _make_from(ds), _make_until(ds) };
		}
		else
		{
			const auto any_date = std::chrono::year_month_day{};

			return util::days_period{ any_date, any_date };
		}
	}


	inline schedule::schedule(
		util::days_period p,
		dates ds
	) : _period{ std::move(p) },
		_dates{ std::move(ds) }
	{
		_trim();
	}

	inline schedule::schedule(
		dates ds
	) : _period{ _make_period(ds) },
		_dates{ std::move(ds) }
	{
		_trim();
	}


	inline void schedule::_trim()
	{
		// get rid of the dates which are outside [from, until]
		_dates.erase(_dates.begin(), std::lower_bound(_dates.cbegin(), _dates.cend(), _period.get_from()));
		_dates.erase(std::upper_bound(_dates.cbegin(), _dates.cend(), _period.get_until()), _dates.end());
	}


	inline auto schedule::operator+=(schedule s) -> schedule&
	{
		*this = *this + std::move(s);

		return *this;
	}

	inline auto schedule::operator+=(const std::chrono::year_month_day& ymd) -> schedule&
	{
		if(_period.contains(ymd))
			_dates.insert(ymd);

		return *this;
	}

	inline auto schedule::operator-=(const std::chrono::year_month_day& ymd) -> schedule&
	{
		_dates.erase(ymd);

		return *this;
	}


	inline auto schedule::contains(const std::chrono::year_month_day& ymd) const noexcept -> bool
	{
		return std::find(_dates.cbegin(), _dates.cend(), ymd) != _dates.cend();
	}

	inline auto schedule::contains(const std::chrono::sys_days& sd) const noexcept -> bool
	{
		return contains(std::chrono::year_month_day{ sd });
	}

	inline auto schedule::get_period() const noexcept -> const util::days_period&
	{
		return _period;
	}

	inline auto schedule::get_dates() const noexcept -> const dates&
	{
		return _dates;
	}

}
