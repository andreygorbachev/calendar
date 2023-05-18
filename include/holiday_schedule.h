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

	class holiday_schedule // rename to just schedule? (and we might have a regular_schedule as well for things like mortgage payments)
	{

	public:

		using storage = std::set<std::chrono::year_month_day>; // should we template on this? (so we can build schedules based on vector if needed)

	public:

		explicit holiday_schedule(
			std::chrono::year_month_day front,
			std::chrono::year_month_day back,
			storage hols
		);

	public:

		void operator+=(const holiday_schedule& h);

		void operator+=(const std::chrono::year_month_day& ymd);
		void operator-=(const std::chrono::year_month_day& ymd);

		friend auto operator==(const holiday_schedule& h1, const holiday_schedule& h2) noexcept -> bool = default;

	public:

		auto is_holiday(const std::chrono::year_month_day& ymd) const noexcept -> bool;

	public:

		auto get_front() const noexcept -> const std::chrono::year_month_day&;
		auto get_back() const noexcept -> const std::chrono::year_month_day&;

		auto get_hols() const noexcept -> const storage&;

	private:

		std::chrono::year_month_day _front;
		std::chrono::year_month_day _back;

		storage _hols;

	};



	inline auto operator|(const holiday_schedule& h1, const holiday_schedule& h2) -> holiday_schedule
	{
		auto front = std::max(h1.get_front(), h2.get_front());
		auto back = std::min(h1.get_back(), h2.get_back());

		auto hols2 = h2.get_hols();
		auto hols = h1.get_hols();
		hols.merge(std::move(hols2));

		return holiday_schedule{
			std::move(front),
			std::move(back),
			std::move(hols)
		};
	}

	inline auto operator&(const holiday_schedule& h1, const holiday_schedule& h2) -> holiday_schedule
	{
		auto front = std::max(h1.get_front(), h2.get_front());
		auto back = std::min(h1.get_back(), h2.get_back());

		const auto& hols1 = h1.get_hols();
		auto hols = holiday_schedule::storage{};
		for (const auto& h : hols1)
			if (h2.is_holiday(h))
				hols.insert(h);

		return holiday_schedule{
			std::move(front),
			std::move(back),
			std::move(hols)
		};
	}

	inline auto operator+(const holiday_schedule& h1, const holiday_schedule& h2) -> holiday_schedule
	{
		if (h1.get_front() > h2.get_front())
			return h2 + h1;

		if (std::chrono::sys_days{ h1.get_back() }++ == h2.get_front())
			throw std::out_of_range{ "Front and back are not consistent" };

		auto hols2 = h2.get_hols();
		auto hols = h1.get_hols();
		hols.merge(std::move(hols2));

		return holiday_schedule{
			h1.get_front(),
			h2.get_back(),
			std::move(hols)
		};
	}



	inline holiday_schedule::holiday_schedule(
		std::chrono::year_month_day front,
		std::chrono::year_month_day back,
		storage hols
	) : _front{ std::move(front) },
		_back{ std::move(back) },
		_hols{ std::move(hols) }
	{
		if (front > back)
			throw std::out_of_range{ "Front and back are not consistent" };

		// get rid of the part of hols which is outside [front, back]
		hols.erase(hols.begin(), std::lower_bound(hols.cbegin(), hols.cend(), _front));
		hols.erase(std::upper_bound(hols.cbegin(), hols.cend(), _back), hols.end());
	}


	inline void holiday_schedule::operator+=(const holiday_schedule& h)
	{
		*this = *this + h;
	}

	inline void holiday_schedule::operator+=(const std::chrono::year_month_day& ymd)
	{
		_hols.insert(ymd);
	}

	inline void holiday_schedule::operator-=(const std::chrono::year_month_day& ymd)
	{
		_hols.erase(ymd);
	}


	inline auto holiday_schedule::is_holiday(const std::chrono::year_month_day& ymd) const noexcept -> bool
	{
		// if ymd is outside [front, back] it is not a holiday

		return std::find(_hols.cbegin(), _hols.cend(), ymd) != _hols.cend();
	}

	inline auto holiday_schedule::get_front() const noexcept -> const std::chrono::year_month_day&
	{
		return _front;
	}

	inline auto holiday_schedule::get_back() const noexcept -> const std::chrono::year_month_day&
	{
		return _back;
	}

	inline auto holiday_schedule::get_hols() const noexcept -> const storage&
	{
		return _hols;
	}

}
