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

	// we should think about what to do for dates which are not "ok"
	class holiday_schedule
	{

	public:

		using storage = std::set<std::chrono::year_month_day>;

	public:

		// or we should use "begin"/"end" instead of "front"/"back"
		// (or use the same ideas but with different names)

		explicit holiday_schedule(
			std::chrono::year_month_day front,
			std::chrono::year_month_day back,
			storage hols
		);

		// should we have a notion of a "wall calendar" - 1 year (for the current year as a default)

	public:

		// add operator+=(holiday_schedule)

		void operator+=(std::chrono::year_month_day ymd);
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

		// consider better error handling
	//	assert(std::chrono::sys_days{ h1.get_back() }++ == h2.get_front()); // no gaps between calendars are allowed

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

		// is it ok for holidays before _front or after _back
	}


	inline void holiday_schedule::operator+=(std::chrono::year_month_day ymd)
	{
		_hols.insert(std::move(ymd));
	}

	inline void holiday_schedule::operator-=(const std::chrono::year_month_day& ymd)
	{
		_hols.erase(ymd);
	}


	inline auto holiday_schedule::is_holiday(const std::chrono::year_month_day& ymd) const noexcept -> bool
	{
		// check that ymd is inside our calendar

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
