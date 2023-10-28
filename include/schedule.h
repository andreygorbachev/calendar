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

#include "period.h"

#include <cstddef>
#include <chrono>
#include <memory>
#include <set>
#include <algorithm>
#include <compare>


namespace gregorian
{

	class schedule
	{

	public:

		using storage = std::set<std::chrono::year_month_day>;

	public:

		explicit schedule(
			days_period from_until,
			storage dates
		);

		explicit schedule(
			storage dates
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

	public:

		auto get_from_until() const noexcept -> const days_period&;

		auto get_dates() const noexcept -> const storage&;

	private:

		void _trim();

	private:

		days_period _from_until;

		storage _dates;

	};



	inline auto operator|(schedule s1, schedule s2) -> schedule
	{
		auto& dates = s1._dates;
		dates.merge(s2._dates);

		return schedule{
			s1.get_from_until() | s2.get_from_until(),
			std::move(dates)
		};
	}

	inline auto operator&(schedule s1, schedule s2) -> schedule
	{
		auto dates = schedule::storage{};
		for (const auto& h : s1._dates)
			if (s2.contains(h))
				dates.insert(h);

		return schedule{
			s1.get_from_until() & s2.get_from_until(),
			std::move(dates)
		};
	}

	inline auto operator~(const schedule& s) -> schedule
	{
		auto from_until = s.get_from_until();
		auto dates = schedule::storage{};

		for (
			auto d = from_until.get_from();
			d <= from_until.get_until();
			d = std::chrono::sys_days{ d } + std::chrono::days{ 1 }
		)
			if (!s.contains(d))
				dates.insert(d);

		return schedule{
			std::move(from_until),
			std::move(dates)
		};
	}


	inline auto operator+(schedule s1, schedule s2) -> schedule
	{
		auto& dates = s1._dates;
		dates.merge(s2._dates);

		return schedule{
			s1.get_from_until() + s2.get_from_until(),
			std::move(dates)
		};
	}


	constexpr auto FirstDayOfJanuary = std::chrono::day{ 1u };
	constexpr auto LastDayOfDecember = std::chrono::day{ 31u };

	inline auto _make_from(const gregorian::schedule::storage& hols) noexcept -> std::chrono::year_month_day
	{
		const auto h = *hols.cbegin();

		return { h.year(), std::chrono::January, gregorian::FirstDayOfJanuary };
	}

	inline auto _make_until(const gregorian::schedule::storage& hols) noexcept -> std::chrono::year_month_day
	{
		const auto h = *hols.crbegin();

		return { h.year(), std::chrono::December, gregorian::LastDayOfDecember };
	}

	inline auto _make_from_until(const gregorian::schedule::storage& hols) noexcept -> gregorian::days_period
	{
		if (!hols.empty())
		{
			return { _make_from(hols), _make_until(hols) };
		}
		else
		{
			const auto any_date = std::chrono::year_month_day{};

			return { any_date, any_date };
		}
	}


	inline schedule::schedule(
		days_period from_until,
		storage dates
	) : _from_until{ std::move(from_until) },
		_dates{ std::move(dates) }
	{
		_trim();
	}

	inline schedule::schedule(
		storage dates
	) : _from_until{ {}, {} },
		_dates{ std::move(dates) }
	{
		_from_until = _make_from_until(_dates);

		_trim();
	}


	inline void schedule::_trim()
	{
		// get rid of the hols which are outside [from, until]
		_dates.erase(_dates.begin(), std::lower_bound(_dates.cbegin(), _dates.cend(), _from_until.get_from()));
		_dates.erase(std::upper_bound(_dates.cbegin(), _dates.cend(), _from_until.get_until()), _dates.end());
	}


	inline auto schedule::operator+=(schedule s) -> schedule&
	{
		*this = *this + std::move(s);

		return *this;
	}

	inline auto schedule::operator+=(const std::chrono::year_month_day& ymd) -> schedule&
	{
		if(_from_until.contains(ymd))
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

	inline auto schedule::get_from_until() const noexcept -> const days_period&
	{
		return _from_until;
	}

	inline auto schedule::get_dates() const noexcept -> const storage&
	{
		return _dates;
	}

}
