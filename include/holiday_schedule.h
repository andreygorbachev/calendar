#pragma once

#include <cstddef>
#include <chrono>
#include <bitset>
#include <memory>
#include <set>
#include <algorithm>
#include <cassert> // might not be needed in the future


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

	// if h2 before h1 should the function swap them around?
	inline auto operator+(const holiday_schedule& h1, const holiday_schedule& h2) -> holiday_schedule
	{
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
		// should we force that front is not after back
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
