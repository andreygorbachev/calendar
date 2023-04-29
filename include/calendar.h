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

	constexpr basic_calendar() noexcept;

	constexpr explicit basic_calendar(weekend_storage weekend) noexcept;

public:

	constexpr bool operator==(const basic_calendar&) const noexcept = default;

public:

	constexpr auto is_weekend(const std::chrono::year_month_day& ymd) const noexcept -> bool;

	constexpr auto is_business_day(const std::chrono::year_month_day& ymd) const noexcept -> bool;

private:

	weekend_storage _weekend;

};


class calendar : public basic_calendar
{

};



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
