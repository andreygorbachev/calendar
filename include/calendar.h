#pragma once

#include <cstddef>
#include <chrono>
#include <bitset>
#include <memory>
#include <vector>
#include <algorithm>


class basic_calendar
{

public:

	using weekend_storage = std::bitset<std::size_t{ 7 }>;

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

	using holiday_storage = std::vector<std::chrono::year_month_day>;

public:

	constexpr explicit calendar(
		holiday_storage holidays
	);

	constexpr explicit calendar(
		basic_calendar::weekend_storage weekend,
		holiday_storage holidays
	);

public:

	constexpr auto operator==(const calendar&) const noexcept -> bool = default;

public:

	constexpr auto is_holiday(const std::chrono::year_month_day& ymd) const noexcept -> bool;

	constexpr auto is_business_day(const std::chrono::year_month_day& ymd) const noexcept -> bool override;

private:

	holiday_storage _holidays;

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

constexpr auto basic_calendar::get_weekend() const noexcept -> const weekend_storage&
{
	return _weekend;
}



constexpr calendar::calendar(
	holiday_storage holidays
) : basic_calendar{},
	_holidays{ std::move(holidays) }
{
}

constexpr calendar::calendar(
	basic_calendar::weekend_storage weekend,
	holiday_storage holidays
) : basic_calendar{ std::move(weekend) },
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
