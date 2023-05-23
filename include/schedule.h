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

#include <cstddef>
#include <chrono>
#include <bitset>
#include <memory>
#include <set>
#include <algorithm>
#include <stdexcept>


namespace calendar
{

	class schedule
	{

	public:

		using storage = std::set<std::chrono::year_month_day>;
		// should we template on this? (so we can build schedules based on vector if needed)
		// or should we just work with a sorted vector (without duplicates)
		// as we build a schedule once and use it many times in a sequential manner

	public:

		explicit schedule(
			std::chrono::year_month_day from,
			std::chrono::year_month_day until,
			storage dates
		);

	public:

		void operator+=(const schedule& h);

		void operator+=(const std::chrono::year_month_day& ymd);
		void operator-=(const std::chrono::year_month_day& ymd);

		friend auto operator==(const schedule& s1, const schedule& s2) noexcept -> bool = default;

	public:

		auto contains(const std::chrono::year_month_day& ymd) const noexcept -> bool;

	public:

		auto get_from() const noexcept -> const std::chrono::year_month_day&;
		auto get_until() const noexcept -> const std::chrono::year_month_day&;

		auto get_dates() const noexcept -> const storage&;

	private:

		std::chrono::year_month_day _from;
		std::chrono::year_month_day _until;

		storage _dates;

	};



	inline auto operator|(const schedule& s1, const schedule& s2) -> schedule
	{
		auto from = std::max(s1.get_from(), s2.get_from());
		auto until = std::min(s1.get_until(), s2.get_until());

		auto dates2 = s2.get_dates();
		auto dates = s1.get_dates();
		dates.merge(std::move(dates2));

		return schedule{
			std::move(from),
			std::move(until),
			std::move(dates)
		};
	}

	inline auto operator&(const schedule& s1, const schedule& s2) -> schedule
	{
		auto from = std::max(s1.get_from(), s2.get_from());
		auto until = std::min(s1.get_until(), s2.get_until());

		const auto& dates1 = s1.get_dates();
		auto dates = schedule::storage{};
		for (const auto& h : dates1)
			if (s2.contains(h))
				dates.insert(h);

		return schedule{
			std::move(from),
			std::move(until),
			std::move(dates)
		};
	}

	inline auto operator+(const schedule& s1, const schedule& s2) -> schedule
	{
		if (s1.get_from() > s2.get_from())
			return s2 + s1;

		if (std::chrono::sys_days{ s1.get_until() }++ == s2.get_from())
			throw std::out_of_range{ "Front and back are not consistent" };

		auto dates2 = s2.get_dates();
		auto dates = s1.get_dates();
		dates.merge(std::move(dates2));

		return schedule{
			s1.get_from(),
			s2.get_until(),
			std::move(dates)
		};
	}



	inline schedule::schedule(
		std::chrono::year_month_day from,
		std::chrono::year_month_day until,
		storage dates
	) : _from{ std::move(from) },
		_until{ std::move(until) },
		_dates{ std::move(dates) }
	{
		if (_from > _until)
			throw std::out_of_range{ "Front and back are not consistent" };

		// get rid of the part of hols which is outside [front, back]
		dates.erase(dates.begin(), std::lower_bound(dates.cbegin(), dates.cend(), _from));
		dates.erase(std::upper_bound(dates.cbegin(), dates.cend(), _until), dates.end());
	}


	inline void schedule::operator+=(const schedule& h)
	{
		*this = *this + h;
	}

	inline void schedule::operator+=(const std::chrono::year_month_day& ymd)
	{
		_dates.insert(ymd);
	}

	inline void schedule::operator-=(const std::chrono::year_month_day& ymd)
	{
		_dates.erase(ymd);
	}


	inline auto schedule::contains(const std::chrono::year_month_day& ymd) const noexcept -> bool
	{
		// if ymd is outside [front, back] it is not a holiday

		return std::find(_dates.cbegin(), _dates.cend(), ymd) != _dates.cend();
	}

	inline auto schedule::get_from() const noexcept -> const std::chrono::year_month_day&
	{
		return _from;
	}

	inline auto schedule::get_until() const noexcept -> const std::chrono::year_month_day&
	{
		return _until;
	}

	inline auto schedule::get_dates() const noexcept -> const storage&
	{
		return _dates;
	}

}
