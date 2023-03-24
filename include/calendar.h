#pragma once

#include <cstddef>
#include <chrono>
#include <bitset>
#include <memory>


class basic_calendar
{

public:

	using weekend_storage = std::bitset<std::size_t{ 7 }>;

public:

	basic_calendar() noexcept;

	explicit basic_calendar(weekend_storage weekend) noexcept;

public:

	auto is_weekend(const std::chrono::year_month_day& ymd) const noexcept -> bool;

	auto is_business_day(const std::chrono::year_month_day& ymd) const noexcept -> bool;

private:

	weekend_storage _weekend;

};



inline basic_calendar::basic_calendar() noexcept : _weekend{}
{
	_weekend[std::chrono::Saturday.c_encoding()] = true;
	_weekend[std::chrono::Sunday.c_encoding()] = true;
}

inline basic_calendar::basic_calendar(weekend_storage weekend) noexcept : _weekend{ std::move(weekend) }
{
}


inline auto basic_calendar::is_weekend(const std::chrono::year_month_day& ymd) const noexcept -> bool
{
	const auto wd = std::chrono::weekday{ ymd };

	return _weekend[wd.c_encoding()];
}

inline auto basic_calendar::is_business_day(const std::chrono::year_month_day& ymd) const noexcept -> bool
{
	return !is_weekend(ymd);
}
