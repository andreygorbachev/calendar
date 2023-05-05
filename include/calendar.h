#pragma once

#include <cstddef>
#include <chrono>
#include <bitset>
#include <memory>
#include <vector>
#include <algorithm>
#include <cassert> // might not be needed in the future



constexpr auto week_length = std::size_t{ std::chrono::Sunday.iso_encoding() };


class basic_calendar
{

public:

	using weekend_storage = std::bitset<week_length>;

public:

	constexpr basic_calendar() noexcept;

	constexpr explicit basic_calendar(weekend_storage weekend) noexcept;

	constexpr virtual ~basic_calendar() noexcept = default;

public:

	constexpr auto operator==(const basic_calendar&) const noexcept -> bool = default;

public:

	constexpr auto is_weekend(const std::chrono::year_month_day& ymd) const noexcept -> bool;

	constexpr virtual auto is_business_day(const std::chrono::year_month_day& ymd) const noexcept -> bool;

public:

	constexpr auto get_weekend() const noexcept -> const weekend_storage&;

private:

	weekend_storage _weekend;

};



class calendar : public basic_calendar
{

public:

	using holidays_storage = std::vector<std::chrono::year_month_day>;
	// I wonder if it is better to use std::set here (or some other ordered container), but that messes up constexpr

public:

	constexpr explicit calendar(
		std::chrono::year_month_day front,
		std::chrono::year_month_day back,
		holidays_storage holidays
	);

	constexpr explicit calendar(
		std::chrono::year_month_day front,
		std::chrono::year_month_day back,
		basic_calendar::weekend_storage weekend,
		holidays_storage holidays
	);

public:

	constexpr auto operator==(const calendar&) const noexcept -> bool = default;
	// at the moment this probably does not do the right thing:
	// 1) If we have a duplication of a date in one of them, which is the only difference, they would be different
	// 2) If 2 calendars just differ in the order of holidays they would be different

public:

	constexpr auto is_holiday(const std::chrono::year_month_day& ymd) const noexcept -> bool;

	constexpr auto is_business_day(const std::chrono::year_month_day& ymd) const noexcept -> bool override;

public:

	constexpr auto get_front() const noexcept -> const std::chrono::year_month_day&;
	constexpr auto get_back() const noexcept -> const std::chrono::year_month_day&;

	constexpr auto get_holidays() const noexcept -> const holidays_storage&;

private:

	std::chrono::year_month_day _front;
	std::chrono::year_month_day _back;

	holidays_storage _holidays;

};



constexpr auto operator|(const calendar& c1, const calendar& c2) -> calendar
{
	// consider better error handling
	assert(c1.get_front() == c2.get_front());
	assert(c1.get_back() == c2.get_back());

	const auto weekend = c1.get_weekend() | c2.get_weekend();

	// not efficient for now as we just duplicate the dates (mostly)
	const auto& h2 = c2.get_holidays();
	auto holidays = c1.get_holidays();
	holidays.insert(holidays.end(), h2.cbegin(), h2.cend());

	return calendar{ c1.get_front(), c1.get_back(), weekend, holidays };
}

constexpr auto operator&(const calendar& c1, const calendar& c2) -> calendar
{
	// consider better error handling
	assert(c1.get_front() == c2.get_front());
	assert(c1.get_back() == c2.get_back());

	const auto weekend = c1.get_weekend() & c2.get_weekend();

	const auto& h1 = c1.get_holidays();
	auto holidays = calendar::holidays_storage{};
	for (const auto& h : h1)
		if (c2.is_holiday(h))
			holidays.push_back(h);

	return calendar{ c1.get_front(), c1.get_back(), weekend, holidays };
}



constexpr basic_calendar::basic_calendar() noexcept : _weekend{}
{
	_weekend[std::chrono::Saturday.c_encoding()] = true;
	_weekend[std::chrono::Sunday.c_encoding()] = true;
}

constexpr basic_calendar::basic_calendar(weekend_storage weekend) noexcept : _weekend{ std::move(weekend) }
{
}


constexpr auto basic_calendar::is_weekend(const std::chrono::year_month_day& ymd) const noexcept -> bool
{
	const auto wd = std::chrono::weekday{ ymd };

	return _weekend[wd.c_encoding()];
}

constexpr auto basic_calendar::is_business_day(const std::chrono::year_month_day& ymd) const noexcept -> bool
{
	return !is_weekend(ymd);
}

constexpr auto basic_calendar::get_weekend() const noexcept -> const weekend_storage&
{
	return _weekend;
}



constexpr calendar::calendar(
	std::chrono::year_month_day front,
	std::chrono::year_month_day back,
	holidays_storage holidays
) : basic_calendar{},
	_front{ std::move(front) },
	_back{ std::move(back) },
	_holidays{ std::move(holidays) }
{
}

constexpr calendar::calendar(
	std::chrono::year_month_day front,
	std::chrono::year_month_day back,
	basic_calendar::weekend_storage weekend,
	holidays_storage holidays
) : basic_calendar{ std::move(weekend) },
	_front{ std::move(front) },
	_back{ std::move(back) },
	_holidays{ std::move(holidays) }
{
}


constexpr auto calendar::is_holiday(const std::chrono::year_month_day& ymd) const noexcept -> bool
{
	return std::find(_holidays.cbegin(), _holidays.cend(), ymd) != _holidays.cend();
}

constexpr auto calendar::is_business_day(const std::chrono::year_month_day& ymd) const noexcept -> bool
{
	return !is_weekend(ymd) && !is_holiday(ymd);
}

constexpr auto calendar::get_front() const noexcept -> const std::chrono::year_month_day&
{
	return _front;
}

constexpr auto calendar::get_back() const noexcept -> const std::chrono::year_month_day&
{
	return _back;
}

constexpr auto calendar::get_holidays() const noexcept -> const holidays_storage&
{
	return _holidays;
}
