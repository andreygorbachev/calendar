#pragma once

#include <cstddef>
#include <chrono>
#include <bitset>
#include <memory>
#include <set>
#include <algorithm>
#include <cassert> // might not be needed in the future



// we should think about what to do for dates which are not "ok"
class calendar // rename to holiday_schedule
{

public:

	using holidays_storage = std::set<std::chrono::year_month_day>;

public:

	// or we should use "begin"/"end" instead of "front"/"back"
	// (or use the same ideas but with different names)

	explicit calendar(
		std::chrono::year_month_day front,
		std::chrono::year_month_day back,
		holidays_storage holidays
	);

	// should we have a notion of a "wall calendar" - 1 year (for the current year as a default)

public:

	friend auto operator==(const calendar& c1, const calendar& c2) noexcept -> bool = default;
	// at the moment this probably does not do the right thing:
	// 1) If we have a duplication of a date in one of them, which is the only difference, they would be different
	// 2) If 2 calendars just differ in the order of holidays they would be different

	// add operator+=

public:

	auto is_holiday(const std::chrono::year_month_day& ymd) const noexcept -> bool;

public:

	auto get_front() const noexcept -> const std::chrono::year_month_day&;
	auto get_back() const noexcept -> const std::chrono::year_month_day&;

	auto get_holidays() const noexcept -> const holidays_storage&;

private:

	std::chrono::year_month_day _front;
	std::chrono::year_month_day _back;

	holidays_storage _holidays;

};



inline auto operator|(const calendar& c1, const calendar& c2) -> calendar
{
	auto front = std::max(c1.get_front(), c2.get_front());
	auto back = std::min(c1.get_back(), c2.get_back());

	auto h2 = c2.get_holidays();
	auto holidays = c1.get_holidays();
	holidays.merge(h2);

	return calendar{
		std::move(front),
		std::move(back),
		std::move(holidays)
	};
}

inline auto operator&(const calendar& c1, const calendar& c2) -> calendar
{
	auto front = std::max(c1.get_front(), c2.get_front());
	auto back = std::min(c1.get_back(), c2.get_back());

	const auto& h1 = c1.get_holidays();
	auto holidays = calendar::holidays_storage{};
	for (const auto& h : h1)
		if (c2.is_holiday(h))
			holidays.insert(h);

	return calendar{
		std::move(front),
		std::move(back),
		std::move(holidays)
	};
}

// if c2 before c1 should the function swap them around?
inline auto operator+(const calendar& c1, const calendar& c2) -> calendar
{
	// consider better error handling
//	assert(std::chrono::sys_days{ c1.get_back() }++ == c2.get_front()); // no gaps between calendars are allowed

	auto h2 = c2.get_holidays();
	auto holidays = c1.get_holidays();
	holidays.merge(h2);

	return calendar{
		c1.get_front(),
		c2.get_back(),
		std::move(holidays)
	};
}



inline calendar::calendar(
	std::chrono::year_month_day front,
	std::chrono::year_month_day back,
	holidays_storage holidays
) : _front{ std::move(front) },
	_back{ std::move(back) },
	_holidays{ std::move(holidays) }
{
	// should we force that front is not after back
	// is it ok for holidays before _front or after _back
}


inline auto calendar::is_holiday(const std::chrono::year_month_day& ymd) const noexcept -> bool
{
	// check that ymd is inside our calendar

	return std::find(_holidays.cbegin(), _holidays.cend(), ymd) != _holidays.cend();
}

inline auto calendar::get_front() const noexcept -> const std::chrono::year_month_day&
{
	return _front;
}

inline auto calendar::get_back() const noexcept -> const std::chrono::year_month_day&
{
	return _back;
}

inline auto calendar::get_holidays() const noexcept -> const holidays_storage&
{
	return _holidays;
}
