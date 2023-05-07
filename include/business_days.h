#pragma once

#include "calendar.h"

#include <cstddef>
#include <memory>
#include <chrono>



class business_days
{

public:

	explicit business_days(const calendar* cal) noexcept;

public:

	auto is_business_day(const std::chrono::year_month_day& ymd) const noexcept -> bool;

	auto count(
		const std::chrono::year_month_day& start,
		const std::chrono::year_month_day& end
	) const -> std::size_t;
	// if end is before start should the function swap them around? (or return a negative number? or throw an exception)
	// if we need to return a negative number then the return should not be std::size_t (which we might want to change anyway)
	// should we consider calling start "front" and end "back" to be more consistent with STL
	// (or should we operate with "begin"/"end" ideas here instead)

private:

	const calendar* _calendar;

};



inline business_days::business_days(const calendar* cal) noexcept : _calendar{ cal }
{
}


inline auto business_days::is_business_day(const std::chrono::year_month_day& ymd) const noexcept -> bool
{
	return _calendar->is_business_day(ymd);
	// does it mean that is_business_day should be removed from calendar? (and only exist here)
}

inline auto business_days::count(
	const std::chrono::year_month_day& start,
	const std::chrono::year_month_day& end
) const -> std::size_t
{
	auto result = 0/*uz*/;

	// naive implementation to start with
	for (auto d = start; d <= end; d = std::chrono::sys_days{ d } + std::chrono::days{ 1 })
		if (is_business_day(d))
			result++;

	return result;
}
